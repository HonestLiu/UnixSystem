#include <unistd.h>
#include <stdio.h>

int main()
{
    int seconds = 0;
    //设置计时器
    seconds = alarm(5);
    printf("seconds = %d\n", seconds);

    sleep(2);
    //重置计时器，返回剩余秒数
    seconds = alarm(5);
    printf("seconds = %d\n", seconds);

    while (1)
        ;
    return 0;
}
