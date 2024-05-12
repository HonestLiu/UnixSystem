#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    /* 创建信号集合 */
    // 创建信号集
    sigset_t set1;
    // 清空新建信号集(初始化)
    sigemptyset(&set1);
    // 将SIGINT信号加入信号集
    sigaddset(&set1, SIGINT);

    /* 将信号集设置为阻塞集合(采用SIG_BLOCK的方式设置) */
    sigprocmask(SIG_BLOCK, &set1, NULL);
    printf("阻塞SIG_BLOCK信号5秒\n");
    sleep(5);

    /* 查看未决信号集 */
    // 创建信号集(接收未决信号集)
    sigset_t set2;
    // 获取进程中的未决信号集
    sigpending(&set2);
    //判断SIG_BLOCK是否在未决信号集中(在阻塞集阻塞期间键入Ctrl + C这里就能获取到它)
    if (sigismember(&set2, SIG_BLOCK))
    {
        printf("\n");
        printf("信号SIG_BLOCK在未决信号集中\n");
    }

    // 从阻塞集中移除SIG_BLOCK
    sigprocmask(SIG_UNBLOCK, &set1, NULL);

    return 0;
}
