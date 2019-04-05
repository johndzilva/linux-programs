/*
 * message-queue-receive.c
 *
 *  Created on: 11-Dec-2017
 *      Author: dzilva
 *
 *  Description: IPC message queue Program
 *      use $ipcs -q in terminal to view queue details
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE     128

void die(char *s) {
    perror(s);
    exit(1);
}

typedef struct {
    long mtype;
    char mtext[MAXSIZE];
} msgbuf;

void main() {
    int msqid;
    key_t key;
    int msgflg = IPC_CREAT | 0666;
    msgbuf rcvbuffer;

    // Step 1 of program
    key = ftok("/tmp", 'a');  //file to key function to get key from file

    // Step 2 of program
    if ((msqid = msgget(key, msgflg)) < 0)
        die("msgget()");

    //Receive an answer of message type 1.

    // Step 3 of program
    if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0)
        die("msgrcv");

    printf("%s\n", rcvbuffer.mtext);

    exit(0);
}
