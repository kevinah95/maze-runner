#include <stdlib.h>
#include "operation.h"
#include "vector.h"
#include "thread.h"

void move(Array *a, ThreadData *data, const char *maze, int width, int height){

    int x = data->future_x_pos;
    int y = data->future_y_pos;
    int movementCount = data->accumulated_movements;
    int dir = data->future_direction;
    char sym = (a->size) + '0';



    switch(dir){
        case 0:{
            int left = (x > 0) ? (x - 1) : x;
            int right = (x< width - 1) ? (x + 1) : x;

            for (unsigned yl = y+1; yl-- > 0;) {
                y = yl;
                if (vector_get(maze,(x + width * y)) == ' '){
                    vector_set(maze,(x + width * y),sym);
                    movementCount++;
                }
                else{
                    return;
                }
                char left_flag = vector_get(maze,left + width * y);
                if (left_flag == ' ' && x>0) {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = left;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 3;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(a,data_c);
                }

                char right_flag = vector_get(maze,(right + width * y));
                if (right_flag == ' ' && x<(width-1)) {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = right;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 1;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(a,data_c);
                }
            }

        }break;
        case 1:{
            int up = (y > 0) ? (y - 1) : y;
            int down = (y < height - 1) ? (y + 1) : y;
            for (int xl=x ; xl < width; xl++) {
                x = xl;
                if (vector_get(maze,(x + width * y)) == ' ') {
                    vector_set(maze,(x + width * y),sym);
                    movementCount++;
                }
                else{
                    return;
                }
                char up_flag = vector_get(maze,(x + width * up));
                if (up_flag == ' ' && y > 0) {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = x;
                    data_c->future_y_pos = up;
                    data_c->future_direction = 0;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(a,data_c);
                }

                char down_flag = vector_get(maze,(x + width * down));
                if (down_flag == ' ' && y < (height-1)) {
                    ThreadData *data_c;
                    data_c = (ThreadData *) malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = x;
                    data_c->future_y_pos = down;
                    data_c->future_direction = 2;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(a, data_c);
                }
            }
        }break;

        case 2:{
            int left = (x > 0) ? (x - 1) : x;
            int right = (x < width - 1) ? (x + 1) : x;
            //-------------
            for (int yl = y; yl < height; yl++) {
                y = yl;
                if (vector_get(maze,(x + width * y)) == ' ') {
                    vector_set(maze,(x + width * y),sym);
                    movementCount++;
                }
                else {
                    return;

                }
                char left_flag = vector_get(maze,left + width * y);
                if (left_flag == ' ' && x>0) {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = left;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 3;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(a,data_c);
                }

                char right_flag = vector_get(maze,(right + width * y));
                if (right_flag == ' ' && x<(width-1)) {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = right;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 1;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(a,data_c);
                }
            }
        }break;

        case 3:{
            int up = (y > 0) ? (y - 1) : y;
            int down = (y < height - 1) ? (y + 1) : y;
            for (unsigned xl = x+1; xl-- > 0;) {
                x = xl;
                if (vector_get(maze,(x + width * y)) == ' ') {
                    vector_set(maze,(x + width * y),sym);
                    movementCount++;
                } else {
                    return;
                }
                char up_flag = vector_get(maze, (x + width * up));
                if (up_flag == ' ' && y > 0) {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = x;
                    data_c->future_y_pos = up;
                    data_c->future_direction = 0;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(a,data_c);
                }

                char down_flag = vector_get(maze,(x + width * down));
                if (down_flag == ' ' && y < (height-1)) {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = x;
                    data_c->future_y_pos = down;
                    data_c->future_direction = 2;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(a,data_c);
                }
            }
        }break;
    }
}
