#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <GL/freeglut.h>

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

int main (int argc, char** argv) {
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
                viewGraph(argc, argv);
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

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void viewGraph(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

    int width = 1920;
    int height = 1080;
    glutInitWindowSize(width, height);

    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);
    int win = glutCreateWindow("Tutorial 01");
    printf("window id: %d\n", win);

    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glutDisplayFunc(RenderSceneCB);

    glutMainLoop();
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


