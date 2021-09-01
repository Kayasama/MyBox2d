#define _CRT_SECURE_NO_WARNINGS

#include ".\box2d\b2_settings.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void* b2Alloc_Default(int32 size)
{
    return malloc(size);
}

void b2Free_Default(void* mem)
{
    free(mem);
}