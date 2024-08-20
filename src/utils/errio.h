#pragma once

#include <stdio.h>

#define perrorf(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
