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

    printf("\nFilas: ");
    printf("%d",filas);

    printf("\nColumnas: ");
    columnas = n / filas;
    printf("%d",columnas);

    for (int i = 0 ; i < n ; i++){
        printf("%c",vector_get(&vector, i));
    }
    fclose(fp);
    return vector;
}
