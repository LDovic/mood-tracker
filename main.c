#include <stdio.h>

int mood;
int running;
FILE *file_pointer;

void setMood();

int main () {
    printf("Welcome to the mood tracker.\n");
    running = 1;
    while (running) {
        printf("(1) - Set new mood, (2) - View graph, (3) - quit\n");
        scanf("%i", &running);
        switch (running) {
            case 1:
                setMood();
            break;
            case 2:
            case 3:
                running = 0;
            break;
            default:
                running = 0;
                printf("Invalid option. Exiting...\n");
        }
    }

    return 0;
}

void setMood() {
    file_pointer = fopen("file", "a");
    
    if (!file_pointer) {
        printf("File not found.\n");
       return;
    }

    printf("Please enter mood: ");
    scanf("%i", &mood);
    printf("Writing...\n");
    
    fprintf(file_pointer, "%d", mood);

    fclose(file_pointer);
}
