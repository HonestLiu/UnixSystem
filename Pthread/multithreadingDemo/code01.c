#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* 线程参数结构体
    - 当需要给线程传递的参数大于2个时，就需要定义结构体来传递参数
 */
typedef struct Msg
{
    char taskName[32];
    int time;
} Msg;

void *fun(void *arg)
{
    // 先强转成原指针，再取地址，最后新建一个参数变量接收(避免多次线程创建参数变量被覆盖)
    Msg msg = *(Msg *)arg;

    printf("线程名:%s\n", msg.taskName);

    for (int i = 0; i < msg.time; ++i)
    {
        printf("%s:运行中:%d\n", msg.taskName, i);
        sleep(1);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    // 线程号
    pthread_t pt = pthread_self();

    while (1)
    {
        // 初始化参数结构体
        Msg msg;

        // 从标准输入读取线程名
        printf("请输入要创建的线程名:");
        fgets(msg.taskName, sizeof(msg.taskName), stdin);
        printf("%s\n", msg.taskName);
        printf("\n");
        // 去除读入线程名后的回车-让最后一个字符等于0即可
        msg.taskName[strlen(msg.taskName) - 1] = 0;
        // 读入任务执行的次数
        printf("请输入任务执行的时间:");
        scanf("%d", &msg.time);
        getchar();
        // 创建线程
        pthread_create(&pt, NULL, fun, (void *)&msg);
        // 线程分离
        pthread_detach(pt);
    }

    return 0;
}
