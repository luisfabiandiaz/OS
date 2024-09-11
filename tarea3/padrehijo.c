#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define END_MESSAGE "EOM"
#define BUFFER_SIZE 256

int main() {
    int Fd1[2], Fd2[2];
    int lineas = 0;
    pid_t pid;
    pipe(Fd1); 
    pipe(Fd2); 

    pid = fork();

    if (pid == 0) { // Proceso hijo
        close(Fd1[0]); 
        close(Fd2[1]); 

        char* lineas_hijo[] = {"Primra linea\n", "Segunda linea\n", "Tercera linea\n","CUarta linea\n", END_MESSAGE};
        
        for (int i = 0; lineas_hijo[i] != END_MESSAGE; i++) {
            write(Fd1[1], lineas_hijo[i], strlen(lineas_hijo[i]));
        }
        
        write(Fd1[1], END_MESSAGE, strlen(END_MESSAGE));

        close(Fd1[1]); 

        char buffer[BUFFER_SIZE];
        read(Fd2[0], buffer, BUFFER_SIZE);
        printf("Hijo: El padre ha contado %s líneas\n", buffer);

        close(Fd2[0]); 
    } 
    else {
        close(Fd1[1]); 
        close(Fd2[0]); 

        FILE* pipe_lectura = fdopen(Fd1[0], "r");
        char *buffer = NULL;
        size_t len = 0;

        while (getline(&buffer, &len, pipe_lectura) != -1) {
            if (strncmp(buffer, END_MESSAGE, strlen(END_MESSAGE)) == 0) {
                break;
            }
            lineas++; 
        }

        fclose(pipe_lectura);
        free(buffer); 

      
        char buffer_padre[BUFFER_SIZE];
        sprintf(buffer_padre, "%d", lineas);
        write(Fd2[1], buffer_padre, strlen(buffer_padre) + 1); 

        close(Fd1[0]); 
        close(Fd2[1]); 
    }

    return 0;
}

