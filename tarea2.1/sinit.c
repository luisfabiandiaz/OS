#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/shm.h>

#define KEY 0x1111
#define SHMSZ     27

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    int shmid;
    key_t key;
    char *shm, *s;
    key = 5678;

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    strncpy(shm, "003ini", SHMSZ);


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

    printf("Semaforo y sh inicializados");
    return 0;
}
