#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// 产品节点
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 定义头节点
Node *head = NULL;
// 定义信号量
sem_t producerSem; // 生产者
sem_t consumerSem; // 消费者
// 全局定义互斥锁
pthread_mutex_t mutex;

// 生产者线程
void *producerFun(void *arg)
{
    // 设置随机数种子
    srandom(getpid());
    // 获取线程编号
    int index = (int)(long)arg;

    // 循环生成商品并放置到商品列表并通知消费者
    while (1)
    {

        // 申请资源，信号量(可生产产品数)减1
        sem_wait(&producerSem);

        // 生成商品
        Node *node = (Node *)malloc(sizeof(Node));

        if (node == NULL)
        {
            printf("malloc error\n");
        }
        node->data = random() % 100 + 1; // 随机生成1~100的值作为值
        printf("生产者线程%d生产:%d\n", index, node->data);
        if (head == NULL)
        {
            node->next = NULL;
            // 这里因为head是全局变量，无需return,单独写一定要返回
            head = node;
        }
        else
        {
            node->next = head;
            head = node;
        }

        // 添加可消费产品量(对消费者信息量进行V操作)
        sem_post(&consumerSem);

        // 稍稍睡一下
        sleep(rand() % 3 + 1);
    }
}
// 消费者线程
void *ConsumerFun(void *arg)
{
    // 获取线程编号
    int index = (int)(long)arg;

    // 这个放在线程外，放置出现双重free的问题
    Node *temp = NULL;
    while (1)
    {
        // 申请资源(消费产品)
        sem_wait(&consumerSem);

        //加锁
        pthread_mutex_lock(&mutex);
        
        // 消费者消费商品
        temp = head; // 临时变量记录头节点，用以释放头节点

        // 让头节点指向下一个节点
        head = head->next;

        //解锁
        pthread_mutex_unlock(&mutex);

        printf("消费者线程%d消费:%d\n", index, temp->data);
        // 释放头节点
        free(temp);

        // 对生产者线程进行V操作(增加生产者信号量(可生产产品容器的量)，让生产者生产产品)
        sem_post(&producerSem);

        // 稍稍睡一下
        sleep(rand() % 3 + 1);
    }
}

int main(int argc, char const *argv[])
{
    // 初始化线程
    pthread_t pt[6];

    // 初始化信号量
    sem_init(&producerSem, 0, 4); // 生产者,可生产产品量为4
    sem_init(&consumerSem, 0, 0); // 消费者，可消费产品数默认为0

    //初始化互斥锁
    pthread_mutex_init(&mutex,NULL);

    for (int i = 0; i < 6; i++)
    {
        if (i < 2)
        {
            // 生产者线程
            pthread_create(&pt[i], NULL, producerFun, (void *)(long)i);
        }
        else
        {
            // 消费者线程
            pthread_create(&pt[i], NULL, ConsumerFun, (void *)(long)i);
        }
    }

    // 释放线程资源
    for (int i = 0; i < 6; i++)
    {
        pthread_join(pt[i], NULL);
    }

    // 释放互斥锁资源
    pthread_mutex_destroy(&mutex);

    return 0;
}
