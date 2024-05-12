#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/* 创建一个子进程，并在5秒后关闭它 */
int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // 正常来说这个子进程是永远不会停止的
        while (1)
        {
            printf("子进程%d:\"我还活着!!!\"\n", getpid());
            sleep(1);
        }
    }

    if (pid > 0)
    {
        // 5秒后结束子进程
        printf("父进程%d:\"给你活5秒\"\n", getpid());
        for (int i = 1; i < 5; i++)
        {
            printf("父进程%d:\"你还能再活%d秒\"\n", getpid(), i);
            sleep(1);
        }
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}
