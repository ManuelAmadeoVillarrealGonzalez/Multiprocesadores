#include <stdio.h>
#include <omp.h>//Se agregan las librerias adecuadas, debido a que utilizaremos OMP nesecitaremos utilizar la libreria de OMP mas concretamente el archivo omp.h
#include <math.h>

FILE *fptr;

int N = 1000000/6;//Se eligen el numero de pasos que utilizaremos en nuestro programa para el metodo de euler
#define NUM_THREADS 6//Elegimos la cantidad de Threads a utilizar para nuestro programa, esto es nesecario en cada uno de nuestros codigos para que el codigo sepa cuantos hilos a utilizar por el programa

void Euler(int N,FILE *x,int j);//Creamos la funcion Euler que sera utilizada despues en cada una de nuestras secciones del codigo

int main()
{
    omp_set_num_threads(NUM_THREADS);//Esta linea de codigo nos especifica la cantidad de threads que utilizaremos durante la ejecuccion en paralelo de nuestro programa
    const double startTime = omp_get_wtime();//La funcion omp_get_wtime nos ayuda a medir la respuesta del sistema, en este caso la utilizamos al inicio y final de nuestro programa para poder calcular cuanto tiempo tarda todo el programa en correr.
    fptr=fopen("Euler_n_0.txt","w");
    #pragma omp parallel//Esta directiva nos permite realizar programas en paralelo dando la instruccion de manera explicita de compilar la parte de codigo de manera paralela. 
    {
     #pragma omp sections//Esta directiva nos permite realizar diferentes tareas para cada uno de los threads que nosotros utilizaremos, en este caso como definimos 6 threads utilizaremos cada uno de ellos para realizar una tarea. En caso de no tener suficientes secciones los threads que no se utilizan se quedan esperando sin realizar accion alguna
        {
       #pragma omp section//Dividimos las secciones que utilizaremos en nuestro programa, debido a que tenemos 6 threads utilizaremos 6 secciones para que cada thread realice una tarea de manera independiente. Y vamos de manera ascendente donde la primera seccion utilizara el primer thread y asi de manera sucesiva
         (void)Euler(N,fptr,1);//Corremos la funcion Euler que se encargara de realizar los calculos para el metodo de euler
       #pragma omp section
         (void)Euler(N,fptr,2);
       #pragma omp section
         (void)Euler(N,fptr,3);
       #pragma omp section
         (void)Euler(N,fptr,4);
       #pragma omp section
         (void)Euler(N,fptr,5);
       #pragma omp section
         (void)Euler(N,fptr,6);
        }
    }
    const double endTime = omp_get_wtime();//La funcion omp_get_wtime nos ayuda a medir la respuesta del sistema, en este caso la utilizamos al inicio y final de nuestro programa para poder calcular cuanto tiempo tarda todo el programa en correr.
    printf("tomo (%lf) segundos\n",(endTime-startTime));
    fclose(fptr);  
}
void Euler(int N, FILE *ptr,int j){//Funcion de Euler que se encargara de realizar los calculos correspondientes del metodo de euler
    printf("Numero de pasos:%d \n", N);
    fprintf(fptr, "Datos que encuentra el metodo de Euler(variable ind.\t variable dep.\t numero de thread)\n");
    double h,t[N],w[N],ab;
    double w0=0.5,a=0,b=2;
    int i;
    h=(b-a)/N;
    w[0] = w0;
    t[0] = a;

    for(i=0;i<N;i++){
        t[i]=a+(h*i);
        w[i]=w[i-1]+h*(1+exp(t[i-1]*t[i-1])-exp(w[i-1]));
       }
    for(i=0;i<N;i++){
        fprintf(fptr, "%f\t %f\n en el thread numero %i\t", t[i], w[i],j);
    }
}