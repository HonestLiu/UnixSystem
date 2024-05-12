#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> //需要使用memset函数格式化字符串
#define SIZE 128

int main(int argc, char const *argv[])
{
    int i = 0;
    int res = -1;
    char str[SIZE];

    /* 以只写的方式打开有名管道文件，获取文件描述符 */
    int fd = open("fifo", O_WRONLY);

    if (fd == -1)
    {
        perror("fopen");
        return 1;
    }
    /* 使用write函数向有名管道写出数据 */
    while (1)
    {
        // 格式化字符串
        memset(str, 0, SIZE);
        i++;
        snprintf(str, SIZE, "写出数据%d", i);
        res = write(fd, str, SIZE);
        if (res <= 0)
        {
            perror("write");
            break;
        }
        
        printf("写出:%s\n", str);
        //2秒写一次
        sleep(2);
    }

    /* 关闭有名管道 */
    close(fd);

    return 0;
}
