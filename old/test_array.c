#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../thread.h"
#include "../utils.h"

int main() {
    /* Intializes random number generator */
    srand(time(0));

    Array a;
    int i;

    initArray(&a, 1);  // initially 5 elements
    ThreadData *data;
    data = (ThreadData *)malloc(1 * sizeof(ThreadData));
    data->future_direction = 10;
    ThreadData *data2;
    data2 = (ThreadData *)malloc(1 * sizeof(ThreadData));
    data2->future_direction = 11;
    insertArray(&a, data);  // automatically resizes as necessary
    insertArray(&a, data2);  // automatically resizes as necessary
    free(data2);
    printf("%d\n", a.array[1].future_direction);  // print 10th element
    printf("%d\n", a.size);  // print number of elements
    printf("%d\n", a.mem_size);  // print number of elements
    freeArray(&a);

    return 0;
}