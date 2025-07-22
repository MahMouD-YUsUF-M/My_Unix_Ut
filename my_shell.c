      #include <stdio.h>
 #include <string.h>

int main(int argc , char* argv[]){
char *line = NULL;
    size_t len = 0;
int f=0,r=0;
        while(!f)
        {
                printf("Femto shell prompt >");
         ssize_t read = getline(&line, &len, stdin);
        if (read == -1) break;
                          line[strcspn(line, "\n")] = '\0';
          char *token=strtok(line," ");
           if (!token) continue;
          if(strcmp(token,"exit") == 0)
                          {
                            f=1;
                       printf("%s","Good Bye\n");
                      continue;
                         }
          else  if (strcmp(token,"echo") == 0)
                {
                    int sp=1;
                    token=strtok(NULL," ");
                    while(token != NULL ){
                        if(!sp)
                        printf(" ");
                    printf("%s",token);
                    sp=0;
                      token=strtok(NULL," ");
                    }
                    printf("\n");
                }
        else
        {
         printf("%s","Invalid command\n");
         r=1;
        }

        }
        return r;
}





