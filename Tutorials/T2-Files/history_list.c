#include "history_list.h"
#include <stdio.h>
#include <string.h>

History* init_history(){
    History* hist = (History*)malloc(sizeof(History));

    if(hist == NULL){
        printf("MEMORY WAS NOT ALLOCATED FOR HISTORY OBJECT");
        return;
    }
    hist->head = NULL;
    hist->tail = NULL;
    hist->count = 0;
    hist->next_number = 0;

    return hist;
}

void add_to_history(History* hist, const char* command){

    HistoryNode* node = (HistoryNode*)malloc(sizeof(HistoryNode));

    node->command = command;

    int cmd_len = strlen(command); //add null terminator??
    int temp_count = hist->count;

    if(cmd_len >= 1024) {
        printf("COMMAND LENGTH HAS BEEN EXCEEDED");
        return;
    }

    //make sure that the the list hasn't gone over max history size
    if(temp_count >= MAX_HISTORY_SIZE) {
        //null content
        hist->head->number = NULL;
        hist->head->command = NULL;

        //null pointer and transfer head to next node
        hist->head = hist->head->next;
        hist->head->prev = NULL;
    }


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

char* get_command_by_number(History* hist, int number){
    HistoryNode* temp = hist->head;
    
    if(number == hist->tail->number) {
        return hist->tail->command;
    }

    while(temp != NULL && temp != hist->tail) {
        if(number == temp->number) {
            return temp->command;
        }
        temp = temp->next;
    }

    
}
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

        free(curr);
        temp->prev = NULL;
        curr = temp;
    }

    free(hist);
}