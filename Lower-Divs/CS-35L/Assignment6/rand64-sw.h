#ifndef RANDSW_H
#define RANDSW_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
    void software_rand64_init(const char* filepath);
    unsigned long long software_rand64(void);
    void software_rand64_fini(void);
    void mrand_rand64_init(void);
    unsigned long long mrand_rand64(void);
    void mrand_rand64_fini(void);
#endif