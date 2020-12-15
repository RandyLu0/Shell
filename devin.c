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


int main(){
        char wd[256];
        while(1){
                getcwd(wd,256);
                printf("LIXA:%s$ ",wd);
                fgets(buffer, sizeof(buffer), stdin);

                buffer[strcspn(buffer,"\n")]='\0';

                char **commandList = parse_args(buffer,";");

                //print_array(commandList);

                int i;
                for (i = 0; commandList[i]; i++){
                        int s = directions(commandList[i]);

                        if (s == 1){
                                char * line = commandList[i];
                                char * command = malloc(sizeof(char));
                                char * filename = malloc(sizeof(char));
                                char ** split = parse_args(line,">");
                                command = split[0];
                                filename = split[1];
                                printf("%s\n",command);

                                int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0640);
                                if (fd == -1){
                                        printf("Error: %s\n", strerror(errno));
                                        return -1;
                                }
                                int backup_stdout = dup(STDOUT_FILENO);
                                dup2(fd, STDOUT_FILENO);
                                run(command);
                                dup2(backup_stdout, STDOUT_FILENO);
                                close(fd);
                        }

                        if (s == 0){
                                int counter;
                                for(counter=0;commandList[counter]!=NULL;counter++){
                                        run(commandList[counter]);
                                }
                        }

                }

                free(commandList);
                cleanF();



        }


        return 0;
}
