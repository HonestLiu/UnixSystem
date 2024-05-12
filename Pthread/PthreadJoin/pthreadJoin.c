//
// Created by honestliu on 24-4-14.
//
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
创建一个线程，运行一段时间后，再使用pthread_join函数释放它的资源(它是阻塞的)
 */
void *fun(void *arg) {
    static int num = 0;
    for ( ; num < 2; ++num) {
        printf("线程运行中:%d\n", num);
        sleep(1);
    }
    return &num;
}

int main(int argc, char const *argv[]) {

    pthread_t pt = pthread_self();
    memset(&pt, 0, sizeof(pt));
    //存储退出返回值的变量
    void *rest = NULL;

    int ret = pthread_create(&pt, NULL, fun, NULL);
    if (ret != 0) {
        printf("pthread_create error\n");
        return 1;
    }

    //阻塞等待释放线程资源
    ret = pthread_join(pt, &rest);
    if (ret != 0) {
        printf("pthread_join error\n");
        return 1;
    } else {
        printf("线程资源释放，释放状态为:%d\n", *((int *) rest));//2
    }
    printf("主线程退出\n");

    return 0;
}
