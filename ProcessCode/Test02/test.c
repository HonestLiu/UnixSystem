#include <stdio.h>
#include <string.h>

void login();

void sign();

char *filePath = "data.txt";

int main() {
    int opcode;
    while (1){
        printf("欢迎来到登录注册器 登录(1) 注册(2)\n");
        printf("请输入操作码:");
        scanf("%d", &opcode);
        switch (opcode) {
            case 1:
                login();
                break;
            case 2:
                sign();
                break;
            default:
                break;
        }
    }
}

void login() {
    char name[30];
    printf("请输入用户名: ");
    scanf("%s", name);
    printf("\n");
    char password[30];
    printf("请输入密码: ");
    scanf("%s", password);
    printf("\n");

    FILE *file = file = fopen(filePath, "r");
    if (file == NULL) {
        printf("文件打开失败");
    }

    char line[1024];
    //不断读取用户数据文件并截取用户名和密码与用户输入的值进行比较，只有一样时才会返回返回"登录成功"
    while (fgets(line, 1024, file) != NULL) {
        //切割字符串，获取用户名和密码
        char *userName = strtok(line, ":");
        printf("%s\n",userName);
        char *passwd = strtok(NULL, "\n");
        printf("%s\n",passwd);
        printf("%d\n",strcmp(passwd,password));

        if (strcmp(userName, name) == 0 && strcmp(passwd,password) == 0) {
            printf("登录成功");
            printf("\n");
            return;
        }
    }
    printf("登录失败，密码或用户名错误");
    printf("\n");
    fclose(file);

    return;
}

void sign() {
    char name[30];
    printf("请输入用户名:");
    scanf("%s",name);
    printf("\n");
    char  passwd[30];
    printf("请输入密码:");
    scanf("%s",passwd);
    printf("\n");

    FILE *file = fopen(filePath,"a");
    if (file == NULL) {
        printf("文件打开失败");
    }

    fputs(name,file);
    fputs(":",file);
    fputs(passwd,file);
    fputs("\n",file);

    fclose(file);

    return;
}

