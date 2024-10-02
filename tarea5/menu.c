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

struct msgbuf
{
    long    mtype;
    char    mtext[MAXSIZE];
};

main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    struct msgbuf sbuf;
    size_t buflen;

    key = 1234;

    if ((msqid = msgget(key, msgflg )) < 0)   //Get the message queue ID for the given key
	die("msgget");

    //Message Type
    sbuf.mtype = 1;

    printf("Menu: ");
    printf("1: signal 2 \n");
    printf("2: signal 9 \n");
    printf("3: signal 18 \n");
    printf("4: signal 19 \n");
    scanf("%d", &var);
    if(var > 0 && var < 5){
    	switch(var){
		case 1:
			sbuf.stype = 2;
			sbuf.mtype = 1;
			break;
		case 2:
                        sbuf.stype = 9;
                        sbuf.mtype = 1;
                        break;
		case 3:
                        sbuf.stype = 18;
                        sbuf.mtype = 1;
                        break;
		case 4:
                        sbuf.stype = 19;
                        sbuf.mtype = 1;
                        break;
	}
	else{
		printf("ERROR")
	}
    }

    getchar();

    buflen = strlen(sbuf.mtext) + 1 ;

    if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
    {
        printf ("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
        die("msgsnd");
    }

    else
        printf("Message Sent\n");

    exit(0);
}
         
