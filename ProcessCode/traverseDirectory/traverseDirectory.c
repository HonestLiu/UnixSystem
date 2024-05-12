#include <sys/types.h>
#include <dirent.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

/*
定义一个函数，采用递归算法，扫描目录下的文件
使用opendir、readdir、closedir三个内置函数接口
 */

// 遍历函数
void traverse(char *dirName);

int main()
{
    // 传入要扫描的目录
    char dirName[30];
    printf("请输入要扫描的目录:");
    scanf("%s", dirName);
    printf("\n");
    traverse(dirName);
}

void traverse(char *dirName)
{
    /* 递归:当扫描的目标是目录时，就再次调用本函数，直到遇到文件名时，直接打印 */
    // 打开要扫描的目录
    DIR *dir = opendir(dirName);
    if (dir == NULL)
    {
        perror("openDir");
    }

    struct dirent *rd;
    char filePath[1024];
    while (rd = readdir(dir)) // NULL直接默认成flase即可，读不到的时候会停下的
    {

        // 在Linux系统中，使用dirent.h库中的readdir函数遍历目录时，它会返回目录中所有的条目，包括.（表示当前目录）和..（表示父目录）
        if (strcmp(rd->d_name, ".") == 0 || strcmp(rd->d_name, "..") == 0)
        {
            // 跳过当前目录和父目录
            continue;
        }

        // 拼接当前遍历到内容的目录(我忘了)
        snprintf(filePath, sizeof(filePath), "%s/%s", dirName, rd->d_name);

        if ((rd->d_type & DT_REG) == DT_REG)
        {
            // 读到的是文件，打印文件名
            printf("遍历到文件:%s\n", rd->d_name);
        }
        if ((rd->d_type & DT_DIR) == DT_DIR)
        {
            // 如果遍历到的是目录，则再次调用本函数，实现递归
            traverse(filePath);
        }
    }
    closedir(dir);
}