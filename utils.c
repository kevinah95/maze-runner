#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "vector.h"

unsigned int rand_interval(unsigned int min, unsigned int max) {
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

void gotoxy(int x,int y){
    x+=1;
    y+=1;
    printf("%c[%d;%df",0x1B,y,x);
}

char get_random_character(){
    return 'a' + (random() % 26);
}

int get_random_int(){
    return rand_interval(0,7);
}

void show_maze(const char *maze, int width, int height) {
    int x, y;
    clear();
    for (y = 0; y < height; y++) {
        //int rand_num =  rand_interval(0,7);
        for (x = 0; x < width; x++) {
            gotoxy(x,y);
            printf("%c", vector_get(maze,x + width * y));
            /*fflush(stdout);
            usleep(SECOND);*/
            /*switch(maze[y * width + x]) {
                case '#':  printf("[]");  break;
                case ' ':  printf("  ");  break;
                //default: printf("%c%c", maze[x + width * y],maze[x + width * y]);  break;
                default: PRINTC (rand_num, "%c%c", maze[x + width * y],maze[x + width * y]);  break;
            }*/
        }
    }
}



