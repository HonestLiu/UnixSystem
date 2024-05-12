#include <pthread.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    /* 每一个进程都至少包含一个线程，所以可以直接从当前进程获取线程 */

    // 获取线程号
    pthread_t pt1 = pthread_self();
    printf("pt1:%lu\n", pt1);
    pthread_t pt2 = pthread_self();
    printf("pt2:%lu\n", pt2);

    // 比较两个线程号是否相等,相等非0值
    if (pthread_equal(pt1, pt2) != 0)
    {
        printf("两个线程ID相等\n");
    }
    else
    {
        printf("两个线程ID不相等\n");
    }

    return 0;
}
