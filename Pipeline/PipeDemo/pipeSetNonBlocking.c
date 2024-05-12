#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int res = -1;

    // 创建管道(必须在fork子进程之前创建)
    int pipefd[2];
    res = pipe(pipefd);
    if (res == -1)
    {
        perror("pipe");
        return -1;
    }

    // fork子进程
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return -1;
    }

    /* 管道通信:父进程读、子进程写 */

    // 子进程
    if (pid == 0)
    {
        // 关闭写文件描述符
        close(pipefd[1]);

        /* 设置读文件描述符非阻塞 */
        int flags = fcntl(pipefd[0], F_GETFD);
        flags = flags | O_NONBLOCK;
        fcntl(pipefd[0], F_SETFL, flags);

        // 从管道中读
        char buf[128];
        res = read(pipefd[0], buf, sizeof(buf));
        if (res < 0)
        {
            perror("read");
            _exit(-1);
        }
        printf("读到的字符是:%s\n", buf);
        // 关闭读文件描述符
        close(pipefd[0]);
        // 读完直接退出
        _exit(0);
    }
    else
    {
        // 父进程
        // 关闭读文件描述符
        close(pipefd[0]);

        /* 制造阻塞，让父进程随眠2秒 */
        sleep(2);

        // 往管道中写入数据
        char str[] = "HelloPipe";
        int len = write(pipefd[1], str, sizeof(str));
        printf("写出数据长度:%d\n", len);

        // 关闭写文件描述符
        close(pipefd[1]);
    }

    return 0;
}
