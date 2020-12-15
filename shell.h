#ifndef SHELL_H
#define SHELL_H

char ** parse_args(char * line, char * d);

void CleanF();

void run(char * input);

int directions(char * input);

#endif