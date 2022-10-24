#include <stdio.h>

FILE *file_pointer;

int mood;
int running;

char green[] = "\033[0;32m";
char yellow[] = "\033[1;33m";
char red[] = "\033[0;31m";
char default_color[] = "\033[0m";

void setMood();

int main () {
    file_pointer = fopen("file.csv", "w");
    if (!file_pointer) {
        printf("%sCannot open file. Exiting...\n%s", red, default_color);
        return 0;
    }

    printf("%s -- Welcome to the mood tracker.%s\n", green, default_color);
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
	        printf("%sInvalid option. Exiting...\n%s", red, default_color);
                running = 0;
        }
    }

    return 0;
}

void setMood() {
    file_pointer = fopen("file", "a");
    
    if (!file_pointer) {
        printf("%sFile not found.\n%s", red, default_color);
       return;
    }

    printf("Please enter mood: ");
    scanf("%i", &mood);
    printf("Writing...\n");
    
    fprintf(file_pointer, "%d", mood);

    fclose(file_pointer);
}


