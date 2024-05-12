#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    /* 创建匿名存储映射区 */
    void *add = NULL;
    add = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (add == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }

    /* 创建子进程 */
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        munmap(add, 1024);
        return 1;
    }

    if (pid == 0) // 子进程
    {
        // 写数据到匿名存储映射区
        char str[] = "你好啊！张三";
        memcpy(add, str, strlen(str));
    }
    else // 父进程
    {
        wait(NULL);
        // 从匿名存储映射区中读数据
        printf("读取到数据:%s\n", (char *)add);
    }

    /* 释放匿名存储映射区 */
    munmap(add, 1024);

    return 0;
}