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
        while (1)
        {
            printf("这里是子进程ID:%d;父进程的ID为:%d\n", getpid(),getppid());
            sleep(2);
        }
    }
    else if (id > 0) // 大于0表示fork返回的是子进程Id，即其是父进程
    {
            printf("这里是父进程ID:%d,其将在2秒后终止\n", getpid());
            sleep(2);
    }

    return 0;//只有父进程会到达这里，到此父进程终止，子进程成为孤儿进程
}
