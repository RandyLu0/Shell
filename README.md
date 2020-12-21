## RGD
By Randy Lu, Devin Zhang, Gavin Zhao\
TNPG: RGD

### Features:
- Forks and executes commands
- Parses multiple commands on one line
- Redirects using >, <

---

### Attempted:

---

### Bugs
- There cannot be whitespace before and after the semicolon and direction operators
    - $ls<example.txt      this will work
    - $ls < example.txt    this will not work

---

### Files and Function Headers 
#### shell.c
    * Handles all the functions that is needed for the shell to work
    ```
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
    
    /*================ int directions(char* input) ================
    Inputs: char* input
        
    Returns an int
        - 0     Normal Command
        - 1     Command has a >
        - 2     Command has a <
        - 3     Command has a |
    =======================================================*/
    ```
    
#### main.c
    * The core of the shell that puts all the functions together to form a working shell
    ```
    /*================ int main() ================
    Inputs: N/A
          
    Prints the input request, reads the command, and then execute it
    =======================================================*/
    ```

  
