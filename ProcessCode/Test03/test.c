#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>//read、write的头文件
/*open的头文件*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])//argc表示参数的个数 argv是记录参数的字符数组(和Java一样，这些是终端传入的)
{
    int fd = open("a.txt", O_RDONLY);//以只读的形式打开a.txt
    printf("%d\n",fd);//获取的文件描述符数
    char str[128] = "";//需要进行初始化
    read(fd,str,sizeof(str));
    printf("%s\n",str);//helloWold
    close(fd);
    return 0;
}
