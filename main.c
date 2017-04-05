#include <stdio.h>
#include <pthread.h>
#include <memory.h>
#include "vector.c"
#include "utils.h"
#include "thread.h"
#include "operation.h"

pthread_t *threads;

void* doSomeThing(ThreadData *p_data)
{

    unsigned long i = 0;



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

    //show_maze(&vector,width,height);
    //----------------Array
    Array a;
    int i;


    //--data_a
    initArray(&a, 1);
    ThreadData *data_a;
    data_a = (ThreadData *)malloc(1 * sizeof(ThreadData));
    data_a->future_x_pos = 0;
    data_a->future_y_pos = 0;
    data_a->future_direction = 2;
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
    /*initArray(&a, 1);
    ThreadData *data_b;
    data_b = (ThreadData *)malloc(1 * sizeof(ThreadData));
    data_b->future_x_pos = 4;
    data_b->future_y_pos = 1;
    data_b->future_direction = 1;
    data_b->drawed = 0;
    data_b->accumulated_movements = 5;
    insertArray(&a, data_b);
    //--data_c
    initArray(&a, 1);
    ThreadData *data_c;
    data_c = (ThreadData *)malloc(1 * sizeof(ThreadData));
    data_c->future_x_pos = 0;
    data_c->future_y_pos = 0;
    data_c->future_direction = 2;
    data_c->drawed = 0;
    data_c->accumulated_movements = 0;
    insertArray(&a, data_c);
    int num_trues =0;
    int index_array = 0;
    //---------1fst Thread
    threads=(pthread_t *)malloc(1 * sizeof(pthread_t ));
    int index_threads = 0;


    //----------------While
    while (index_array < a.size){
        if(index_threads==0){
            err = pthread_create(&(threads[index_threads]), NULL, &doSomeThing, &a.array[index_array]);
            if (err != 0)
                printf("\ncan't create thread :[%s]", strerror(err));
            else
                printf("\n Thread %d created successfully\n",index_threads+1);
            index_threads++;
        } else{
            threads =(pthread_t *)realloc(threads,sizeof ( pthread_t )*(index_threads+1)) ;
            if(threads==NULL)
                printf("error with realloc");
            err = pthread_create(&(threads[index_threads]), NULL, &doSomeThing, &a.array[index_array]);
            if (err != 0)
                printf("\ncan't create thread :[%s]", strerror(err));
            else
                printf("\n Thread %d created successfully\n",index_array);
            index_threads++;
        }

        index_array++;
    }
    //----------------

    i = 0;
    while(i < index_threads)
    {
        pthread_join(threads[i], NULL);
        pthread_join(threads[i], NULL);
        i++;
    }*/
    //---------------

    freeArray(&a);
    return(0);

}