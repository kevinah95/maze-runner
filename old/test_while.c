#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../thread.h"
#include "../utils.h"

void fake_loop(int *p_counter,Array * array){
    int i;
    ThreadData *data;
    data = (ThreadData *)malloc(1 * sizeof(ThreadData));
    data->future_direction = 10;
    insertArray(array, data);
    for(i=0; i<(0xFFFF);i++);
    *p_counter +=2;

}

int main() {
    /* Intializes random number generator */
    srand(time(0));

    Array a;
    int i;

    initArray(&a, 1);  // initially 5 elements
    ThreadData *data;
    data = (ThreadData *)malloc(1 * sizeof(ThreadData));
    data->future_direction = 10;
    insertArray(&a, data);  // automatically resizes as necessary
    int counter;

    int only_one = 0;
    printf("%d\n", counter);
    while (counter!=a.size){
        if(only_one != 1)
            fake_loop(&counter,&a);
        only_one++;
    }

    printf("%d\n", a.array[0].future_direction);  // print 10th element
    printf("%d\n", a.size);  // print number of elements
    printf("%d\n", a.mem_size);  // print number of elements
    freeArray(&a);

    return 0;
}

