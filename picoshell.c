#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <linux/limits.h>
#include <errno.h>
extern char **environ;		// Declare environ as external
int nanoshell_main (int argc, char *argv[])
{
  char *buf = NULL;
  size_t buf_size = 0;
  int last_status = 0;



  while (1)
    {
      printf ("Nano shell prompt > ");
      fflush (stdout);

      ssize_t read = getline (&buf, &buf_size, stdin);
      if (read == -1)
	break;

      if (read > 0 && buf[read - 1] == '\n')
	buf[read - 1] = '\0';

      if (strlen (buf) == 0)
	continue;

      char *nargv[PATH_MAX];
      nargv[0] = strtok (buf, " ");
      int i;
      for (i = 1; i < PATH_MAX && nargv[i - 1] != NULL; i++)
	{
	  nargv[i] = strtok (NULL, " ");
	}

      if (nargv[0] == NULL)
	continue;

      // Built-in: exit
      if (strcmp (nargv[0], "exit") == 0)
	{
	  printf ("Good Bye\n");
	  break;
	}

      // Built-in: cd
      if (strcmp (nargv[0], "cd") == 0)
	{
	  const char *target =
	    (nargv[1] != NULL) ? nargv[1] : getenv ("HOME");
	  if (chdir (target) != 0)
	    {
	      fprintf (stderr, "cd: %s: %s\n", target, strerror (errno));
	      last_status = 1;
	    }
	  else
	    {
	      last_status = 0;
	    }
	  continue;
	}

      // Built-in: pwd
      if (strcmp (nargv[0], "pwd") == 0)
	{
	  char cwd[PATH_MAX];
	  if (getcwd (cwd, sizeof (cwd)) != NULL)
	    {
	      printf ("%s\n", cwd);
	      last_status = 0;
	    }
	  else
	    {
	      perror ("pwd failed");
	      last_status = 1;
	    }
	  continue;
	}

      // Built-in: echo
      if (strcmp (nargv[0], "echo") == 0)
	{
	  for (int j = 1; nargv[j] != NULL; j++)
	    {
	      printf ("%s", nargv[j]);
	      if (nargv[j + 1] != NULL)
		printf (" ");
	    }
	  printf ("\n");
	  last_status = 0;
	  continue;
	}

      if (strcmp (nargv[0], "export") == 0)
	{
	  putenv (nargv[1]);
printf ("\n");
	  last_status = 0;
	  continue;
	}
      if (nargv[1] == NULL && strchr (nargv[0], '=') != NULL)
	{
	  if (strlen (nargv[0]) >= 3 && nargv[0][0] != '='
	      && nargv[0][strlen (nargv[0]) - 0] != '=')
	    {
	      putenv (nargv[0]);
printf ("\n");
	  last_status = 0;
	    }
	  else
	    {
	      perror ("Invalid command");
	      last_status = 1;
	    }
continue;

	}

      // External command
      pid_t pid = fork();
        if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                last_status = WEXITSTATUS(status);
            } else {
                last_status = 1;
            }
        } else if (pid == 0) {
            execvp(nargv[0], nargv);
            fprintf(stderr, "%s: command not found\n", nargv[0]);
            exit(127);  // Command not found exit code
        } else {
            perror("fork failed");
            free(buf);
            return 1;
        }
    }

    free(buf);
    return last_status;
}

