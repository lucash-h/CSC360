#include "history_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
1. History* init_history()
Purpose: Initialize a new history list

Returns: Pointer to newly allocated History structure

Parameters: None

Requirements:

Allocate memory for History structure
Initialize all fields to appropriate starting values
Handle memory allocation failures
*/

History* init_history(){
    History* hist = (History*)malloc(sizeof(History));

    if(hist == NULL){
        fprintf(stderr, "MEMORY WAS NOT ALLOCATED FOR HISTORY OBJECT\n");
        return NULL;
    }

    hist->head = NULL;
    hist->tail = NULL;
    hist->count = 0;
    hist->next_number = 1;

    return hist;
}

/*
2. void add_to_history(History* hist, const char* command)
Purpose: Add a new command to the history

Parameters:

hist: Pointer to History structure
command: String containing the command to add
Requirements:

Skip empty commands
Don't add duplicate of most recent command
Maintain doubly linked list connections
Enforce MAX_HISTORY_SIZE limit
Handle memory allocation failures
*/

void add_to_history(History* hist, const char* command){

    //handle empty commands
    if(command == NULL) return;



    HistoryNode* node = (HistoryNode*)malloc(sizeof(HistoryNode));
    if(node == NULL){
        fprintf(stderr, "NODE MEMORY ALLOCATION DIDNT WORK");
        return;
    }
        
    //put command and relevant data into hist and node
    

    //dont go over max size and if so, remove oldest node
    if(hist->count >= MAX_HISTORY_SIZE) { 
        HistoryNode* temp = hist->head;
        //null content

        hist->head->number = -1;
        hist->head->command = NULL;

        //null pointer and transfer head to next node
        hist->head = hist->head->next;
        hist->head->prev = NULL;

        free(temp->command);
        free(temp);

        hist->count--;
    }

    //update node and hist with info
    node->command = strdup(command);
    node->number = hist->next_number;
    hist->next_number ++;
    hist->count ++;

    hist->tail->next = node;
    node->prev = hist->tail;
    hist->tail = node;

}

void show_history(History* hist){
    
    HistoryNode* temp = hist->head;

    while((temp != hist->tail) && (temp != NULL)) {
        printf("\nCommand: %s\n", temp->command);
        temp = temp->next;
    }
}
/*
3. char* get_command_by_number(History* hist, int number)
Purpose: Retrieve a specific command by its number

Parameters:

hist: Pointer to History structure
number: Command number to retrieve
Returns: Newly allocated string containing the command, or NULL if not found

Requirements:

Return NULL for invalid numbers
Return a copy of the command string
Handle memory allocation failures
*/

char* get_command_by_number(History* hist, int number){
    HistoryNode* temp = hist->head;

    while(temp != NULL && temp != hist->tail) {
        if(number == temp->number) {
            return temp->command;
        }
        temp = temp->next;
    }

    if(temp->number == number) {
        return temp->command;
    } else {
        return NULL;
    }
    
}

/*
4. void free_history(History* hist)
Purpose: Free all memory associated with history

Parameters:

hist: Pointer to History structure
Requirements:

Free all HistoryNode structures
Free all command strings
Free the History structure itself
Handle NULL pointer gracefully
*/
void free_history(History* hist){
    //go through the list and null everything
    //start at head go to next, null prev node and prev pointer
    //go to next and do the same
    if(hist == NULL) {
        return;
    }

    HistoryNode* curr = hist->head;

    while(curr != NULL) {

        HistoryNode* temp = curr->next;

        free(curr->command);
        free(curr);
        temp->prev = NULL;
        curr = temp;
    }

    free(hist);
}