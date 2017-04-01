#include <stdlib.h>
#include <stdio.h>
#include "thread.h"

void initArray(Array *a, size_t initialSize) {
    a->array = (ThreadData *)malloc(initialSize * sizeof(ThreadData));
    a->size = 0;
    a->mem_size = initialSize;
}

void insertArray(Array *a, ThreadData *element) {
    // a->size is the number of size entries, because a->array[a->size++] updates a->size only *after* the array has been accessed.
    // Therefore a->size can go up to a->mem_size
    if (a->size == a->mem_size) {
        a->mem_size *= 2;
        a->array = (ThreadData *)realloc(a->array, a->mem_size * sizeof(ThreadData));
    }
    a->array[a->size++] = *element;
}

void freeArray(Array *a) {
    free(a->array);
    a->array = NULL;
    a->size = a->mem_size = 0;
}