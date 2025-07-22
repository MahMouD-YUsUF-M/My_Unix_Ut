       #include <stdio.h>
 #include <string.h>

int main(int argc , char* argv[]){
char line[255];
int f=0;
	while(!f)
	{
           fgets(line,sizeof(line),stdin);
	   char *token= strtok(line," ");
	   while(token != NULL ){
           
		   if(token=="exit")
		   {
			   f=1;
		       printf("%s","Good Bye :)");
                      break;
		   }
		   else if(token!="echo")
                      {
                      printf("%s","Invalid command");
                      break;
                      } 
		   else 
		   {
			   printf("%s",token);
		   }

	   }
	}
}
