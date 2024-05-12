#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 获取唯一的key值
    int key = ftok("/", 2023);

    // 获取共享内存的标识
    int shmid = shmget(key, 64, IPC_CREAT | 0666);

    // 将虚拟内存和物理内存建议映射
    char *shmaddr = (char *)shmat(shmid, NULL, 0);

    // 操作虚拟内存
    printf("读到数据:%s\n",shmaddr);

    // 释放映射
    shmdt(shmaddr);

    return 0;
}
