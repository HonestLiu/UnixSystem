#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>

void fun(int sig){
    printf("触发信号sig:%d\n",sig);
}

int main(int argc, char const *argv[])
{
    /*设置时间结构体*/
    struct itimerval tv;

    // 设置第一次运行要经过的时间(触发时间)
    tv.it_value.tv_sec = 5;  // 秒
    tv.it_value.tv_usec = 0; // 微秒(必须设置)

    // 设置周期执行时间(触发周期)
    tv.it_interval.tv_sec = 2;  // 秒
    tv.it_interval.tv_usec = 0; // 微秒

    // 注册信号，让定时器发出的SIGALRM(自然计时法)后，使用自定义函数处理该信号
    signal(SIGALRM,fun);

    /*注册定时器*/
    setitimer(ITIMER_REAL, &tv, NULL);

    /*稍作阻塞*/
    getchar();
    

    return 0;
}
