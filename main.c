#include <stdio.h>
#include "vector.c"
#include "utilities.h"


int main() {
    //Lectura de la dirección del archivo
    int width = 0;
    int height = 0;
    Vector vector;
    vector_init(&vector);
    vector = readFile(vector,&width, &height);

    return(0);

}