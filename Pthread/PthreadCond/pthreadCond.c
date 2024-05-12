#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
设置两个线程，线程A每隔3秒唤醒一次线程B执行任务
 */

// 创建全局变量
int flag = 0;
// 创建条件变量
pthread_cond_t pct;
// 创建互斥锁变量
pthread_mutex_t pmt;

void *FunA(void *arg)
{
    while (1)
    {
        // 加锁
        pthread_mutex_lock(&pmt);
        // 修改全局变量
        flag = 1;
        // 解锁
        pthread_mutex_unlock(&pmt);
        // 发送条件信号
        pthread_cond_signal(&pct);

        // 睡眠
        sleep(2);
    }
    return NULL;
}
void *FunB(void *arg)
{
    while (1)
    {
        //使用pthread_cond_wait前需要确保互斥锁已经上锁
        pthread_mutex_lock(&pmt);

        // 在使用条件变量时，通常都会结合一个互斥锁和条件判断来使用，以确保在满足条件之前线程不会提前返回。
        if (flag == 0)
        {
            //未满足等待条件，线程会暂时休眠，互斥锁也会被解锁
            pthread_cond_wait(&pct, &pmt);
            //满足等待条件，线程解除休眠继续运行，互斥锁重新上锁
        }

        printf("线程B满足条件运行...\n");
        // 修改全局变量为0
        flag = 0;
        pthread_mutex_unlock(&pmt);
    }

    return NULL;
}

int main(int argc, char const *argv[])
{
    /* 创建变量 */

    // 创建线程变量
    pthread_t pt1;
    pthread_t pt2;
    int res = -1;

    /* 创建/初始化资源 */

    // 初始化条件变量
    res = pthread_cond_init(&pct, NULL);
    if (res != 0)
    {
        printf("pthread_mutex_init_error\n");
    }

    // 初始化互斥锁
    res = pthread_mutex_init(&pmt, NULL);
    if (res != 0)
    {
        printf("pthread_mutex_init_error\n");
    }
    // 创建线程
    res = pthread_create(&pt1, NULL, FunA, NULL);
    if (res != 0)
    {
        printf("pthread_create error\n");
    }
    res = pthread_create(&pt2, NULL, FunB, NULL);
    if (res != 0)
    {
        printf("pthread_create error\n");
    }

    /* 释放资源 */

    // 释放线程资源
    pthread_join(pt1, NULL);
    pthread_join(pt2, NULL);
    // 释放互斥锁资源
    pthread_mutex_destroy(&pmt);
    // 释放条件变量
    pthread_cond_destroy(&pct);

    return 0;
}
