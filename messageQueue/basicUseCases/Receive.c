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

    /* 向消息队列接收消息 */

    // 接收消息结构体
    struct msgbuf msg;
    //接收消息类型为10的消息
    int res = msgrcv(muqid,&msg,sizeof(msg)-sizeof(long),10,0);
    if (res == -1)
    {
        perror("msgsnd");
        return 1;
    }
    printf("%s发送消息:%s\n",msg.sendUser,msg.mtext);

    return 0;
}
