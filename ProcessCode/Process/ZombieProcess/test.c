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

    if (id == 0) // 返回为0，表示该进程是子进程
    {
        // 显示的结束子进程
        _exit(-1);
    }
    else if (id > 0) // 大于0表示fork返回的是子进程Id，即其是父进程
    {
        printf("父进程不结束，不去回收终止的子进程\n");
        sleep(1);
        while (1)
        {
        }
    }

    return 0;
}
