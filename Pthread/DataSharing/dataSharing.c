#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
验证数据区、堆区数据共享
 */
// 数据区数据
int num = 100;

/* 线程函数 */
// 在线程内修改进程的数据，看是否会影响到进程中的数据，进而证明二者是否共享的
void *dataSharing(void *data)
{
    // 将传入的堆区数据进行转换
    int *heap = (int *)data;

    // 访问数据区数据num
    printf("修改之前的num值为:%d,*heap的值为:%d\n", num, *heap);
    // 对数据进行修改
    num++;
    (*heap)++;
    printf("修改之后的num值为:%d,*heap的值为:%d\n", num, *heap);
    return NULL;
}

int main(int argc, char const *argv[])
{

    // 定义线程ID
    pthread_t pt1;
    // 初始化线程ID，为保证可移植性，使用memset进行初始化
    memset(&pt1, 0, sizeof(pt1));

    // 定义堆区-验证堆区数据共享
    void *data = calloc(1, sizeof(int));
    if (data == NULL)
    {
        perror("calloc");
        return 1;
    }
    memset(data, 0, sizeof(int));

    // 创建子进程
    int res = pthread_create(&pt1, NULL, dataSharing, data);
    if (res != 0)
    {
        printf("pthread_create\n");
        return 1;
    }

    // 在进程中打印数据区的数据，验证线程的修改是否作用到了进程数据区
    sleep(1);
    printf("进程的数据区数据为:%d,堆区数据为:%d\n", num, *((int *)data));

    //释放堆区数据
    free(data);

    // 阻塞，避免进程结束
    printf("输入任意键退出\n");
    getchar();

    return 0;
}
