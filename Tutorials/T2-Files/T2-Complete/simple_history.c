#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history_list.h"

void process_command(History* hist, char* input);

int main() {
    History* hist = init_history();
    char input[MAX_COMMAND_LENGTH];
    
    printf("Enter commands (type 'exit' to quit):\n");
    
    while (1) {
        printf("> ");
        if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL) {
            break;
        }
        
        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;
        
        process_command(hist, input);
    }
    
    free_history(hist);
    return 0;
}

void process_command(History* hist, char* input) {
    // Handle exit command
    if (strcmp(input, "exit") == 0) {
        free_history(hist);
        exit(0);
    }

    // Handle history command
    if (strcmp(input, "history") == 0) {
        show_history(hist);
        return;
    }

    // Handle !n command
    if (input[0] == '!') {
        char* end;
        long num = strtol(input + 1, &end, 10);
        
        if (*end != '\0' || num <= 0) {
            printf("Invalid command number\n");
            return;
        }

        char* cmd = get_command_by_number(hist, num);
        if (cmd) {
            printf("Command #%ld was: %s\n", num, cmd);
            free(cmd);
        } else {
            printf("Command not found\n");
        }
        return;
    }

    // Regular command - add to history
    add_to_history(hist, input);
}