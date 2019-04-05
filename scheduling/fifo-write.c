/*
 * fifo-write.c
 *
 *  Created on: 11-Dec-2017
 *      Author: dzilva
 *
 *  Description: IPC Named pipe | C program to implement one side of FIFO
 *               a named pipe (also known as a FIFO) is one of the methods
 *               for intern-process communication. This side writes first,
 *               then reads
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;

    char * myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    char array1[80], array2[80];
    while (1) {
        fd = open(myfifo, O_WRONLY);

        fgets(array2, 80, stdin);

        write(fd, array2, strlen(array2) + 1);
        close(fd);

        fd = open(myfifo, O_RDONLY);

        read(fd, array1, sizeof(array1));

        printf("User2: %s\n", array1);
        close(fd);
    }
    return 0;
}
