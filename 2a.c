#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#define BUFFER_SIZE 1024

int main(int argC, char** argV)
{
	int src, dest, n;
	char buffer[BUFFER_SIZE];
	if(argC != 3){
		printf("Usage %s <src> <dest>\n", argV[0]);
		exit(1);
	}
	if((src = open(argV[1], O_RDONLY)) == -1){
		perror("Error Opening Source File.\n");
		exit(1);
	}
	if((dest = open(argV[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1){
		perror("Error Opening Dest File.\n");
		exit(1);
	}
	while((n=read(src, buffer, BUFFER_SIZE)) > 0){
		if(write(dest, buffer, n) != n){
			perror("Error Writing to Destination.\n");
			exit(1);
	}}
	if(n == -1){
		perror("Error reading from source file\n");
		exit(1);
	}
	close(src);
	close(dest);
	printf("FIle copied successfully\n");
	return 0;
}
