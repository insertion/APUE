#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#define MAXSIZE 1024
void copydata(char *src,char *des)
{
    struct stat sstat;
    int n;
    char buff[MAXSIZE];
    int sfd=open(src,O_RDONLY);
    if (fstat(sfd,&sstat) == -1) 
    {
        printf("fstat error\n");
    }
    int dfd=open(des,O_WRONLY|O_CREAT);
    chmod(des,sstat.st_mode);
    //set des file's mode as src's
    while((n=read(sfd,buff,MAXSIZE)) > 0)
    {
        if(write(dfd,buff,n)!=n)
            printf("write error\n");
    }
    close(sfd);
    close(dfd);
}

int main(int argc,char **argv)
{
    if(argc<3)
        printf("usage: cp filename filename \n");
    copydata(argv[1],argv[2]);
    return 0;
}