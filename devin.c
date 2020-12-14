#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <errno.h>

char buffer[256];

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


int main(){
        char wd[256];
        while(1){
                getcwd(wd,256);
                printf("LIXA:%s$ ",wd);
                fgets(buffer, sizeof(buffer), stdin);

                buffer[strcspn(buffer,"\n")]='\0';

                char **commandList = parse_args(buffer,";");

                //print_array(commandList);

                int counter;
                for(counter=0;commandList[counter]!=NULL;counter++){
                        run(commandList[counter]);
                }

                free(commandList);
                cleanF();
        }


        return 0;
}
