#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> //需要使用memset函数格式化字符串
#define SIZE 1024

int main(int argc, char const *argv[])
{
    // 用于接收映射文件的内存地址
    void *addr = NULL;
    // 1.以读写的方式打开一个文件
    int fd = open("test.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    // 2.将文件映射到内存
    addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }
    printf("文件映射成功\n");

    // 3.关闭文件
    close(fd);

    // 4.通过内存写文件
    char str[] = "helloworld";
    memcpy(addr, str, sizeof(str) + 1);
    // 5.断开存储映射
    munmap(addr, 1024);
    return 0;
}
