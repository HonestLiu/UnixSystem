#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>

/* 消息结构体 */
struct msgbuf
{
    long mtype;
    char sendUser[64];
    char mtext[128];
};

int main(int argc, char const *argv[])
{
    /*生成唯一的key值*/
    key_t key = ftok("/", 2024);

    /*创建消息队列*/
    int muqid = msgget(key, IPC_CREAT);
    if (muqid == -1)
    {
        perror("msgget");
        return 1;
    }

    /* 向消息队列发送消息 */

    // 创建消息结构体
    struct msgbuf msg;
    msg.mtype = 10;
    strcpy(msg.sendUser, "zhangSan");
    strcpy(msg.mtext, "Hello,My Name is zhangSan");

    int res = msgsnd(muqid, &msg, sizeof(msg) - sizeof(long), 0);
    if (res == -1)
    {
        perror("msgsnd");
        return 1;
    }

    return 0;
}
