#include <unistd.h>

int main()
{

    /*
    //使用execl发起ls-ah命令，必须包含ls的路径名，因为它不会去环境中去获取ls的路径
    execl("/usr/bin/ls","ls","-a","-h",NULL);
    */

   /*
   //使用execlp发起ls-ah命令，因为其会去path中去获取ls的路径，所以无需指明ls的路径
   execlp("ls","ls","-a","-h",NULL);
   */

    //使用execvp需要以指针数组的形式传入程序名和程序选项
    char *argv[] = {"ls","-a","-h",NULL};
    execvp("ls",argv);
}