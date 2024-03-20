#ifndef POEM_COLLECTOR_H
#define POEM_COLLECTOR_H

#include "poem.h"
#include "poem_container.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void run(const char* filename);
Poem* readPoemFromConsole(void);
int readNumberFromConsole(void);
void trim(char* str);

void MemoryAllocationException(void);
void IOException(void);

#endif