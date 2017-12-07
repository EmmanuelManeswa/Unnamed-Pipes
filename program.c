#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc,char *argv[]){

    int fds[2];
    pipe(fds);

    if(!fork()){
	close(fds[READ_END]);
        dup2(fds[WRITE_END],1);
	execlp("ls","ls",NULL);
    }
    else{
	close(fds[WRITE_END]);
	char buf[1000];
	int size;
	while((size = read(fds[READ_END],buf,sizeof(buf))) > 0)
	     write(1,buf,size);
	close(fds[READ_END]);
    }

    exit(EXIT_SUCCESS);
}
