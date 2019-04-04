//IPC message queue Program 

//use $ipcs -q in terminal to view queue details

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE     128

void die(char *s)
{
  perror(s);
  exit(1);
}

typedef struct msgbuf
{
    long    mtype;
    char    mtext[MAXSIZE];
};

void main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666; 
/*  0400    Read by user.
    0200    Write by user.

    0040    Read by group.
    0020    Write by group.

    0004    Read by others.
    0002    Write by others.*/

    key_t key;
    struct msgbuf sbuf;
    size_t buflen;

    // Step 1 of program
    key = ftok("file-name","a");  //file to key function to get key from file
    if(key == -1)
    	die("Key not created");

    // Step 2 of program
    if ((msqid = msgget(key, msgflg )) < 0)   //Get the message queue ID for the given key
      die("msgget");

    //Message Type
    sbuf.mtype = 1;

    printf("Enter a message to add to message queue : ");
    scanf("%[^\n]",sbuf.mtext);
    getchar();

    buflen = strlen(sbuf.mtext) + 1 ;

    // Step 3 of program
    if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
    {
        printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buflen);
        die("msgsnd");
    }
    else
        printf("Message Sent\n");

    // Step 4 of program
    if (msgctl(msqid, IPC_RMID, NULL) == -1)
    {
        die("delete not happened");
    }

    exit(0);
}
