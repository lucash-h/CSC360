#ifndef HISTORY_LIST_H
#define HISTORY_LIST_H

#define MAX_COMMAND_LENGTH 1024
#define MAX_HISTORY_SIZE 1000

// Node structure for our linked list
typedef struct HistoryNode {
    int number;             // Command number
    char* command;          // The command string
    struct HistoryNode* next;
    struct HistoryNode* prev;
} HistoryNode;

// History structure to keep track of list metadata
typedef struct {
    HistoryNode* head;
    HistoryNode* tail;
    int count;
    int next_number;
} History;

// Functions you need to implement in history_list.c
History* init_history();
void add_to_history(History* hist, const char* command);
void show_history(History* hist);
char* get_command_by_number(History* hist, int number);
void free_history(History* hist);

#endif