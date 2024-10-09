#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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

struct sembuf p = {0, -1, SEM_UNDO};
struct sembuf v = {0, +1, SEM_UNDO};

void semP(int id) {
    if (semop(id, &p, 1) < 0) {
        perror("semop p");
        exit(1);
    }
}

void semV(int id) {
    if (semop(id, &v, 1) < 0) {
        perror("semop v");
        exit(1);
    }
}

int main() {
    int id = semget(KEY, 1, 0); 
    if (id < 0) {
        perror("semget");
        exit(1);
    }
    semP(id);
    for (int x = 0; x < 10; x++) { 
        printf("hola mundo\n");
        sleep(1);  
    }
    semV(id);

    return 0;
}

