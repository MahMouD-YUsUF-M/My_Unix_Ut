     #include <fcntl.h>
       #include <unistd.h>
#include <stdio.h>
int main(int argc , char* argv [])
{
        char buffer[1024];

int fi = open(argv[1],O_RDONLY);
ssize_t r;
if( fi<0)
{
    printf("error");
    return 1;
}
int si = open(argv[2],O_RDWR|O_CREAT| O_TRUNC,0644);
if( si<0)
{
    printf("error");
    return 1;
}
while(  (r = read(fi,buffer,sizeof(buffer)))>0)
{
int  w=write(si,buffer,r);
}
close(si);
remove(argv[1]);
return 0;
}


