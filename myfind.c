#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
//#define UNIX
void list(char *path,char * target)
{
	//typedef struct __dirsteram DIR;
	DIR * dsp;
	struct dirent *dirp;
	char *nextpath;
	if(dsp=opendir(path))
		while(dirp=readdir(dsp))
			{
				if (!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, ".."))
					{
						continue;
					}
    

#ifdef UNIX
				if(!strcmp(dirp->d_name,target))
					printf("%s/%s\t%d\n",path,dirp->d_name,dirp->d_type);
				if(dirp->d_type==DT_DIR)
                //this is not neccssary accturly
					{
						nextpath = (char *)malloc(strlen(path)+strlen(dirp->d_name)+2);
						sprintf (nextpath, "%s/%s", path, dirp->d_name);
						list(nextpath,target);
						free(nextpath);
					}
#else
                    if(!strcmp(dirp->d_name,target))
					    printf("%s/%s\n",path,dirp->d_name);
                    nextpath = (char *)malloc(strlen(path)+strlen(dirp->d_name)+2);
					sprintf (nextpath, "%s/%s", path, dirp->d_name);
					list(nextpath,target);
					free(nextpath);
#endif
			}
	closedir(dsp);
}
int main(int argc,char**argv)
{
	if(argc<3)
		{
			printf("YOU MUST INPUT PATH AND TARGET\n");
			printf("usage : find path target\n");
		}
    else    
        list(argv[1],argv[2]);

	return 0;
}
