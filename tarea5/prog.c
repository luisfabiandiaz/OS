#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
void sighandler(int);

int main () {
   signal(SIGINT, sighandler);

   while(1) {
	pid_t my_pid = getpid();
      printf("soy %d\n", my_pid); 	
      printf("zzzzz\n");
      sleep(2);
   }
   return(0);
}

void sighandler(int signum) {
    printf("Señal detectada: %d\n", signum);
}
