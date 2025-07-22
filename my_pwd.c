#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>
int main()
{

	char cwd[PATH_MAX];
        if(getcwd(cwd,sizeof(cwd)) != NULL)
		{
                   printf("%s\n",cwd);
		}
	else
	{
	printf("error");
	return 1;
	}
	return 0;
	
}


