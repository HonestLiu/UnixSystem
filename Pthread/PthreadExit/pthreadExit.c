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
    //使用pthread_exit退出线程
    pthread_exit(NULL);
    //return &num;
}

int main() {

    pthread_t pt = pthread_self();
    memset(&pt, 0, sizeof(pt));
    int ret = pthread_create(&pt, NULL, fun, NULL);
    if (ret != 0) {
        printf("pthread_create error\n");
        return 1;
    }

    printf("按下任意键结束主线程\n");

    getchar();
    return 0;
}
