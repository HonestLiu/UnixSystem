#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    // 使用fork创建子进程
    pid_t id = fork();
    // 判断是否创建失败
    if (id < 0)
    {
        perror("create");
    }

    // 定义一个变量(父子进程均拥有)
    int num = 0;

    /* 通过fork的返回值，判断此时是位于哪个进程 */
    if (id == 0) // 返回为0，表示该进程是子进程
    {
        printf("这里是子进程ID:%d\n", getpid());
        num = 66;
        printf("子进程的num值为:%d\n", num);
    }
    else if (id > 0) // 大于0表示fork返回的是子进程Id，即其是父进程
    {
        printf("这里是父进程ID:%d\n", getpid());
        printf("子进程的num值为:%d\n", num);
    }
}
