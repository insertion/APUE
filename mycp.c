#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
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
void copydir(char *src,char *des,struct stat src_stat)
{
    DIR *dp;
    struct dirent *dirp;
    char *spathname,*dpathname;
    dp=opendir(src);
    if(mkdir(des,src_stat.st_mode)==-1)
    {
        printf("mkdir %s error,maybe the dir has being exsit!\n",des);
    }
    while(dirp=readdir(dp))
    {
        if (!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, ".."))
			{
				continue;
			}
        spathname = (char *)malloc(2+strlen(src+strlen(dirp->d_name)));
        dpathname = (char *)malloc(2+strlen(des+strlen(dirp->d_name)));
        sprintf(spathname,"%s/%s",src,dirp->d_name);
        sprintf(dpathname,"%s/%s",des,dirp->d_name);
    
        if(stat(spathname,&src_stat)==-1)
        {
          printf("stat error\n");
        }
        if(S_ISDIR(src_stat.st_mode))
            copydir(spathname,dpathname,src_stat);
        else
            copydata(spathname,dpathname);
        free(spathname);
        free(dpathname);
    }
}
int main(int argc,char **argv)
{
     if(argc<3)
        printf("usage: cp filename filename \n");
   struct stat src_stat;
   if(stat(argv[1],&src_stat)==-1)
    {
        printf("stat error\n");
    }
    if(S_ISDIR(src_stat.st_mode))
            copydir(argv[1],argv[2],src_stat);
        else
            copydata(argv[1],argv[2]);
    return 0;
}