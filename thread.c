#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "thread.h"
#include "utils.h"

void initArray(Array *a, size_t initialSize) {
    a->array = (ThreadData *) malloc(initialSize * sizeof(ThreadData));
    a->size = 0;
    a->mem_size = initialSize;
}

void insertArray(Array *a, ThreadData *element) {
    // a->size is the number of size entries, because a->array[a->size++] updates a->size only *after* the array has been accessed.
    // Therefore a->size can go up to a->mem_size
    if (a->size == a->mem_size) {
        a->mem_size *= 2;
        a->array = (ThreadData *) realloc(a->array, a->mem_size * sizeof(ThreadData));
    }
    a->array[a->size++] = *element;
}

void freeArray(Array *a) {
    free(a->array);
    a->array = NULL;
    a->size = a->mem_size = 0;
}

void print_in_maze(ThreadData *p_data) {

    int is_reverse = 1;
    if (p_data->future_direction == DOWN) {
        int start = 0;
        int end = 5;
        char *to_print = 'D';
        reverse_loop_immutable_coord_x(start, end, !is_reverse, p_data->future_x_pos, to_print);
    }
    if (p_data->future_direction == RIGHT) {
        int start = 1;
        int end = 3;
        char *to_print = 'R';
        reverse_loop_immutable_coord_y(start,end, !is_reverse, p_data->future_y_pos, to_print);
    }
    if (p_data->future_direction == UP) {
        int start = 4;
        int end = 0;
        char *to_print = 'U';
        reverse_loop_immutable_coord_x(start,end, is_reverse, p_data->future_x_pos, to_print);
    }
    if (p_data->future_direction == LEFT) {
        char *to_print = 'L';
    }


}

/*
 * Reverse the order in a FOR loop: http://stackoverflow.com/a/3586329
 */
void reverse_loop_immutable_coord_x(int start_y_pos,int end_y_pos, int is_reverse, int immutable_coord_x, char *to_print) {
    if(!is_reverse) for( int i=start_y_pos;i<end_y_pos;i++) print_in_coordinates(immutable_coord_x, i, to_print);
    else{int i=start_y_pos; while(i-- > end_y_pos) print_in_coordinates(immutable_coord_x, i, to_print);}
}

void reverse_loop_immutable_coord_y(int start_x_pos,int end_x_pos, int is_reverse, int immutable_coord_y, char *to_print) {
    if(!is_reverse) for( int i=start_x_pos;i<end_x_pos;i++) print_in_coordinates(i, immutable_coord_y, to_print);
    else{int i=start_x_pos; while(i-- > end_x_pos) print_in_coordinates(i, immutable_coord_y, to_print);}
}


void print_in_coordinates(int x, int y, char *to_print) {
    gotoxy(x, y);
    printf("%c", to_print);
    fflush(stdout);
    usleep(SECOND);
}