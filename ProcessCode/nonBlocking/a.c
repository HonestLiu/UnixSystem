/* 导入write和read函数的头文件 */
#include <unistd.h>
/* 导入open函数的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* 导入C标准库 */
#include <stdio.h>
#include <stdlib.h>

/* 默认阻塞 */
void test01()
{
    int fd = open("/dev/tty", O_RDONLY);
    if (fd == 0)
    {
        perror("open");
    }
    // 使用read读取fd的值
    unsigned char buf[128];
    read(fd, buf, sizeof(buf));
    printf("读取到的内容是:%s\n", buf); // 默认是阻塞的
    close(fd);
}

/* 通过open设置不阻塞--文件描述符不存在 */
void test02()
{
    int fd = open("/dev/tty", O_RDONLY | O_NONBLOCK); // 使用 `|` 符号在原属性的基础上加上非阻塞属性即可
    if (fd == 0)
    {
        perror("open");
    }
    // 使用read读取fd的值
    unsigned char buf[128];
    read(fd, buf, sizeof(buf));
    printf("读取到的内容是:%s\n", buf); // 不阻塞了
    close(fd);
}

/* 使用fcntl设置不阻塞--文件描述符存在 */
void fcntlTest()
{
    // 获取标准输入(已存在的文件描述符)的文件状态标记
    int flag = fcntl(0, F_GETFL);
    // 修改文件标记状态为非阻塞
    flag = flag | O_NONBLOCK;
    // 将修改后的文件状态标记设置回文件描述符内
    fcntl(0, F_SETFL, flag);

    printf("准备读取数据........\n");
    unsigned char buf[128];
    read(0, buf, sizeof(buf));
    printf("读取到的内容是:%s\n", buf); 
}

int main()
{
    fcntlTest();
    //test02();
}