#include <stdio.h>
#include <omp.h>//Se agregan las librerias adecuadas, debido a que utilizaremos OMP nesecitaremos utilizar la libreria de OMP mas concretamente el archivo omp.h
#include <math.h>
FILE *fptr;

#define NUM_THREADS 6//Elegimos la cantidad de Threads a utilizar para nuestro programa, esto es nesecario en cada uno de nuestros codigos para que el codigo sepa cuantos hilos a utilizar por el programa

int main()
{
int N = 10000000;//Se eligen el numero de pasos que utilizaremos en nuestro programa para el metodo de euler

fptr=fopen("Euler_n_01.txt","w");
printf("Numero de pasos:%d \n", N);
fprintf(fptr, "Datos que encuentra el metodo de Euler(variable ind.\t variable dep.\t numero de thread)\n");
    double h,t[N],w[N],ab;
    int thrd[N];
    double w0=0.5,a=0,b=2;
    double t1, t2, tiempo;
    int i;
    omp_set_num_threads(NUM_THREADS);//Esta linea de codigo nos especifica la cantidad de threads que utilizaremos durante la ejecuccion en paralelo de nuestro programa
    const double startTime = omp_get_wtime();//La funcion omp_get_wtime nos ayuda a medir la respuesta del sistema, en este caso la utilizamos al inicio y final de nuestro programa para poder calcular cuanto tiempo tarda todo el programa en correr.
    #pragma omp parallel//Esta directiva nos permite realizar programas en paralelo dando la instruccion de manera explicita de compilar la parte de codigo de manera paralela. 
    {    
    h=(b-a)/N;
    w[0] = w0;
    t[0] = a;
    for(i=0;i<N;i++){
        thrd[i] = omp_get_thread_num();
        t[i]=a+(h*i);
        w[i]=w[i-1]+h*(1+t[i-1]*t[i-1]-w[i-1]);
       }
    }

    const double endTime = omp_get_wtime();//La funcion omp_get_wtime nos ayuda a medir la respuesta del sistema, en este caso la utilizamos al inicio y final de nuestro programa para poder calcular cuanto tiempo tarda todo el programa en correr.
  
    for(i=0;i<N;i++){
        fprintf(fptr, "%f\t %lf\t thread: %d\n", t[i], w[i], thrd[i]);
    }
    printf("tomo (%lf) segundos\n",(endTime-startTime));

fclose(fptr);
}