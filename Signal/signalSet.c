#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/* 创建一个信号集并往集合中添加信号 */
int main(int argc, char const *argv[])
{
    
    sigset_t set;


    // 清空新申请的信号集，保证干净
    sigemptyset(&set);

    // 将SIGINT 加入set集合
    sigaddset(&set, SIGINT);
    // 将SIGISTP 加入set集合
    sigaddset(&set, SIGTSTP);

    if (sigismember(&set, SIGINT))
    {
        printf("信号SIGINT在集合中\n");
    }

    return 0;
}
