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
    - Ex: $ls<example.txt      this will work
    -     $ls < example.txt    this will not work

### Files and Function Headers 

#### parse_args
 * Handles all line parsing fucntions
  ```
  /*======== char ** parse_args(char * line, char * d) ==========
  Inputs:  char *line
            char *d
  Returns: Number of tokens in line separated by d
  *
  
  

  
