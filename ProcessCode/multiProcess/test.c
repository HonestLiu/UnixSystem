#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
//使用宏定义生成子进程的个数
#define Num 3

int main()
{
    pid_t pd;
    int i = 0; // ⭐即是循环创建的子进程的计数器，也是区分子进程的数字

    // 新建3个进程
    for (; i < Num; i++)
    {
        pd = fork();
        // 子进程代码是从fork后开始运行的，在此判断它是不是子进程，是的话直接退出for循环
        // 避免子进程再创建子进程
        if (pd == 0)
        {
            break;
        }
    }

    /* 判断进程
    每个i对应一个子进程，子进程拷贝了父进程的代码和数据，故i的值也是被拷贝的，而其在for循环会被直接break
    故i没有更新，所以i间接辨识了其是第几个进程
     */

    if (i == 0)// 第一个进程
    {
        // 执行任务A
        for (size_t j = 0; j < 2; j++)
        {
            printf("进程:%d,执行第%ld次任务\n", getpid(), j+1);
            sleep(2);
        }
    }
    else if (i == 1) // 第二个进程
    {
        // 执行任务B
        for (size_t j = 0; j < 2; j++)
        {
            printf("进程:%d,执行第%ld次任务\n", getpid(), j+1);
            sleep(2);
        }
    }
    else if (i == 2) // 第三个进程
    {
        // 执行任务C
        for (size_t j = 0; j < 2; j++)
        {
            printf("进程:%d,执行第%ld次任务\n", getpid(), j+1);
            sleep(2);
        }
    }
    else if (i == Num) // 父进程，只有父进程可以拥有循环的结束条件的i
    {
        /* 循环等待子进程结束并释放其资源 */
        while (1)
        {
            //使用waitpid并使用参数设置为不阻塞，其每检查到终止的子进程就会直接返回结果
            pid_t pid = waitpid(-1, NULL, WNOHANG);
            if (pid == 0)
            {
                // 没有子进程终止，退出本轮循环，继续监听
                continue;
            }
            else if (pid == -1)
            {
                // 所以子进程均终止，直接结束while循环，终止父进程
                break;
            }
            else if (pid > 0)
            {
                printf("子进程:%d退出\n", pid);
            }
        }
    }
}
