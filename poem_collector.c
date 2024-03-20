#include "poem_collector.h"

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

        Poem* poem;
        int inputValue = readNumberFromConsole();
        switch(inputValue) {
            case 1:
                printf("I am waiting for your poem (to stop it, press @ or EOF):\n");
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

    int titleBufferSize = 32;
    int contentBufferSize = 128;

    poem->title = (char*)malloc(titleBufferSize * sizeof(char));
    if(poem->title == NULL) { free(poem); return NULL; }

    poem->content = (char*)malloc(contentBufferSize * sizeof(char));
    if(poem->content == NULL) { free(poem->title); free(poem); return NULL; }

    printf("title - ");
    //fgets(poem->title, bufferSize * sizeof(char), stdin);

    int i = 0;
    for(char c = getchar(); c != EOF && c != '\n'; i += 1, c = getchar()) {
        if(i >= titleBufferSize-2) {
            titleBufferSize *= 2;
            poem->title = (char*)realloc(poem->title, titleBufferSize * sizeof(char));
            if(poem->title == NULL) { free(poem->title); return NULL; }
        }
        poem->title[i] = c;
    }
    poem->title[i] = '\0';
    
    printf("content:\n");
    i = 0;
    for(char c = getchar(); c != EOF && c != '@'; i += 1, c = getchar()) {
        if(i >= contentBufferSize-2) {
            contentBufferSize *= 2;
            poem->content = (char*)realloc(poem->content, contentBufferSize * sizeof(char));
            if(poem->content == NULL) { free(poem->content); return NULL; }
        }
        poem->content[i] = c;
    }
    poem->content[i] = '\0';

    trim(poem->title);
    trim(poem->content);

    return poem;
}

int readNumberFromConsole() {
    char line[16];
    fgets(line, sizeof(line), stdin);

    return atoi(line);
}

void trim(char* str) {
    int start = 0;
    while (isspace(str[start])) {
        start += 1;
    }

    if (str[start] == '\0') {
        str[0] = '\0';
        return;
    }

    int end = strlen(str)-1;
    while (isspace(str[end])) {
        end -= 1;
    }
    str[end + 1] = '\0';

    if (start > 0) {
        memmove(str, str + start, end - start + 2);
    }
}

void MemoryAllocationException() {
    printf("Memory allocation error!");
    exit(-1);
}

void IOException() {
    printf("Input/Output error!");
    exit(-1);
}