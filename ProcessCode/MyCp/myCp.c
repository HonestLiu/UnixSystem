/* 导入write和read函数的头文件 */
#include <unistd.h>
/* 导入open函数的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* 导入C标准库 */
#include <stdio.h>
#include <stdlib.h>

/*
目的:使用函数实现cp命令 ./a.out b.txt test (cp b.txt test)
 */

/*
argc：传入参数的个数
argv: 记录所有传入参数的数组，可通过索引访问
    ./a.out b.txt test
      [0]   [1]   [2]
 */
int main(int argc, char const *argv[])
{
    /* 判断传入参数是否正确(3个参数) */
    if (argc < 3)
    {
        printf("请正确的传入参数");
        return 0; // 直接退出
    }

    /* 打开要拷贝的源文件 */
    // 以只读的方式打开b.txt
    int fd_r = open(argv[1], O_RDONLY);
    // 检查是否打开失败
    if (fd_r < 0)
    {
        perror("open");
        return 0;
    }
    /* 以只写的方式打开目标文件，并附加没有就创建的参数 */
    // 拼接目标文件的路径
    char fileUrl[128] = "";
    sprintf(fileUrl, "%s/%s", argv[2], argv[1]); // test/b.txt
    int fd_wc = open(fileUrl, O_WRONLY | O_CREAT, 0666);
    // 判断是否打开
    if (fd_wc < 0)
    {
        perror("open");
        return 0;
    }

    /* 读取源文件并写入目标文件中 */
    while (1)
    {
        unsigned char buf[128] = ""; // 在循环内定义数组，每次都重新创建保证结束数组的干净
        int rleght = read(fd_r, buf, sizeof(buf));
        write(fd_wc, buf, sizeof(buf));
        if (rleght < sizeof(buf))
        {
            break;
        }
    }

    close(fd_wc);
    close(fd_r);
    return 0;
}
