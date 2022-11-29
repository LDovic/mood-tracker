#include <stdio.h>
#include <time.h>
#include <unistd.h>

FILE *file_pointer;

int mood;
int running;

char green[] = "\033[0;32m";
char yellow[] = "\033[1;33m";
char red[] = "\033[0;31m";
char default_color[] = "\033[0m";

void setMood();
void viewGraph();
void createFile();
void resetData();

int main () {
    if (access("file.csv", F_OK) == 0) {
        file_pointer = fopen("file.csv", "a");
    } else {
        createFile();
    }

    if (!file_pointer) {
        printf("%sCannot open file. Exiting...\n%s", red, default_color);
        return 0;
    }

    printf("%s -- Welcome to the mood tracker.%s\n", green, default_color);
    running = 1;
    while (running) {
        printf("(1) - Set new mood, (2) - View graph, (3) - Reset data, (4) - quit\n");
        scanf("%i%*c", &running);
        switch (running) {
            case 1:
                setMood();
            break;
            case 2:
                viewGraph();
            break;
            case 3:
                resetData();
            break;
            case 4:
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
    file_pointer = fopen("file.csv", "a");
    time_t seconds;

    if (!file_pointer) {
        printf("%sFile not found.\n%s", red, default_color);
       return;
    }

    printf("Please enter mood: ");
    scanf("%i*c", &mood);
    printf("Writing...\n");
    
    seconds = time(NULL);

    fprintf(file_pointer, "%d,%ld\n", mood, seconds);
    fclose(file_pointer);
}

void viewGraph() {
    // openGL
}

void createFile() {
    printf("%sInitialising new file...%s\n", yellow, default_color);
    file_pointer = fopen("file.csv", "w");
    fprintf(file_pointer, "%s,%s\n", "x", "y");
    fclose(file_pointer);
}

void resetData() {
    char reset_confirm;
    printf("Are you sure you want to reset the data (y/n)?\n");
    reset_confirm = getchar();

    switch (reset_confirm) {
        case 'y':
        break;
        case 'n':
            return;
        break;
        default:
            printf("%sInvalid option. Exiting...\n%s", red, default_color);
            running = 0;
            return;
    }

    if (remove("file.csv") == 0) {
       printf("%sData reset.%s\n", green, default_color);
       createFile();
       return;
    }

    printf("%sUnable to reset data.\n%s", red, default_color);
}


