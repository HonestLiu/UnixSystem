#include <stdio.h>
#include <stdlib.h>

void fileRead(){
    char* filePath = "/home/honestliu/Develop/Test01/test.txt";
    FILE* file = fopen(filePath, "r");
    if(file == NULL){
        printf("Error: file not found\n");
        exit(1);
    }
    //按行读取文件
    char line[1024];
    while(fgets(line, 1024, file) != NULL){
        printf("%s", line);
    }
    fclose(file);
}

int main(){
    return 0;
}
