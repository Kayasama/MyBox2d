#ifndef B2_STACK_ALLOCATOR_H
#define B2_STACK_ALLOCATOR_H

#include "b2_api.h"
#include "b2_settings.h"

const int32 b2_stackSize = 100 * 1024;
const int32 b2_maxStackEntries = 32;

struct B2_API b2StackEntry
{
    char* data;
    int32 size;
    bool usedMalloc;
};

class B2_API b2StackAllocator
{

};


#endif