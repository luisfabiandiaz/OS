#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
	int input_FD=open("input.txt", O_RDONLY);
	int output_FD=open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	dup2(input_FD, 0);
	dup2(output_FD, 1);

	pid_t pid;
	pid=fork();
	const char *Arg[]={"./pp.exe",NULL};
	if(pid==0){
		execvp(Arg[0], (char * const *)Arg);
		perror("NO se pudo");
		exit(1);
	}
	else{
		wait(NULL);
	}
	close(input_FD);
	close(output_FD);
}
