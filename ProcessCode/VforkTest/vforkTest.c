#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
/*
验证vfork创建的子进程在调用exec之前都是和父进程占用一个进程的，且子进程会在父进程之前运行
 */
int main()
{

    // 验证空间共享的变量(要在创建子线程之前声明变量)
    int num = 6;
    // 使用vfork创建子进程
    pid_t pid = vfork();

    // 在子进程内修改数据，并输出信息
    if (pid == 0)
    {
        num = 100;
        printf("子进程:%d的num值为:%d\n", getpid(), num);

        // vfork创建的子进程必须显式的关闭，否则可能会导致资源泄露
        _exit(-1);
    }

    // 父进程打印num的值
    if (pid > 0)
    {
        printf("父进程:%d的num值为:%d\n", getpid(), num);
    }

    return 0;
}