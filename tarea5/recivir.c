#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#define MAXSIZE 128

void die(char *s) {
    perror(s);
    exit(1);
}

struct msgbuf {
    long mtype;
    int stype;
    pid_t pid;  
};

int main() {
    int msqid;
    key_t key = 1234;
    struct msgbuf rcvbuffer;
    size_t buflen;

    
    if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0) {
        die("msgget()");
    }

    int pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    buflen = sizeof(rcvbuffer) - sizeof(long);

    if (pid == 0) { 
        while (1) {
            if (msgrcv(msqid, &rcvbuffer, buflen, 1, 0) < 0) {
                die("msgrcv");
            }
            printf("Mensaje tipo 1 recibido: PID = %d, Señal = %d\n", rcvbuffer.pid, rcvbuffer.stype);
            kill(rcvbuffer.pid, rcvbuffer.stype);
        }
    } else { 
        while (1) {
            if (msgrcv(msqid, &rcvbuffer, buflen, 2, 0) < 0) {
                die("msgrcv (tipo 2)");
            }
            printf("Mensaje tipo 2 recibido: Señal = %d\n", rcvbuffer.stype);
	    kill(rcvbuffer.pid, rcvbuffer.stype);
        }
    }
    return 0;
}

