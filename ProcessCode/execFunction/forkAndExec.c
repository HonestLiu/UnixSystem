#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    // 使用vfork创建子进程
    pid_t pid = vfork();

    // 子进程
    if (pid == 0)
    {
        sleep(3);
        printf("子进程:%d\n",getpid());
        execl("/usr/bin/ls", "ls", "-a", "-h", NULL);
        _exit(-1);
    }

    // 父进程
    if (pid > 0)
    {
        for (size_t i = 1; i < 10; i++)
        {
            printf("父进程:%d的i=%ld\n", getpid(), i);
            sleep(1);
        }
    }

    return 0;
}
