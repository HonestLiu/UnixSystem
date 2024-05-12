//
// Created by honestliu on 24-4-14.
//
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
创建一个线程，对其进行线程分离，当其结束后让系统去释放它的资源
 */
void *fun(void *arg) {
    static int num = 0;
    for (; num < 2; ++num) {
        printf("线程运行中:%d\n", num);
        sleep(1);
    }
    //这个的结果会被join函数接收，但这里不涉及，因为它分离了
    return &num;
}

int main() {

    pthread_t pt = pthread_self();
    memset(&pt, 0, sizeof(pt));

    int ret = pthread_create(&pt, NULL, fun, NULL);
    if (ret != 0) {
        printf("pthread_create error\n");
        return 1;
    }

    //对线程pt进行线程分离
    pthread_detach(pt);

    //测试使用join释放分离的线程会不会报错
    /* ret = pthread_join(pt, NULL);
     if (ret != 0) {
         printf("pthread_join error\n");
     }*/

    printf("按下任意键结束主线程\n");

    getchar();
    return 0;
}
