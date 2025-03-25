#ifndef OUTPUT_H
#define OUTPUT_H
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "rand64-hw.h"
#include "rand64-sw.h"
    bool writebytes(unsigned long long x, int nbytes);
    int handle_output(char *input, char *output, int nbytes);
#endif