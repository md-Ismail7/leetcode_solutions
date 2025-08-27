#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *memory; // memory[i] = mID or -1 if free
    int size;
} Allocator;

Allocator* allocatorCreate(int n) {
    Allocator *obj = (Allocator*)malloc(sizeof(Allocator));
    obj->size = n;
    obj->memory = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        obj->memory[i] = -1; // all free initially
    }
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    int count = 0;
    int start = -1;

    for (int i = 0; i < obj->size; i++) {
        if (obj->memory[i] == -1) {
            if (count == 0) start = i; // mark start of free block
            count++;
            if (count == size) {
                for (int j = start; j < start + size; j++) {
                    obj->memory[j] = mID;
                }
                return start; // return starting index
            }
        } else {
            count = 0; // reset consecutive count
        }
    }
    return -1; // no free block found
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int freed = 0;
    for (int i = 0; i < obj->size; i++) {
        if (obj->memory[i] == mID) {
            obj->memory[i] = -1;
            freed++;
        }
    }
    return freed;
}

void allocatorFree(Allocator* obj) {
    free(obj->memory);
    free(obj);
}




