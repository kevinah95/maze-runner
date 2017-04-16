#include <stdio.h>
#include <pthread.h>
#include <memory.h>
#include <unistd.h>
#include "vector.c"
#include "utils.h"
#include "thread.h"

pthread_t *threads;
pthread_mutex_t lock;
int index_threads = 0;
int index_array = 0;


void* doOtherThing(ThreadData *p_data)
{
    unsigned long i = 0;

    //for(i=0; i<(0xFFFF);i++);

    //printThreadData(p_data);
    /*if (p_data->future_direction == LEFT){
        sleep(1);
        printf("-----------left(%d)",index_threads);
        printf("Well blue");
    }*/
    pthread_mutex_lock(&lock);
    print_in_maze(p_data);
    pthread_mutex_unlock(&lock);
    //printf("\nThread %d processing done\n",);
    return NULL;
}

void* doSomeThing(ThreadData *p_data)
{
    unsigned long i = 0;

    //for(i=0; i<(0xFFFF);i++);

    //printThreadData(p_data);
    /*if(p_data->future_direction == LEFT){
        ThreadData *data_b;
        data_b = (ThreadData *)malloc(1 * sizeof(ThreadData));
        data_b->future_x_pos = 1;
        data_b->future_y_pos = 4;
        data_b->future_direction = LEFT;
        data_b->drawed = 0;
        data_b->accumulated_movements = 5;
        int err;

        threads =(pthread_t *)realloc(threads,sizeof ( pthread_t )*(index_threads+1)) ;
        if(threads==NULL)
            printf("error with realloc");
        err = pthread_create(&(threads[index_threads]), NULL, &doOtherThing, data_b);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        *//*else
            printf("\n Thread %d created successfully\n",index_array);*//*
        //pthread_join(threads[index_threads], NULL);

        //pthread_join(threads[index_threads], NULL);
        index_threads++;
    } else{*/
    pthread_mutex_lock(&lock);
    print_in_maze(p_data);
    pthread_mutex_unlock(&lock);
    //}



    //printf("\nThread %d processing done\n",);
    return NULL;
}

int main() {
    //Lectura de la dirección del archivo
    int width = 0;
    int height = 0;
    int err;
    Vector vector;
    vector_init(&vector);
    vector = readFile(vector,&width, &height);

    printf("\nFilas: ");
    printf("%d",height);

    printf("\nColumnas: ");
    printf("%d",width);

    show_maze(&vector,width,height);
    printf("\n");
    printf("\n");
    //----------------Array

    usleep(SECOND);
    Array a;
    int i;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }


    //--data_a
    initArray(&a, 1);
    ThreadData *data_a;
    data_a = (ThreadData *)malloc(1 * sizeof(ThreadData));
    data_a->future_x_pos = 0;
    data_a->future_y_pos = 0;
    data_a->future_direction = DOWN;
    data_a->drawed = 0;
    data_a->accumulated_movements = 0;
    insertArray(&a, data_a);

    printf("\n");
    show_maze(&vector,width,height);
    int i_dir = 0;



    //RPOBLEMA: OCUPO PASAR a.array[i_dir] como data_a en la línea 54
    while (i_dir < a.size){
        move(&a,&a.array[i_dir],&vector,width,height);
        printf("\n");
        show_maze(&vector,width,height);
        printf("\nTamaño: %d",a.size);
        i_dir++;
    }

    /*for (int i = 0 ; i<a.size;i++){
        printf("%d",a.array->accumulated_movements);
    }*/


    //--data_b
    ThreadData *data_b;
    data_b = (ThreadData *)malloc(1 * sizeof(ThreadData));
    data_b->future_x_pos = 1;
    data_b->future_y_pos = 4;
    data_b->future_direction = RIGHT;
    data_b->drawed = 0;
    data_b->accumulated_movements = 5;
    insertArray(&a, data_b);
    //--data_c
    ThreadData *data_c;
    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
    data_c->future_x_pos = 2;
    data_c->future_y_pos = 3;
    data_c->future_direction = UP;
    data_c->drawed = 0;
    data_c->accumulated_movements = 7;
    insertArray(&a, data_c);
    int num_trues =0;

    //---------1fst Thread
    threads=(pthread_t *)malloc(1 * sizeof(pthread_t ));


    i = 0;
    //----------------While
    while (i < a.size){
        if(index_threads==0){
            err = pthread_create(&(threads[index_threads]), NULL, &doSomeThing, &a.array[i]);
            if (err != 0)
                printf("\ncan't create thread :[%s]", strerror(err));
            /*else
                printf("\n Thread %d created successfully\n",index_threads);*/
            //pthread_join(threads[index_threads], NULL);
            index_threads++;
        } else{
            threads =(pthread_t *)realloc(threads,sizeof ( pthread_t )*(index_threads+1)) ;
            if(threads==NULL)
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
    while(i < index_threads)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    //---------------

    for (int j = 0; j < height*2; ++j) {
        printf("\n");
    }

    pthread_mutex_destroy(&lock);
    freeArray(&a);
    return(0);

}
