#ifndef POEM_H
#define POEM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "poem_container.c"

void run(const char* filename);
Poem* readPoemFromConsole(void);
int readNumberFromConsole(void);

void MemoryAllocationException(void);
void IOException(void);

struct Poem {
    char* title;
    char* content;
};

typedef struct Poem Poem;

#endif