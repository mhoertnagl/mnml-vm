#ifndef ERRIO_H
#define ERRIO_H

#include <stdio.h>

#define perrorf(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)

#endif