#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     
#include <sys/wait.h>

#include <fcntl.h>
#include <errno.h>

char buffer[256];

char ** parse_args(char * line, char * d){
        char **args = malloc(sizeof(char *));
        char *token;
        char *p;
        p = line;
        int counter = 0;

        while(p){
                token = strsep(&p,d);
                args[counter] = malloc(sizeof(char));
                args[counter] = token;
                counter++;
        }
        args[counter] = NULL;
        return args;
}

void cleanF(){

        int i = 0;
        for(i = 0;i<256;i++){
                buffer[i]='\0';
        }
}


void run(char * input){

        char ** args = parse_args(input," ");

        if(strcmp(args[0],"cd")==0){
                chdir(args[1]);
        }

        else if(strcmp(args[0],"exit")==0){
                exit(0);
                exit(0);
        }

        else{
                int f;
                f=fork();

                int e = 0;

                if(f==0){
                        e = execvp(args[0],args);
                        if(e==-1){
                                exit(errno);
                        }
                }

                else{
                        wait(NULL);
                }
        }
}

int directions(char * input){
        int i;
        for (i = 0; input[i]; i++){
                if (input[i] == '>')
                        return 1;
                if (input[i] == '<')
                        return 2;
                if (input[i] == '|')
                        return 3;
        }
        return 0;
}