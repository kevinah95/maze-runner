#include <stdio.h>
#include <pthread.h>
#include <memory.h>
#include <semaphore.h>
#include <unistd.h>
#include <syscall.h>
#include "vector.c"
#include "utils.h"
#include "thread.h"
#include "operation.h"

pthread_t *threads;
pthread_mutex_t lock;
int index_threads = 0;
int index_array = 0;
Vector vector;
int width = 0;
int height = 0;
sem_t mySemaphore;
pthread_barrier_t barrier;
int cola_proc = 0;

int has_next(int cur_x, int cur_y, enum Direction dir) {
    switch (dir) {
        case DOWN: {
            int next_y = cur_y + 1;

            if (next_y < height) {
                if (vector_get(&vector, (cur_x + width * next_y)) != '#') {
                    return TRUE;
                }
            }
            return FALSE;
        }
            break;
        case RIGHT: {
            int next_x = cur_x + 1;

            if (next_x < width) {
                if (vector_get(&vector, (next_x + width * cur_y)) != '#') {
                    return TRUE;
                }
            }
            return FALSE;
        }
            break;
        case UP: {
            int next_y = cur_y - 1;

            if (next_y >= 0) {
                if (vector_get(&vector, (cur_x + width * next_y)) != '#') {
                    return TRUE;
                }
            }
            return FALSE;
        }
            break;
        case LEFT: {
            int next_x = cur_x - 1;

            if (next_x >= 0) {
                if (vector_get(&vector, (next_x + width * cur_y)) != '#') {
                    return TRUE;
                }
            }
            return FALSE;
        }
            break;

    }
}

int is_finish(int cur_x, int cur_y, enum Direction dir) {

    if (cur_y < height && cur_x < width && cur_y >= 0 && cur_x >= 0) {
        if (vector_get(&vector, (cur_x + width * cur_y)) == '/') {
            return TRUE;
        }
    }
    return FALSE;

}

