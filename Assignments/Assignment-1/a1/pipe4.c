#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wait.h>

//remove this after
//#include <stdio.h>

#define MAX_COMMANDS 4
#define MAX_ARGUMENTS 8
#define MAX_CHAR_LINE_SIZE 80

//this thing is actually gross fix it

int error_check(ssize_t bytes_read) {
  if(bytes_read == -1) {
    //printf("BYTES READ ALLOCATION FAILED\n");
    return 0;
  } else if (bytes_read == 0) {
    //printf("END OF FILE OR NO MORE DATA TO READ");
    return 0;
  } else {
    if(bytes_read > 0) {
      return 1;
    } else {
      return 0;
    }
  }
}


/*
Function inputs a vector that contains a set of command + complement command
uses fork and execvp to run a child process without changing the parent one
*/

void fork_process(char *command_vector[]){
  pid_t p = fork();

    
  if(p == -1) {
    //printf("FORK FAILED'n\'");
    exit(1);
  }

  if(p == 0) { //child process is created
    execvp(command_vector[0],command_vector);
    //printf("EXEC VP FAILED IN FORK PROCESS\n"); //exec vp didnt work
    exit(1);
  }

}

/*
Function clears a string array, setting all values to null
*/
void clear_str_array(char *array[]) {
  for(int i = 0; array[i] != NULL; i++) {
    array[i] = NULL;
  }
}

int main() {
    char buffer[MAX_CHAR_LINE_SIZE];
    char *command_vector[MAX_COMMANDS][MAX_ARGUMENTS];
    int cmd_count = 0;
    int pipes[MAX_COMMANDS-1][2];
    
    
    while(cmd_count < MAX_COMMANDS) {
        ssize_t bytes = read(0, buffer, MAX_CHAR_LINE_SIZE);
        
        //if read breaks
        if(bytes <= 0) {
            //perror("Read error");
            exit(1);
        }
        
        // Check for terminating enter
        if(bytes == 1 && buffer[0] == '\n') {
            break;
        }
        
        // remove enter and add null terminator
        buffer[bytes-1] = '\0';
        
        // tokenize command
        char *token = strtok(buffer, " \t");
        int arg_count = 0;
        
        //while there are tokens and max arguments haven't been exceeded
        while(token && arg_count < MAX_ARGUMENTS-1) {
            command_vector[cmd_count][arg_count] = strdup(token);  
            if(command_vector[cmd_count][arg_count] == NULL) {
                //perror("Memory allocation failed");
                exit(1);
            }
            arg_count++;
            token = strtok(NULL, " \t");
        }
        command_vector[cmd_count][arg_count] = NULL;
        cmd_count++;
    }
    
    if(cmd_count == 0) {
        //printf("No commands entered\n");
        return 0;
    }

    // pipe
    for(int i = 0; i < cmd_count-1; i++) {
        if(pipe(pipes[i]) == -1) {
            //perror("Pipe creation failed");
            exit(1);
        }
    }

    // execute commands w/ piping
    for(int i = 0; i < cmd_count; i++) {
        pid_t pid = fork();
        if(pid == -1) {
            //perror("Fork failed");
            exit(1);
        }
        if(pid == 0) {
            // set up pipes for child
            if(i > 0) {
                if(dup2(pipes[i-1][0], STDIN_FILENO) == -1) {
                    //perror("dup2 input failed");
                    exit(1);
                }
            }
            if(i < cmd_count-1) {
                if(dup2(pipes[i][1], STDOUT_FILENO) == -1) {
                    //perror("dup2 output failed");
                    exit(1);
                }
            }

            // close pipes
            for(int j = 0; j < cmd_count-1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            execvp(command_vector[i][0], command_vector[i]);
            //perror("execvp failed");
            exit(1);
        }
    }

    // close parent pipes
    for(int i = 0; i < cmd_count-1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // wait for all children
    for(int i = 0; i < cmd_count; i++) {
        wait(NULL);
    }

    // free memory
    for(int i = 0; i < cmd_count; i++) {
        for(int j = 0; command_vector[i][j] != NULL; j++) {
            free(command_vector[i][j]);
        }
    }

    return 0;
}