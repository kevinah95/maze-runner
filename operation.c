#include <stdlib.h>
#include "operation.h"
#include "vector.h"

void move(Array *a,ThreadData data,const char *maze, int width, int height){

    int x = data.future_x_pos;
    int y = data.future_y_pos;
    int movementCount = data.accumulated_movements;
    int dir = data.future_direction;

    switch(dir){
        case 0:{
            int left = (x > 0) ? (x - 1) : x;
            int right = (x< width - 1) ? (x + 1) : x;

            for (unsigned yl = y+1; yl-- > 0;) {
                char left_flag = vector_get(*maze,left + width * y);
                if (left_flag == ' ') {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = left;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 3;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(&a,data_c);
                }

                char right_flag = vector_get(*maze,(right + width * y));
                if (right_flag == ' ') {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = right;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 1;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(&a,data_c);
                }
                if (vector_get(*maze,(x + width * y)) == ' ') {
                    y = yl-1;
                    movementCount++;
                }
                else{
                    return;
                }
            }

        }break;
        case 1:{
            int up = (y > 0) ? (y - 1) : y;
            int down = (y < height - 1) ? (y + 1) : y;
            for (int xl=x ; xl < width; xl++) {
                char up_flag = vector_get(*maze,(x + width * up));
                if (up_flag == ' ') {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = up;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 0;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(&a,data_c);
                }

                char down_flag = vector_get(maze,(x + width * down));
                if (down_flag == ' ') {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = down;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 2;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(&a,data_c);
                }
                if (vector_get(*maze,(x + width * y)) == ' ') {
                    x = xl+1;
                    movementCount++;
                }
                else{
                    return;
                }
            }
        }break;

        case 2:{
            int left = (x > 0) ? (x - 1) : x;
            int right = (x < width - 1) ? (x + 1) : x;
            //-------------
            for (int yl = y; yl < height; yl++) {
                char left_flag = vector_get(*maze,left + width * y);
                if (left_flag == ' ') {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = left;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 3;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(&a,data_c);
                }

                char right_flag = vector_get(*maze,(right + width * y));
                if (right_flag == ' ') {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = right;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 1;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(&a,data_c);
                }
                if (vector_get(*maze,(x + width * y)) == ' ') {
                    y = yl+1;
                    movementCount++;
                }
                else {
                    return;
                }
            }
        }break;

        case 3:{
            int up = (y > 0) ? (y - 1) : y;
            int down = (y < height - 1) ? (y + 1) : y;
            for (unsigned xl = x+1; xl-- > 0;) {
                char up_flag = vector_get(maze, (x + width * up));
                if (up_flag == ' ') {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = up;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 0;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(&a,data_c);
                }

                char down_flag = vector_get(maze,(x + width * down));
                if (down_flag == ' ') {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = down;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 2;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(&a,data_c);
                }
                if (vector_get(maze,(x + width * y)) == ' ') {
                    x = xl-1;
                    movementCount++;
                } else {
                    return;
                }
            }
        }break;
    }
}
