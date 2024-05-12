#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 用于读写的全局变量
int num = 0;
// 读写锁指针
pthread_rwlock_t rwlock;

// 读线程
void *readFun(void *arg)
{

    int id = (int)(long)arg;
    while (1)
    {
        // 加读锁
        pthread_rwlock_rdlock(&rwlock);

        printf("读线程:%d 读得num的值为:%d\n", id, num);

        // 解读锁头
        pthread_rwlock_unlock(&rwlock);
        // 随机随眠1~3秒
        sleep(random() % 3 + 1);
    }
}
// 写线程
void *writeFun(void *arg)
{
    int id = (int)(long)arg;
    while (1)
    {
        // 加写锁
        pthread_rwlock_wrlock(&rwlock);
        num++;
        printf("写线程:%d 修改num的值为:%d\n", id, num);

        // 解写锁
        pthread_rwlock_unlock(&rwlock);
        // 随机随眠1~3秒
        sleep(random() % 3 + 1);
    }
}

int main(int argc, char const *argv[])
{
    // 设置随机种子
    srandom(getpid());
    int ret = -1;

    // 初始化读写锁
    ret = pthread_rwlock_init(&rwlock, NULL);

    if (ret != 0)
    {
        printf("初始化读写锁失败\n");
    }

    /* 创建8个线程，前5个读线程，后3个写线程 */
    pthread_t pthreadId[8];

    for (int i = 0; i < 8; i++)
    {
        if (i < 5)
        {
            pthread_create(&pthreadId[i], NULL, readFun, (void *)(long)i);
        }
        else
        {
            pthread_create(&pthreadId[i], NULL, writeFun, (void *)(long)i);
        }
    }

    // 释放线程资源
    for (int i = 0; i < 8; i++)
    {
        pthread_join(pthreadId[i], NULL);
    }

    // 销毁读写锁
    pthread_rwlock_destroy(&rwlock);

    return 0;
}
