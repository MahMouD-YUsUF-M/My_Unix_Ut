#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>

extern char **environ;

int
nanoshell_main (int argc, char *argv[])
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

      char *nargv[PATH_MAX] = { 0 };
      nargv[0] = strtok (buf, " ");

      int i;
      for (i = 1; i < PATH_MAX && nargv[i - 1] != NULL; i++)
	{
	  nargv[i] = strtok (NULL, " ");
	}

      for (i = 0; nargv[i] != NULL; i++)
	{
	  char *src = nargv[i];
	  char tmp[8192] = { 0 };
	  int t = 0;
	  while (*src && t < sizeof (tmp) - 1)
	    {
	      if (*src == '$')
		{
		  src++;
		  char var[4096] = { 0 };
		  int v = 0;
		  while ((*src == '_' || isalnum (*src))
			 && v < sizeof (var) - 1)
		    {
		      var[v++] = *src++;
		    }
		  var[v] = '\0';
		  const char *env_eval = getenv (var);
		  if (env_eval)
		    {
		      strncat (tmp, env_eval,
			       sizeof (tmp) - strlen (tmp) - 1);
		      t = strlen (tmp);
		    }
		}
	      else
		{
		  tmp[t++] = *src++;
		}
	    }
	  tmp[t] = '\0';
	  nargv[i] = strdup (tmp);
	}


  for (i = 0; nargv[i]; i++) {
            if (strcmp(nargv[i], "<") == 0 && nargv[i + 1]) {
                in = nargv[++i];
                if (in[0] == '$') {
                    char *env_val = getenv(in + 1);
                    if (!env_val) {
                        fprintf(stderr, "cannot access %s: No such file or directory\n", in + 1);
                        last_status = 1;
                        in = NULL;
                        break;
                    }
                    in = env_val;
                }
            } else if (strcmp(nargv[i], ">") == 0 && nargv[i + 1]) {
                out = nargv[++i];
                if (out[0] == '$') {
                    char *env_val = getenv(out + 1);
                    if (!env_val) {
                        fprintf(stderr, "cannot access %s: No such file or directory\n", out + 1);
                        last_status = 1;
                        out = NULL;
                        break;
                    }
                    out = env_val;
                }
            } else if (strcmp(nargv[i], "2>") == 0 && nargv[i + 1]) {
                error = nargv[++i];
                if (error[0] == '$') {
                    char *env_val = getenv(error + 1);
                    if (!env_val) {
                        fprintf(stderr, "cannot access %s: No such file or directory\n", error + 1);
                        last_status = 1;
                        error = NULL;
                        break;
                    }
                    error = env_val;
                }
            } 
        }


      if (nargv[0] == NULL)
	continue;

      if (strcmp (nargv[0], "exit") == 0)
	{
	  printf ("Good Bye\n");
	  break;
	}

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
	  if (nargv[1])
	    {
	      putenv (nargv[1]);
	      last_status = 0;
	    }
	  else
	    {
	      fprintf (stderr, "export: missing argument\n");
	      last_status = 1;
	    }
	  continue;
	}

      if (nargv[1] == NULL && strchr (nargv[0], '=') != NULL)
	{
	  if (strlen (nargv[0]) >= 3 && nargv[0][0] != '='
	      && nargv[0][strlen (nargv[0]) - 1] != '=')
	    {
	      putenv (nargv[0]);
	      last_status = 0;
	    }
	  else
	    {
	      fprintf (stderr, "Invalid environment assignment\n");
	      last_status = 1;
	    }
	  continue;
	}

      pid_t pid = fork ();
      if (pid > 0)
	{
	  int status;
	  waitpid (pid, &status, 0);
	  if (WIFEXITED (status))
	    {
	      last_status = WEXITSTATUS (status);
	    }
	  else
	    {
	      last_status = 1;
	    }
	}
      else if (pid == 0)
	{
	  execvp (nargv[0], nargv);
	  fprintf (stderr, "%s: command not found\n", nargv[0]);
	  exit (127);
	}
      else
	{
	  perror ("fork failed");
	  free (buf);
	  return 1;
	}

      for (i = 0; nargv[i] != NULL; i++)
	{
	  free (nargv[i]);
	}
    }

  free (buf);
  return last_status;
}
