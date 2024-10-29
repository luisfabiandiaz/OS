#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/shm.h>
#define SHMSZ     27

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

int main(int argc,char* argv[]) {
    int shmid, v, shmv;
    key_t key;
    char *shm, *s, *p, *txt;
    char d[10];
    txt = argv[1];
    v = atoi(argv[2]);
    key = 5678;

    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    p = shm + 3;

    int id = semget(KEY, 1, 0); 
    if (id < 0) {
        perror("semget");
        exit(1);
    }
    while(1){
    	semP(id);
    
    	strncpy(d, shm, 3);
    	shmv = atoi(d);
    	if(shmv == (v-1)){
		printf("Valor de txt: %s\n", txt);
		sprintf(shm, "%03d", v);
		strcpy(p, txt);
		v = v + 3;
		printf("Contenido de la memoria compartida: %s\n", shm);
    	}
	sleep(1);
    	semV(id);
    }
    return 0;
}
