#include <stdio.h>

int main(int argc, char *argv[]) { //definitely not right syntax str[] args[2] or something
    FILE* file_ptr;
    int space_count = 0;
    char c;

    if(argc != 2) printf("BAD THING HAPPENED");
    
    file_ptr = fopen(argv[1], "r");

    if(file_ptr == NULL) printf("Something Else That Was Bad Happened");

    while((c = fgetc(file_ptr)) != EOF) {
        if(c == ' ') {
            space_count++;
        }

    }

    fclose(file_ptr);

    printf("%d filename", space_count);
}