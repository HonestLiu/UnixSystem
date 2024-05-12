#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 使用dup复制标准输入文件描述符1
    int fd = dup(1);
    // 打印复制描述符所在位图的位置
    printf("当前描述符的位置:%d\n", fd);
    // 使用复制的文件描述符输出信息到控制台
    char *str = "helloDup\n";
    write(fd, str, sizeof(str) + 1);

    /// 关闭复制的文件描述符
    close(fd);
    return 0;
}
