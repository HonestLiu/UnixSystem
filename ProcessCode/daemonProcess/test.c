#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

/*
创建守护进程
 */

int main()
{
    // 创建子进程
    pid_t pid = fork();

    // 关闭父进程，使其形式上脱离终端控制
    if (pid > 0)
    {
        _exit(-1);
    }

    // 创建会话,使子进程完全脱离终端控制
    setsid();

    // 改变当前目录为根目录
    chdir("/home");

    // 重设文件掩码
    umask(0002);

    // 关闭不必要的文件描述符,主要指的是0、1、2这三个面向终端的
    close(0);
    close(1);
    close(2);

    // 书写守护进程的业务
    while (1)
    {

    }

    return 0;
}