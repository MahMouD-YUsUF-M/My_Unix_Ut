#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>

extern char **environ;



typedef enum {REDIR_IN ,REDIR_OUT,REDIR_ERR} REDIRtype;
typedef struct {
    REDIRtype type;
char *filename;
    
}Redirection;


char *expand_vars(const char *input) {
    if (!input) return NULL;
    char *result = (char *)malloc(8192);
    if (!result) return NULL;

    char *dest = result;
    const char *src = input;

    while (*src && (dest - result) < 8191) {
        if (*src == '$' && (isalnum(src[1]) || src[1] == '_')) {
            src++;
            char var[4096] = {0};
            int v = 0;
            while ((isalnum(*src) || *src == '_') && v < 4095) {
                var[v++] = *src++;
            }
            const char *val = getenv(var);
            if (val) {
                strcpy(dest, val);
                dest += strlen(val);
            }
        } else {
            *dest++ = *src++;
        }
    }
    *dest = '\0';
    return result;
}

void cleanup_resources(Redirection *redirs, int redir_count, char **args, int *needs_free, char *input_copy) {
    for (int i = 0; i < redir_count; i++) {
        free(redirs[i].filename);
    }
    if (args && needs_free) {
        for (int i = 0; args[i]; i++) {
            if (needs_free[i]) {
                free(args[i]);
            }
        }
    }
    free(input_copy);
}

