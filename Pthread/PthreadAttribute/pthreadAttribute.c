#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *fun(void *arg)
{
    for (int i = 0; i < 4; ++i)
    {
        printf("子线程运行中:%d\n", i);
        sleep(1);
    }
    return NULL;
}

int main()
{
    // 定义属性结构体变量
    pthread_attr_t attr;
    // 定义线程号
    pthread_t pt = pthread_self();

    // 初始化结构体变量
    pthread_attr_init(&attr);

    // 为结构属性设置线程分离
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // 使用指定的属性创建线程
    int ret = pthread_create(&pt, &attr, fun, NULL);
    if (ret != 0)
    {
        printf("pthread_create error\n");
        return 1;
    }

    // 销毁属性结构体变量(必须的⭐)
    pthread_attr_destroy(&attr);

    // 使用join释放线程资源
    ret = pthread_join(pt, NULL);
    if (ret != 0)
    {
        printf("pthread_join error\n");
    }

    printf("按下任意键退出\n");
    getchar();
}