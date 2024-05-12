#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    /* 获取进程ID */
    pid_t pid = getpid();
    printf("当前的进程ID为:%d\n", pid);

    /* 获取当前进程的父进程ID */
    pid_t ppid = getppid();
    printf("当前进程的父进程ID为:%d\n", ppid);
    
    /* 获取当前进程的组ID */
    pid_t pgid = getpgid(0);
    printf("当前的组ID为:%d\n", pgid);
}
/* 
当前的进程ID为:6994
当前进程的父进程ID为:5683
当前的组ID为:6994
 */