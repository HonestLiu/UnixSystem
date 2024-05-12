#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int res = -1;
    // 创建有名管道符
    res = mkfifo("fifo", 0644);
    if (res == -1)
    {
        perror("mkfifo");
        return 1;
    }

    if (access("fifo", F_OK) == 0)
    {
        printf("成功创建有名管道描述符\n");
    }

    return 0;
}
