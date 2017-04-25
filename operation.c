#include <stdlib.h>
#include "operation.h"
#include "vector.h"
#include "thread.h"

int check_neighbor(int x, int y, int width, int height, enum Direction dir){
    switch (dir){
        case UP:
            return (y > 0) ? (y - 1) : y;
        case RIGHT:
            return (x < width - 1) ? (x + 1) : x;
        case DOWN:
            return (y < height - 1) ? (y + 1) : y;
        case LEFT:
            return (x > 0) ? (x - 1) : x;
        default: return 0;
    }
}

void move(Array *a, ThreadData *data, const char *maze, int width, int height) {

    int x = data->future_x_pos;
    int y = data->future_y_pos;
    int movementCount = data->accumulated_movements;
    enum Direction dir = data->future_direction;
    char sym = 'a' + (random() % 26);


    switch (dir) {
        case UP: {
            int left = check_neighbor(x,y,width,height,LEFT);
            int right = check_neighbor(x,y,width,height,RIGHT);
            data->start = y+1;
            for (unsigned yl = y + 1; yl-- > 0;) {
                y = yl;
                data->end = yl;
                if (vector_get(maze, (x + width * y)) == ' ') {
                    vector_set(maze, (x + width * y), sym);
                    movementCount++;
                } else {

                    return;
                }
                char left_flag = vector_get(maze, left + width * y);
                if (left_flag == ' ' && x > 0) {
                    ThreadData *data_c;
                    data_c = create_thread_data(left,y,movementCount,LEFT);
                    insertArray(a, data_c);
                }

                char right_flag = vector_get(maze, (right + width * y));
                if (right_flag == ' ' && x < (width - 1)) {
                    ThreadData *data_c;
                    data_c = create_thread_data(right,y,movementCount,RIGHT);
                    insertArray(a, data_c);
                }
            }

        }
            break;
        case RIGHT: {
            int up = check_neighbor(x,y,width,height,UP);
            int down = check_neighbor(x,y,width,height,DOWN);
            data->start = x;
            for (int xl = x; xl < width; xl++) {
                x = xl;
                data->end = xl;
                if (vector_get(maze, (x + width * y)) == ' ') {
                    vector_set(maze, (x + width * y), sym);
                    movementCount++;
                } else {

                    return;
                }
                char up_flag = vector_get(maze, (x + width * up));
                if (up_flag == ' ' && y > 0) {
                    ThreadData *data_c;
                    data_c = create_thread_data(x,up,movementCount,UP);
                    insertArray(a, data_c);
                }

                char down_flag = vector_get(maze, (x + width * down));
                if (down_flag == ' ' && y < (height - 1)) {
                    ThreadData *data_c;
                    data_c = create_thread_data(x,down,movementCount,DOWN);
                    insertArray(a, data_c);
                }
            }
            data->end = x+1;
        }
            break;

        case DOWN: {

            int left = check_neighbor(x,y,width,height,LEFT);
            int right = check_neighbor(x,y,width,height,RIGHT);
            //-------------
            data->start = y;
            for (int yl = y; yl < height; yl++) {
                y = yl;
                data->end = yl+1;
                if (vector_get(maze, (x + width * y)) == ' ') {
                    vector_set(maze, (x + width * y), sym);
                    movementCount++;
                } else {

                    return;

                }
                char left_flag = vector_get(maze, left + width * y);
                if (left_flag == ' ' && x > 0) {
                    ThreadData *data_c;
                    data_c = create_thread_data(left, y, movementCount, LEFT);
                    insertArray(a, data_c);
                }

                char right_flag = vector_get(maze, (right + width * y));
                if (right_flag == ' ' && x < (width - 1)) {
                    ThreadData *data_c;
                    data_c = create_thread_data(right, y, movementCount, RIGHT);
                    insertArray(a, data_c);
                }
            }
            data->end = y+1;
        }
            break;

        case LEFT: {
            int up = check_neighbor(x,y,width,height,UP);
            int down = check_neighbor(x,y,width,height,DOWN);
            data->start = x+1;
            for (unsigned xl = x + 1; xl-- > 0;) {
                x = xl;
                data->end = xl;
                if (vector_get(maze, (x + width * y)) == ' ') {
                    vector_set(maze, (x + width * y), sym);
                    movementCount++;
                } else {

                    return;
                }
                char up_flag = vector_get(maze, (x + width * up));
                if (up_flag == ' ' && y > 0) {
                    ThreadData *data_c;
                    data_c = create_thread_data(x,up,movementCount,UP);
                    insertArray(a, data_c);
                }

                char down_flag = vector_get(maze, (x + width * down));
                if (down_flag == ' ' && y < (height - 1)) {
                    ThreadData *data_c;
                    data_c = create_thread_data(x,down,movementCount,DOWN);
                    insertArray(a, data_c);
                }
            }
        }
            break;
        default: printf("------");
            break;
    }
}
