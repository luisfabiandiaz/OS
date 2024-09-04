#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc,char* argv[]){
	int mi_sig;
	pid_t mi_pid;
	mi_sig=atoi(argv[1]);
	mi_pid=atoi(argv[2]);
	kill(mi_pid,mi_sig);
}
