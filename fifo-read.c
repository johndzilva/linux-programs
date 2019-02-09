// IPC Named pipe | C program to implement one side of FIFO
// a named pipe (also known as a FIFO) is one of the methods for intern-process communication
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 
int main()
{
    int fd;
 
    // FIFO file path
    char * myfifo = "/tmp/myfifo";
 
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);
 
    char array1[80], array2[80];
    while (1)
    {
        // Open FIFO for write only
        fd = open(myfifo, O_WRONLY);
 
        // Take an input array2ing from user.
        // 80 is maximum length
        fgets(array2, 80, stdin);
 
        // Write the input array2ing on FIFO
        // and close it
        write(fd, array2, strlen(array2)+1);
        close(fd);
 
        // Open FIFO for Read only
        fd = open(myfifo, O_RDONLY);
 
        // Read from FIFO
        read(fd, array1, sizeof(array1));
 
        // Print the read message
        printf("User2: %s\n", array1);
        close(fd);
    }
    return 0;
}