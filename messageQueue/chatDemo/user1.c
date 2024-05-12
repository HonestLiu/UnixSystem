#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

typedef struct msgbuf
{
    long mtype;        // 消息类型
    char sendUser[64]; // 消息发送者
    char mtext[128];   // 消息内容
} MSG;

int main(int argc, char const *argv[])
{
    // 获取唯一的key
    key_t key = ftok("/", 2024);
    if (key == -1)
    {
        perror("ftok error");
        return 1;
    }

    // 本系统现有用户
    char *userAry[] = {"yiyi", "lisi", "zhangsan"};

    // 本次会话的用户名
    char userName[32];
    // 本次会话用户的ID
    int userId = 0;

    while (userId == 0)
    {
        printf("请输入你的用户名:\n");
        scanf("%s", userName);

        // 遍历数组找到它的ID
        for (int i = 0; i < 3; i++)
        {
            if (strcmp(userAry[i], userName) == 0)
            {
                userId = (i + 1);
                printf("本次会话的ID为:%d\n", userId);
                break;
            }
        }
        if (userId == 0)
        {
            printf("你输入的用户名错误，请重新输入\n");
        }
    }

    // 创建消息队列
    int msqid = msgget(key, IPC_CREAT);
    if (msqid == -1)
    {
        perror("msgget");
        return 1;
    }

    // 开启子进程
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0) // 子进程
    {
        // 循环获取消息队列中的信息
        MSG msg;
        while (1)
        {
            int res = msgrcv(msqid, &msg, sizeof(MSG) - sizeof(long), userId, 0);
            if (res == -1)
            {
                perror("msgrcv");
                return 1;
            }

            printf("%s发来:%s\n", msg.sendUser, msg.mtext);
            printf("请输入你要发送的信息:\n");
        }
    }
    else // 父进程
    {
        while (1)
        {
            char msgText[128];
            char sendUser[32];
            int sendId = 0;
            printf("请输入你要发送的信息:\n");
            scanf("%s", msgText);
            while (sendId == 0)
            {
                printf("请输入你要发送的目标:\n");
                scanf("%s", sendUser);
                for (int i = 0; i < 3; i++)
                {
                    if (strcmp(sendUser, userAry[i]) == 0)
                    {
                        sendId = (i + 1);
                        break;
                    }
                }
                if (sendId == 0)
                {
                    printf("你输入的用户名错误，请重新输入\n");
                }
            }

            MSG msg;
            msg.mtype = sendId;
            strcpy(msg.mtext, msgText);
            strcpy(msg.sendUser, userName);
            // 发送消息
            int res = msgsnd(msqid, &msg, sizeof(msg) - sizeof(long), 0);
            if (res == -1)
            {
                perror("msgsnd");
                return 1;
            }
        }
    }

    return 0;
}
