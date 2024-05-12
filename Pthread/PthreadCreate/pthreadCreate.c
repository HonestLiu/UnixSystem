#include <pthread.h>
#include <stdio.h>
#include <string.h>

// 线程函数1
void *fun1(void *arg)
{
    printf("pt1的线程ID的值为:%lu\n", pthread_self());
    return NULL;
}
void *fun2(void *arg)
{
    // 进行两次强转，对传入的参数的进行解引用
    int res = (int)(long)arg;
    printf("线程2的ID为:%lu,arg的值为:%d\n", pthread_self(), res);
    return NULL;
}

int main(int argc, char const *argv[])
{

    // 创建线程
    pthread_t pt1 = -1;
    pthread_t pt2 = -1;

    // 无参线程
    int ret = pthread_create(&pt1, NULL, fun1, NULL);
    if (ret != 0)
    {
        printf("error number: %d\n", ret);
        // 根据错误号打印错误信息
        printf("error information: %s\n", strerror(ret));
    }

    // 有参线程              (需要将传入的参数先强转成void *)
    pthread_create(&pt2, NULL, fun2, (void *)11);

    printf("main线程的ID为:%lu\n", pthread_self());

    // 阻塞进程，不让进程结束，保证新建线程的运行
    printf("按任意键结束\n");
    getchar();

    return 0;
}
