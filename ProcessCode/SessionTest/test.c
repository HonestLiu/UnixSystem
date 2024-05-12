#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
/*
创建会话，必须要先由父进程创建一个子进程
然后，先终止父进程，再由子进程调用setsid创建会话
 */

int main()
{

    // 创建子进程
    pid_t pid = fork();
    /*父进程终止，子进程创建会话*/

    // 返回子进程id的是父进程
    if (pid > 0)
    {
        _exit(-1);
    }

    // 父进程已终止，剩下的都是子进程了

    /* 创建会话*/
    setsid();
    printf("子进程进程号:%d\n", getpid());

    // 阻塞一下，避免子进程终止
    while (1)
        ;

    return 0;
}