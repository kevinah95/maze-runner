#include "thread.h"
#include "thread.h"
#include "utils.h"

Vector readFile(Vector vector, int *width, int *height){
    char dir [256];
    printf("Ingrese la dirección del archivo con el laberinto:\n>>");
    gets(dir);

    //Lectura del archivo
    FILE *fp;
    char c;
    int n = 0;
    int filas = 0;
    int columnas = 0;

    fp = fopen(dir,"r");
    if(fp == NULL)
    {
        perror("Error in opening file");
    }

    //Instanciación de las variables numRows (height) y numCols (width)

    do
    {
        c = fgetc(fp);
        if( feof(fp) )
        {
            break ;
        }
        //Se agregan los demás caracteres al vector
        if (c != '\n'){
            vector_append(&vector, c);
            n++;

        }
        else {
            filas++;
        }
    }while(1);

    printf("\nElementos: ");
    printf("%d",n);

    columnas = n / filas;

    *width = columnas;
    *height = filas;

    fclose(fp);
    return vector;
}

void move(Array *a,ThreadData data,const char *maze, int width, int height){

    int x = data.future_x_pos;
    int y = data.future_y_pos;
    int movementCount = data.accumulated_movements;
    int dir = data.future_direction;
    
    switch(dir){
        case 0:
            int left = (x > 0) ? (x - 1) : x;
            int right = (x< width - 1) ? (x + 1) : x;

            for (unsigned yl = y+1; yl-- > 0;) {
                if (vector_get(*maze,(x + width * y)) == ' ') {
                    y = yl--;
                    movementCount++;
                }
                char left_flag = vector_get(*maze,left + width * y);
                if (left_flag == ' ') {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = left;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 3;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(a*,*data_c);
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
                    insertArray(a*,*data_c);
                }
            }
            break;
        case 1:
            int up = (y > 0) ? (y - 1) : y;
            int down = (y < height - 1) ? (y + 1) : y;
            for (int xl=x ; xl < width; xl++) {
                if (vector_get(*maze,(x + width * y)) == ' ') {
                    x = x++;
                    movementCount++;
                }
                char up_flag = vector_get(*maze,(x + width * up));
                if (up_flag == ' ') {
                    ThreadData *data_c;
                    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
                    data_c->future_x_pos = up;
                    data_c->future_y_pos = y;
                    data_c->future_direction = 0;
                    data_c->drawed = 0;
                    data_c->accumulated_movements = movementCount;
                    insertArray(a*,*data_c);
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
                    insertArray(a*,*data_c);
                }
            }
            break;
        case 2:
            break;
        case 3:
            break;
    }
}
