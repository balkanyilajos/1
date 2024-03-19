#include "poem.h"

static const char* MENU_TEXT =  "--------------------------\n"
                                "| [1] Add a new poem     |\n"
                                "| [2] Print a poem       |\n"
                                "| [3] Print poems' title |\n"
                                "| [4] Delete a poem      |\n"
                                "| [5] Modify a poem      |\n"
                                "| [6] Exit               |\n"
                                "--------------------------\n"
                                "Write here your command: ";

void run(const char* filename) {
    bool running = true;
    const char* const separator = "-----";
    const char* const separatorWithNewLines = "\n-----\n";

    while(running) {
        printf("%s", MENU_TEXT);

        char* poem;
        int inputValue = readNumberFromConsole();
        switch(inputValue) {
            case 1:
                printf("I am waiting for your poem (to stop it, press @ or EOF): \n");
                poem = readPoemFromConsole();
                if(poem == NULL) MemoryAllocationException();
                if(safeToFile(filename, poem, separatorWithNewLines)) {free(poem); IOException(); }
                free(poem);
            break;
            case 2:
                printf("Enter the id of the selected poem: ");
                int id = readNumberFromConsole();
                char* poem = readFromFile(filename, id, separator);
                if (poem == NULL) IOException();
                
                printf("%s", poem);
                free(poem);
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
            default:
                running = false;
        }
        
        printf("\n");
    }
}

Poem* readPoemFromConsole() {
    Poem* poem = (Poem*)malloc(sizeof(Poem));
    if(poem == NULL) return NULL;

    int bufferSize = 128;
    poem->title = (char*)malloc(bufferSize * sizeof(char));
    poem->content = (char*)malloc(bufferSize * sizeof(char));
    if(poem->content == NULL || poem->title == NULL) return NULL;

    printf("title: ");
    scanf("%s", &poem->title);

    int index = 0;
    bool isLineBreak = true;
    char c = getchar();
    c = getchar();
    while(c != EOF && c != '@') {
        if(isLineBreak && c == '\n') { 
            c = getchar();
            continue;
        }
        else { 
            isLineBreak = false; 
        }

        if(index >= bufferSize) {
            bufferSize *= 2;
            poem = (char*)realloc(poem, bufferSize * sizeof(char));
            if(poem == NULL) { free(poem); return NULL; }
        }
        poem[index++] = c;
        c = getchar();
    }

    poem[index--] = '\0';
    while(poem[index] == '\n') {
        poem[index--] = '\0';
    }

    return poem;
}

int readNumberFromConsole() {
    int number;
    scanf("%d", &number);

    return number;
}

void MemoryAllocationException() {
    printf("Memory allocation error!");
    exit(-1);
}

void IOException() {
    printf("Input/Output error!");
    exit(-1);
}