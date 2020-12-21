## RGD
By Randy Lu, Devin Zhang, Gavin Zhao
TNPG: RGD

### Features:
- Forks and executes commands
- Parses multiple commands on one line
- Redirects using >, <

### Attempted:

### Bugs
- There cannot be whitespace before and after the semicolon and direction operators
    - $ls<example.txt      this will work
    - $ls < example.txt    this will not work

### Files and Function Headers 
#### shell.c
    * Handles all the functions that is needed for the shell to work
    '''
    /*================ char** parse_args() ================
    Inputs: char* line
            char *d
    Returns an array of string split by the d
    =======================================================*/
    
    /*================ void cleanF() ================
    Inputs: N/A
        
    Cleans the buffer by replacing all elements of the char array with a NULL character
    =======================================================*/
    
    /*================ void run() ================
    Inputs: char* input
    
    Takes a command parsed by whitespace. If the command is cd when program use chdir(). 
    If the command is exit then program use exit(). Everything else the program forks and 
    the child executes the command.
    =======================================================*/
    
    '''
    
#### main.c
    *
    '''
    
    
    
    
    '''

  
