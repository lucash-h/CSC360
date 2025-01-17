#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE* file_ptr;
    int word_count = 0;
    char c;
    int word = 1;
    
    file_ptr = fopen(argv[1], "r");

    while((c = fgetc(file_ptr)) != EOF) {
        //printf("HERE IS CHARACTER: %c\n", c);

        if(((c == ' ') || (c == '\n')) && (word == 1)) { //space after non space char
            word_count++;
            word = 0;
        } else if ((word == 0) && ((c != ' ') && (c != '\n'))) { //word and non space -> word = 1 dont incremenet
            word = 1;
        }
    }

    if(c != ' ' || c != '\n') word_count+=1;
    
    fclose(file_ptr);
    printf("%d %s\n", word_count, argv[1]);
    return 0;
}