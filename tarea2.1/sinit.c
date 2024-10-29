#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define KEY 0x1111

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    if (id < 0) {
        perror("semget");
        exit(1);
    }

    union semun u;
    u.val = 1;
    if (semctl(id, 0, SETVAL, u) < 0) {
        perror("semctl");
        exit(1);
    }

    printf("Semaforo inicializado");
    return 0;
}
