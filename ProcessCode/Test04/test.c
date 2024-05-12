#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
    char *message = "Hello, world!\n";
    size_t len = strlen(message);
    ssize_t bytes_written;

    // 文件描述符为1表示标准输出，也就是stdout
    bytes_written = write(1, message, len);

    if (bytes_written != len) {
        perror("write");
        return 1;
    }

    return 0;
}
