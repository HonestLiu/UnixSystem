#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
创建一个子进程并
- 正常终止
- 异常终止
创建一个函数，传入stat指针，判断终止的类型
 */

/* 等待子进程终止的函数 */
void pr_exit(int stat)
{
    // 判断是否为正常终止
    if (WIFEXITED(stat))
    {
        printf("子进程是正常终止的\n");
    }

    //判断是否为异常终止
    if (WIFSIGNALED(stat))
    {
        printf("子进程是异常终止的\n");
    }
    
    
}

int main()
{

    // 使用fork创建第一个子进程
    pid_t first_pid = fork();
    // 判断是否创建失败
    if (first_pid < 0)
    {
        perror("create");
    }
    else if (first_pid == 0)
    {
        // 结束子进程
        printf("子进程:%d结束\n", getpid());
        _exit(7); // 模拟正常结束
    }
    int stat1;
    if (wait(&stat1) != first_pid)
    {
        // 如果没有返回关闭的子进程的PID，则代表出现错误
        perror("wait");
    }
    else
    {
        // 否则，传入stat给pr_exit函数判断终止类型
        pr_exit(stat1);
    }

    //----------------------------------------------------------------

    // 创建第二个子进程
    pid_t second_pid = fork();
    // 判断是否创建失败
    if (second_pid < 0)
    {
        perror("create");
    }
    else if (second_pid == 0)
    {
        // 结束子进程
        printf("子进程:%d结束\n", getpid());
        abort(); // 模拟异常结束
    }

    int stat2;
    if (wait(&stat2) != second_pid)
    {
        // 如果没有返回关闭的子进程的PID，则代表出现错误
        perror("wait");
    }
    else
    {
        // 否则，传入stat给pr_exit函数判断终止类型
        pr_exit(stat2);
    }
}