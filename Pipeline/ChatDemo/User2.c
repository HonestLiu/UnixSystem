#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> //需要使用memset函数格式化字符串
#define SIZE 1024

/*
需要同时具备读和写的能力，故需要两个管道
一个管道循环读信息                      |
一个管道循环等待用户输入并写入到管道中    |  ----> 两个动作不能同时在一个进程中运行，所以需要多进程 --> 主进程负责监听输入并写入，子进程负责循环读数据
 */

/*
约定:
    - fifo1：用于User1读，User2写
    - fifo2: 用于User1写，User2读

 */

int main(int argc, char const *argv[])
{
    // 创建一个子进程，负责循环读取数据
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    /* 分进程处理业务 */

    // 子进程
    if (pid == 0)
    {
        char buf[SIZE];
        int res = -1;
        // 以只读的形式打开有名管道文件fifo2
        int fd = open("fifo2", O_RDONLY);
        if (fd == -1)
        {
            perror("open");
        }

        while (1)
        {
            // 对字符串进行置0操作
            memset(buf, 0, SIZE);
            res = read(fd, buf, SIZE);
            if (res <= 0)
            {
                perror("对方已断开");
                break;
            }
            printf("收到User1的信息:%s\n", buf);
            printf("请输入要发送的信息:\n");
        }
        //关闭有名管道
        close(fd);
    }
    else // 父进程
    {
        char buf[SIZE];
        int res1 = -1;
        int res2 = -1;
        // 以只写的形式打开有名管道文件fifo1
        int fd = open("fifo1", O_WRONLY);
        if (fd == -1)
        {
            perror("open");
        }
        while (1)
        {
            // 对字符串进行置0操作
            memset(buf, 0, SIZE);
            //从标准输入读取用户的输入值
            printf("请输入要发送的信息:\n");
            res1 = read(0,buf,SIZE);
            if (res1 <= 0)
            {
                perror("read2");
                break;
            }

            //去除最后的换行符
            if (buf[strlen(buf) - 1] == '\n')
            {
                buf[strlen(buf) - 1] = '\0';
            }

            //将读取的用户输入信息输出到管道
            res2 = write(fd, buf, strlen(buf));
            if (res2 <= 0)
            {
                perror("write");
                break;
            }
        }
        //关闭有名管道
        close(fd);
    }

    return 0;
}
