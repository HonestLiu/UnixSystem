#include <sys/types.h>
#include <unistd.h>


void *printFun(int pipefd[2]);
int main()
{
    int pipefd[2];
    pipe(pipe);

    pid_t pt = fork();
    if (pt == 0)
    {
        execl("/usr/bin/mplayer", "/usr/bin/mplayer", "-ac", "mad", "-slave", "-quiet", "-idle",
              "-input", "file=./cmdFifo", "/home/honestliu/Music/emo.mp3", NULL);
        dup2(pipefd[1], 1);
    }
    printFun(pipe);

    
}

void * printFun(int pipefd[2]){
    close(pipefd[1]);
    
}