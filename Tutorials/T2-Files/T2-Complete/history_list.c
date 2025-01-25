#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history_list.h"

History* init_history() {
    History* hist = malloc(sizeof(History));
    hist->head = NULL;
    hist->tail = NULL;
    hist->count = 0;
    hist->next_number = 1;
    return hist;
}

HistoryNode* create_node(const char* command, int number) {
    HistoryNode* node = malloc(sizeof(HistoryNode));
    node->command = strdup(command);
    node->number = number;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void add_to_history(History* hist, const char* command) {
    if (!command || command[0] == '\0') {
        return;
    }
    
    // Don't add duplicate of most recent command
    if (hist->tail && strcmp(hist->tail->command, command) == 0) {
        return;
    }

    HistoryNode* node = create_node(command, hist->next_number++);

    if (hist->head == NULL) {
        hist->head = node;
        hist->tail = node;
    } else {
        node->prev = hist->tail;
        hist->tail->next = node;
        hist->tail = node;
    }

    hist->count++;

    if (hist->count > MAX_HISTORY_SIZE) {
        HistoryNode* old_head = hist->head;
        hist->head = hist->head->next;
        hist->head->prev = NULL;
        free(old_head->command);
        free(old_head);
        hist->count--;
    }
}

void show_history(History* hist) {
    HistoryNode* current = hist->head;
    while (current != NULL) {
        printf("%5d  %s\n", current->number, current->command);
        current = current->next;
    }
}

char* get_command_by_number(History* hist, int number) {
    HistoryNode* current = hist->head;
    while (current != NULL) {
        if (current->number == number) {
            return strdup(current->command);
        }
        current = current->next;
    }
    return NULL;
}

void free_history(History* hist) {
    HistoryNode* current = hist->head;
    while (current != NULL) {
        HistoryNode* next = current->next;
        free(current->command);
        free(current);
        current = next;
    }
    free(hist);
}