void *doSomeThing(ThreadData *p_data) {
    pthread_mutex_lock(&lock);
    int movi = 0;
    switch (p_data->future_direction) {
        case DOWN: {
            int x = p_data->future_x_pos;
            int y = p_data->future_y_pos;
            while (has_next(x, y, DOWN)) {
                //sem_wait(&mySemaphore);
                print_in_coordinates(x, y, vector_get(&vector, x + width * y));
                //sem_post(&mySemaphore);
                movi++;
                y++;
            }

            //sem_wait(&mySemaphore);
            print_in_coordinates(x, y, vector_get(&vector, x + width * y));
            //sem_post(&mySemaphore);
            if (is_finish(x, y, DOWN)) {
                //sem_wait(&mySemaphore);
                gotoxy(width + 5, height + 5);
                printf("Se encontró una salida: x:%d y:%d movimientos:%d", x, y, p_data->accumulated_movements + movi);
                fflush(stdout);
                usleep(SECOND);
                //sem_post(&mySemaphore);
            }
        }
            break;
        case RIGHT: {
            int x = p_data->future_x_pos;
            int y = p_data->future_y_pos;
            while (has_next(x, y, RIGHT)) {
                //sem_wait(&mySemaphore);
                print_in_coordinates(x, y, vector_get(&vector, x + width * y));
                //sem_post(&mySemaphore);
                movi++;
                x++;
            }
            //sem_wait(&mySemaphore);
            print_in_coordinates(x, y, vector_get(&vector, x + width * y));
            //sem_post(&mySemaphore);
            if (is_finish(x, y, RIGHT)) {
                //sem_wait(&mySemaphore);
                gotoxy(width + 5, height + 5);
                printf("Se encontró una salida: x:%d y:%d movimientos:%d", x, y, p_data->accumulated_movements + movi);
                fflush(stdout);
                usleep(SECOND);
                //sem_post(&mySemaphore);
            }
        }
            break;
        case UP: {
            int x = p_data->future_x_pos;
            int y = p_data->future_y_pos;
            while (has_next(x, y, UP)) {
                //sem_wait(&mySemaphore);
                print_in_coordinates(x, y, vector_get(&vector, x + width * y));
                //sem_post(&mySemaphore);
                movi++;
                y--;
            }
            //sem_wait(&mySemaphore);
            print_in_coordinates(x, y, vector_get(&vector, x + width * y));
            //sem_post(&mySemaphore);
            if (is_finish(x, y, UP)) {
                //sem_wait(&mySemaphore);
                gotoxy(width + 5, height + 5);
                printf("Se encontró una salida: x:%d y:%d movimientos:%d", x, y, p_data->accumulated_movements + movi);
                fflush(stdout);
                usleep(SECOND);
                //sem_post(&mySemaphore);
            }
        }
            break;
        case LEFT: {
            int x = p_data->future_x_pos;
            int y = p_data->future_y_pos;
            while (has_next(x, y, LEFT)) {
                //sem_wait(&mySemaphore);
                print_in_coordinates(x, y, vector_get(&vector, x + width * y));
                //sem_post(&mySemaphore);
                movi++;
                x--;
            }
            //sem_wait(&mySemaphore);
            print_in_coordinates(x, y, vector_get(&vector, x + width * y));
            //sem_post(&mySemaphore);
            if (is_finish(x, y, LEFT)) {
                //sem_wait(&mySemaphore);
                gotoxy(width + 5, height + 5);
                printf("Se encontró una salida: x:%d y:%d movimientos:%d", x, y, p_data->accumulated_movements + movi);
                fflush(stdout);
                usleep(SECOND);
                //sem_post(&mySemaphore);
            }
        }
            break;
    }


    //sem_wait(&mySemaphore);
    gotoxy(width + 3, height + 3);
    printf("Thread treminado [getpid: %d getpthread_self: %lu tid:%lu]\n", getpid(), pthread_self(),
           syscall(SYS_gettid));
    fflush(stdout);
    usleep(SECOND);
    //sem_post(&mySemaphore);
    
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    //Lectura de la dirección del archivo
    int err;

    vector_init(&vector);
    vector = readFile(vector, &width, &height);
    clear();
    gotoxy(width + 1, height + 1);
    printf("Filas: %d Columnas:%d", height, width);
    fflush(stdout);
    usleep(SECOND);

    show_maze(&vector, width, height);
    printf("\n");
    printf("\n");
    //----------------Array

    usleep(SECOND);
    Array a;
    int i;
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init failed\n");
        return 1;
    }
    sem_init(&mySemaphore, 0, 0);

    //----------------------------------------------------------------------
    //--data_a
    initArray(&a, 1);
    ThreadData *data_a;
    data_a = (ThreadData *) malloc(1 * sizeof(ThreadData));
    data_a->future_x_pos = 0;
    data_a->future_y_pos = 0;
    data_a->future_direction = DOWN;
    data_a->drawed = 0;
    data_a->accumulated_movements = 0;
    insertArray(&a, data_a);

    int i_dir = 0;



    //RPOBLEMA: OCUPO PASAR a.array[i_dir] como data_a en la línea 54
    while (i_dir < a.size) {
        move(&a, &a.array[i_dir], &vector, width, height);
        usleep(SECOND);
        i_dir++;
    }
    //show_maze(&vector,width,height);
    pthread_barrier_init(&barrier, 0, a.size);

    /*i_dir = 0;
    while (i_dir < a.size) {
        printf("%d",a.array[i_dir].future_x_pos);//------------
        i_dir++;
    }*/


    /*for (int i = 0 ; i<a.size;i++){
        printf("%d",a.array->accumulated_movements);
    }*/



    //---------1fst Thread
    threads = (pthread_t *) malloc(1 * sizeof(pthread_t));
    int index_threads = 0;


    i = 0;
    //----------------While
    //sem_post(&mySemaphore);
    while (i < a.size) {
        if (index_threads == 0) {
            err = pthread_create(&(threads[index_threads]), NULL, &doSomeThing, &a.array[i]);
            if (err != 0)
                printf("\ncan't create thread :[%s]", strerror(err));
            /*else
                printf("\n Thread %d created successfully\n",index_threads);*/
            //pthread_join(threads[index_threads], NULL);
            index_threads++;
        } else {
            threads = (pthread_t *) realloc(threads, sizeof(pthread_t) * (index_threads + 1));
            if (threads == NULL)
                printf("error with realloc");
            err = pthread_create(&(threads[index_threads]), NULL, &doSomeThing, &a.array[i]);
            if (err != 0)
                printf("\ncan't create thread :[%s]", strerror(err));
            /*else
                printf("\n Thread %d created successfully\n",index_array);*/
            //pthread_join(threads[index_threads], NULL);
            index_threads++;
        }

        i++;
    }
    //----------------

    i = 0;
    while (i < index_threads) {
        pthread_join(threads[i], NULL);
        i++;
    }
    //---------------

    for (int j = 0; j < height; ++j) {
        printf("\n");
    }

    pthread_mutex_destroy(&lock);
    sem_destroy(&mySemaphore);
    pthread_barrier_destroy(&barrier);
    freeArray(&a);
    return (0);

}