int microshell_main(int argc, char *argv[]) {
    char *buf = NULL;
    size_t buf_size = 0;
    int last_status = 0;

    while (1) {
        printf("micro shell prompt > ");
        fflush(stdout);

        ssize_t read = getline(&buf, &buf_size, stdin);
        if (read == -1) break;
        if (read > 0 && buf[read - 1] == '\n')
            buf[read - 1] = '\0';
        if (strlen(buf) == 0) continue;

        char *input_copy = strdup(buf);
        if (!input_copy) {
            perror("strdup failed");
            continue;
        }

        char *nargv[PATH_MAX] = {0};
        nargv[0] = strtok(input_copy, " ");
        int i;
        for (i = 1; i < PATH_MAX && nargv[i - 1]; i++)
            nargv[i] = strtok(NULL, " ");

        Redirection redirs[PATH_MAX];
        int redir_count = 0;
        char *args[PATH_MAX] = {0};
        int argi = 0;
        int needs_free[PATH_MAX] = {0};
        int parse_error = 0;

        for (i = 0; nargv[i] && !parse_error; i++) {
            if ((strcmp(nargv[i], "<") == 0 || strcmp(nargv[i], ">") == 0 || strcmp(nargv[i], "2>") == 0) && nargv[i + 1]) {
                REDIRtype type;
                if (strcmp(nargv[i], "<") == 0) type = REDIR_IN;
                else if (strcmp(nargv[i], ">") == 0) type = REDIR_OUT;
                else type = REDIR_ERR;

                char *expanded = expand_vars(nargv[++i]);
                if (!expanded) {
                    fprintf(stderr, "expansion failed\n");
                    last_status = 1;
                    parse_error = 1;
                } else {
                    redirs[redir_count++] = (Redirection){ type, expanded };
                }
            } else {
                args[argi] = nargv[i];
                needs_free[argi] = 0;
                argi++;
            }
        }
        args[argi] = NULL;

        if (parse_error) {
            cleanup_resources(redirs, redir_count, args, needs_free, input_copy);
            continue;
        }

        for (i = 0; args[i] && !parse_error; i++) {
            char *expanded = expand_vars(args[i]);
            if (!expanded) {
                fprintf(stderr, "expansion failed\n");
                last_status = 1;
                parse_error = 1;
            } else {
                if (strcmp(expanded, args[i]) != 0) {
                    args[i] = expanded;
                    needs_free[i] = 1;
                } else {
                    free(expanded);
                }
            }
        }

        if (parse_error) {
            cleanup_resources(redirs, redir_count, args, needs_free, input_copy);
            continue;
        }

        if (!args[0]) {
            cleanup_resources(redirs, redir_count, args, needs_free, input_copy);
            continue;
        }

        // Built-in commands (only if no redirection)
        if (redir_count == 0) {
            if (strcmp(args[0], "exit") == 0) {
                printf("Good Bye\n");
                cleanup_resources(redirs, redir_count, args, needs_free, input_copy);
                break;
            }

            if (strcmp(args[0], "cd") == 0) {
                const char *target = args[1] ? args[1] : getenv("HOME");
                if (chdir(target) != 0) {
                    fprintf(stderr, "cd: %s: %s\n", target, strerror(errno));
                    last_status = 1;
                } else {
                    last_status = 0;
                }
                cleanup_resources(redirs, redir_count, args, needs_free, input_copy);
                continue;
            }

            if (strcmp(args[0], "pwd") == 0) {
                char cwd[PATH_MAX];
                if (getcwd(cwd, sizeof(cwd))) {
                    printf("%s\n", cwd);
                    last_status = 0;
                } else {
                    perror("pwd failed");
                    last_status = 1;
                }
                cleanup_resources(redirs, redir_count, args, needs_free, input_copy);
                continue;
            }

            if (strcmp(args[0], "echo") == 0) {
                for (int j = 1; args[j]; j++) {
                    printf("%s", args[j]);
                    if (args[j + 1]) printf(" ");
                }
                printf("\n");
                last_status = 0;
                cleanup_resources(redirs, redir_count, args, needs_free, input_copy);
                continue;
            }

            if (strcmp(args[0], "export") == 0) {
                if (args[1] && strchr(args[1], '=')) {
                    char *arg_copy = strdup(args[1]);
                    if (arg_copy) {
                        char *name = strtok(arg_copy, "=");
                        char *value = strtok(NULL, "");
                        if (name && value) {
                            if (setenv(name, value, 1) == 0) {
                                last_status = 0;
                            } else {
                                perror("export failed");
                                last_status = 1;
                            }
                        } else {
                            fprintf(stderr, "export: invalid syntax\n");
                            last_status = 1;
                        }
                        free(arg_copy);
                    } else {
                        perror("export: memory allocation failed");
                        last_status = 1;
                    }
                } else {
                    fprintf(stderr, "export: missing or invalid argument\n");
                    last_status = 1;
                }
                cleanup_resources(redirs, redir_count, args, needs_free, input_copy);
                continue;
            }

            if (!args[1] && strchr(args[0], '=') && args[0][0] != '=') {
                char *arg_copy = strdup(args[0]);
                if (arg_copy) {
                    char *name = strtok(arg_copy, "=");
                    char *value = strtok(NULL, "");
                    if (name && value) {
                        if (setenv(name, value, 1) != 0) {
                            perror("variable assignment failed");
                        }
                    }
                    free(arg_copy);
                }
                cleanup_resources(redirs, redir_count, args, needs_free, input_copy);
                continue;
            }
        }

        // External command execution
        pid_t pid = fork();
        if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            last_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
        } else if (pid == 0) {
            for (int i = 0; i < redir_count; i++) {
                Redirection r = redirs[i];
                int fd = -1;
                if (r.type == REDIR_IN) {
                    fd = open(r.filename, O_RDONLY);
                    if (fd < 0 || dup2(fd, STDIN_FILENO) == -1) {
                        dprintf(STDERR_FILENO, "cannot access %s: %s\n", r.filename, strerror(errno));
                        exit(1);
                    }
                } else if (r.type == REDIR_OUT) {
                    fd = open(r.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd < 0) {
                    dprintf(STDERR_FILENO, "%s: %s\n", r.filename, strerror(errno));
                    exit(1);
                }
                if (dup2(fd, STDOUT_FILENO) == -1) {
                    dprintf(STDERR_FILENO, "dup2 failed for stdout: %s\n", strerror(errno));
                    close(fd);
                    exit(1);
                }
                
                } else if (r.type == REDIR_ERR) {
                    fd = open(r.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd < 0 || dup2(fd, STDERR_FILENO) == -1) {
                        dprintf(STDERR_FILENO, "cannot create %s: %s\n", r.filename, strerror(errno));
                        exit(1);
                    }
                }
                if (fd != -1) close(fd);
            }

            execvp(args[0], args);
            dprintf(STDERR_FILENO, "%s: command not found\n", args[0]);
            exit(127);
        } else {
            perror("fork failed");
            free(buf);
            return 1;
        }

        cleanup_resources(redirs, redir_count, args, needs_free, input_copy);
    }

    free(buf);
    return last_status;
}

