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
    char ch;
    struct input_event kevent;
    char *usage = "usage\n\t-b : run in background\n\t-f : output to a file\n";
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
    while( ( ch = getopt( argc, argv, "hbf:" ) ) != EOF ) 
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
                printf("the arg is %s\n",optarg);
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
                   if(kevent.type==EV_KEY)
                   printf("type:%u \t code:%u \t value%d \n",kevent.type,kevent.code,kevent.value);
               } 
        }
    return 0;
}