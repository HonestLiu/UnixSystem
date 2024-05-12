## 生产者消费者条件变量模型

**产品放置:**使用链表存储生产者生产的产品
**生产者:**生产者生产产品后放置到链表上，并发出信号通知消费者消费产品
**消费者:**消费者会先看链表上有没有产品，没有就会`pthread_coin_wait`阻塞等待，直到生产者发送信号为止
![](https://honescos.oss-cn-hangzhou.aliyuncs.com/img/1713279796003-7913cdba-dabf-465a-8625-bfd102c882b9.jpegwYuQxDVbQ320240417154779348c0dd9c0a141.jpeg)

```c
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// 产品节点
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 创建互斥锁
pthread_mutex_t mutex;
// 创建条件变量
pthread_cond_t cond;
// 定义头节点
Node *head = NULL;

// 生产者线程
void *producerFun(void *arg)
{
    // 设置随机数种子
    srandom(getpid());

    // 循环生成商品并放置到商品列表并通知消费者
    while (1)
    {
        // 加锁
        pthread_mutex_lock(&mutex);

        // 生成商品
        Node *node = (Node *)malloc(sizeof(Node));
        if (node == NULL)
        {
            printf("malloc error\n");
        }
        node->data = random() % 100 + 1; // 随机生成1~100的值作为值
        printf("生产者生产:%d\n", node->data);
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
        // 解锁
        pthread_mutex_unlock(&mutex);

        // 通知消费者消费商品
        pthread_cond_signal(&cond);

        // 稍稍睡一下
        sleep(rand() % 3);
    }
}
// 消费者线程
void *ConsumerFun(void *arg)
{
    while (1)
    {
        // 加互斥锁
        pthread_mutex_lock(&mutex);
        while (head == NULL)
        {
            // 如果产品列表为空，则阻塞等待生成者生成商品
            pthread_cond_wait(&cond, &mutex);
        }
        // 消费者消费商品
        Node *temp = head; // 临时变量记录头节点，用以释放头节点
        printf("消费者消费:%d\n", temp->data);
        // 让头节点指向下一个节点
        head = head->next;
        // 释放头节点
        free(temp);
        // 解互斥锁
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char const *argv[])
{
    // 初始化线程
    pthread_t producer = pthread_self(); // 生产者
    pthread_t consumer = pthread_self(); // 消费者
    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);
    // 初始化条件变量
    pthread_cond_init(&cond, NULL);

    // 创建线程
    pthread_create(&producer, NULL, producerFun, NULL);
    pthread_create(&consumer, NULL, ConsumerFun, NULL);

    // 释放线程资源
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    // 释放条件变量
    pthread_cond_destroy(&cond);
    // 释放互斥锁资源
    pthread_mutex_destroy(&mutex);

    return 0;
}
```

