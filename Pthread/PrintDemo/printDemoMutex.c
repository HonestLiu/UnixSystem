#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
 * 创建两个线程，一个打印小写字母，一个打印大写字母 到控制台
 * */
// 定义互斥锁变量
pthread_mutex_t mutex;

// 打印小写字母到控制台
void *fun1(void *arg)
{
    // 互斥锁加锁
    pthread_mutex_lock(&mutex);

    for (int i = 'a'; i < 'z'; ++i)
    {
        // 等同于putc(c, stdout)，将int转换成char并通过标准输出输出到控制台
        putchar(i);
        // 刷新缓冲区
        fflush(stdout);
        // 等待，以以微秒为间隔的sleep
        usleep(1000000);
    }
    printf("\n");
    // 互斥锁解锁
    pthread_mutex_unlock(&mutex);

    return NULL;
}
// 打印大写字母到控制台
void *fun2(void *arg)
{
    // 互斥锁加锁
    pthread_mutex_lock(&mutex);

    for (int i = 'A'; i < 'Z'; ++i)
    {
        // 等同于putc(c, stdout)，将int转换成char并通过标准输出输出到控制台
        putchar(i);
        // 刷新缓冲区
        fflush(stdout);
        // 等待，以以微秒为间隔的sleep
        usleep(1000000);
    }
    printf("\n");
    // 互斥锁解锁
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    // 初始化互斥锁
    int res = pthread_mutex_init(&mutex, NULL);
    if (res != 0)
    {
        printf("pthread_mutex_init_error\n");
    }
    else
    {
        printf("初始化互斥锁成功\n");
    }

    // 线程变量
    pthread_t pt1 = pthread_self();
    pthread_t pt2 = pthread_self();

    memset(&pt1, 0, sizeof(pt1));
    memset(&pt2, 0, sizeof(pt2));

    // 创建线程
    res = pthread_create(&pt1, NULL, fun1, NULL);
    if (res != 0)
    {
        printf("pthread_create error\n");
    }
    res = pthread_create(&pt2, NULL, fun2, NULL);
    if (res != 0)
    {
        printf("pthread_create error\n");
    }


    // 阻塞等待线程结束并结束它
    pthread_join(pt1, NULL);
    pthread_join(pt2, NULL);

    printf("\n线程释放完毕，main线程退出\n");
    
    //销毁互斥锁
    res = pthread_mutex_destroy(&mutex);
    if (res != 0)
    {
        printf("互斥锁销毁失败\n");
    }else{
        printf("互斥锁销毁成功\n");
    }


    return 0;
}