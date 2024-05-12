#include <signal.h>
#include <stdio.h>

// 旧的信号处理函数
void oldFun(int sig)
{
    printf("捕获到信号:%d\n", sig);
}

// 新的信号处理函数
void newFun(int signum, siginfo_t *info, void *context)
{
    printf("捕获到信号:%d\n", signum);
}

int main(int argc, char const *argv[])
{
    // 接收sigaction函数返回值的变量
    int ret = -1;

#if 0
    /* 使用旧的信号处理函数指针 */

    // 创建sigaction结构体
    struct sigaction act;
    // 设置旧的信号处理函数
    act.sa_handler = oldFun;
    // 使用默认的处理方式
    act.sa_flags = 0;
#else
    /* 使用新的信号处理函数指针 */

    // 创建sigaction结构体
    struct sigaction act;
    // 设置新的信号处理函数
    act.sa_sigaction = newFun;
    // 设置使用新的信号处理函数处理信号
    act.sa_flags = SA_SIGINFO;

#endif
    // 信号注册
    ret = sigaction(SIGINT, &act, NULL);
    if (ret == -1)
    {
        perror("sigaction");
        return 1;
    }
    printf("....输入任意键继续...\n");

    while (1)
    {
        getchar();
    }

    return 0;
}
