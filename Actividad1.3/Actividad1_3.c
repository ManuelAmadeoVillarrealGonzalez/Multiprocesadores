#include<stdio.h>
#include "omp.h"//Se agregan las librerias adecuadas, debido a que utilizaremos OMP nesecitaremos utilizar la libreria de OMP mas concretamente el archivo omp.h
#define NUM_THREADS 18//Elegimos la cantidad de Threads a utilizar para nuestro programa, esto es nesecario en cada uno de nuestros codigos para que el codigo sepa cuantos hilos a utilizar por el programa

int main()
{
    omp_set_num_threads(NUM_THREADS);//Esta linea de codigo nos especifica la cantidad de threads que utilizaremos durante la ejecuccion en paralelo de nuestro programa
    #pragma omp parallel//Esta directiva nos permite realizar programas en paralelo dando la instruccion de manera explicita de compilar la parte de codigo de manera paralela. 
    {
        int ID = omp_get_thread_num();//obtenemos el numero de thread que estamos utilizando en este momento.
        printf("Procesadores(%d)\n", ID);
        printf("Multiples(%d)\n", ID);
        printf("en accion(%d)----\n", ID);
    }
}