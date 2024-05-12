#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    struct stat s;
    stat("testDir", &s);

    if (S_ISREG(s.st_mode))
    {
        printf("这是普通文件\n");
    }
    if (S_ISDIR(s.st_mode))
     {
         printf("这是文件夹\n");
     }

     

    if ((s.st_mode & S_IRUSR) == S_IRUSR)
    {
        printf("所有者具备读权限\n");
    }

    if (S_ISCHR(s.st_mode))
    {
        printf("11");
    }
}

