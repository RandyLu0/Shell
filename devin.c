#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <errno.h>

char buffer[256];
char *command[10];

void print_array(char ** input){
	int i = 1;
	printf("0) %s\n",input[0]);
	while(1){
		printf("%d) %s\n",i,input[i]);
		i++;
		if(input[i]==NULL){
			printf("%d) %s\n",i,input[i]);
			break;
		}
	}
}

char ** parse_args(char * line){
        char **args = command;
        char *token;
        char *p;
        p = line;
        int counter = 0;

        while(p){
                token = strsep(&p," ");
		args[counter] = token;
                counter++;
        }
        args[counter] = NULL;
        return command;
}

void cleanF(){

	int i = 0;
	for(i = 0;i<256;i++){
		buffer[i]='\0';
	}
	for(i=0;i<10;i++){
		command[i]=NULL;
	}
}


int run(char * input){

	char ** args = parse_args(input);
	print_array(args);
	int f;
	f=fork();

	int e = 0;

	if(f==0){
		e = execvp(args[0],args);
	}

	else{
		wait(NULL);
	}

	cleanF();
	return 0;
}

int main(){
	while(1){
		printf("$");
		fgets(buffer, sizeof(buffer), stdin);

		buffer[strcspn(buffer,"\n")]='\0';

		if(strcmp(buffer, "exit") == 0){
			printf("\nEXITED SHELL\n");
			break;
		}

		run(buffer);
	}
	return 0;
}
