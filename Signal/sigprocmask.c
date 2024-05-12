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

    //将set信号集设置为阻塞集
    sigprocmask(SIG_BLOCK,&set,NULL);

    sleep(5);//在这5秒内发生的SIGINT信号都会被临时阻塞，不会被处理

    //5秒后从信号阻塞集合中删除 set 信号集，SIGINT开始被处理
    sigprocmask(SIG_UNBLOCK,&set,NULL);

    return 0;
}
