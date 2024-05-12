#include <unistd.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
    //创建存放管道文件描述符的整形数组
    int pipefd[2];

    //使用pipe函数创建无名管道
    int res = pipe(pipefd);
    if (res == -1)
    {
        //创建管道失败
        perror("pipe");
        return 1;
    }

    printf("读管道为:%d,写管道为:%d\n",pipefd[0],pipefd[1]);

    //获取管道缓冲区的大小并打印
    printf("读管道缓冲区的大小为:%ld\n",fpathconf(pipefd[0], _PC_PIPE_BUF));
    printf("写管道缓冲区的大小为:%ld\n",fpathconf(pipefd[1], _PC_PIPE_BUF));


    //关闭管道描述符(尽管进程结束会自动关闭，但建议还是手动关闭)
    close(pipefd[0]);
    close(pipefd[1]);


    
    return 0;
}
