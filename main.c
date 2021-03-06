#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     
#include <sys/wait.h>

#include <fcntl.h>
#include <errno.h>
#include "shell.h"

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

int main(){
        char wd[256];
        while(1){
                getcwd(wd,256);
                printf("RGD:%s$ ",wd);
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
                        
                        if (s == 2){
                                char * line = commandList[i];
                                char * command = malloc(sizeof(char));
                                char * filename = malloc(sizeof(char));
                                char ** split = parse_args(line,"<");
                                command = split[0];
                                filename = split[1];

                                int fd = open(filename, O_RDONLY);
                                if (fd == -1){
                                printf("Error: %s\n", strerror(errno));
                                return -1;
                                }

                                int backup_stdin = dup(STDOUT_FILENO);
                                dup2(fd, STDIN_FILENO);
                                run(command);
                                 dup2(backup_stdin, STDIN_FILENO);
                                close(fd);
                        }
                        
                        if (s == 3){
                                char * line = commandList[i];
                                char ** split = parse_args(line,"|");
                                char ** command1 = parse_args(split[0], " ");
                                char ** command2 = parse_args(split[1], " ");

                                int p[2];
                                pipe(p);
                                int f = fork();
                                if(f==0){
                                        dup2(p[1], STDOUT_FILENO);
                                        close(p[0]);
                                        close(p[1]);
                                        execvp(command1[0], command1);
                                }
                                else {
                                dup2(p[0], STDIN_FILENO);
                                close(p[0]);
                                close(p[1]);
                                execvp(command2[0], command2);
                                }
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
