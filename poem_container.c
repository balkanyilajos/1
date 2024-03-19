#include "poem_container.h"

bool isFileExists(const char* filename) {
    FILE *fp = fopen(filename, "r");
    bool isExists = false;
    if (fp != NULL)
    {
        isExists = true;
        fclose(fp);
    }
    return isExists;
}

int createFile(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if(fp == NULL) { return -2; };
    fclose(fp);
    return 0;
}

int safeToFile(const char* filename, const char* text, const char* separator) {
    if(!strlen(text)) { return 0; }
    if(!isFileExists(filename)) {
        if(createFile(filename)) { return -1; }
    }

    FILE* fp = fopen(filename, "a");
    fprintf(fp, "%s", text);
    fprintf(fp, "%s", separator);

    fclose(fp);
    return 0;
}

char* readFromFile(const char* filename, const int poemId, const char* separator) {
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) return NULL;

    size_t bufferSize = 128;
    const size_t maxLineLength = 64;
    char* poem = (char*)malloc(bufferSize * sizeof(char));
    if(poem == NULL) return NULL;
    poem[0] = '\0';

    char line[maxLineLength];

    int currentId = 1;
    size_t poemLength = 0;
    const size_t separatorLength = strlen(separator);
    while(poemId != currentId && fgets(line, maxLineLength, fp) != NULL) {
        if(strlen(line) >= separatorLength && strstr(line, separator) != NULL) {
            currentId += 1;
        }
    }
    while(fgets(line, maxLineLength, fp) != NULL && strcmp(line, separator)) {
        size_t lineLength = strlen(line);
        if(strlen(line) >= separatorLength && strstr(line, separator) != NULL) { break; }
        if(lineLength > bufferSize - poemLength) {
            bufferSize *= 2;
            char* poem = (char*)realloc(poem, bufferSize * sizeof(char));
            if(poem == NULL) return NULL;
        }

        poemLength += lineLength;
        strcat(poem, line);
    }

    fclose(fp);
    return poem;
}
