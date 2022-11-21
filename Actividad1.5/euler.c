#include <stdio.h>
#include <omp.h>//Se agregan las librerias adecuadas, debido a que utilizaremos OMP nesecitaremos utilizar la libreria de OMP mas concretamente el archivo omp.h
#include <math.h>
#define NUM_THREADS 6//Elegimos la cantidad de Threads a utilizar para nuestro programa, esto es nesecario en cada uno de nuestros codigos para que el codigo sepa cuantos hilos a utilizar por el programa
int N = 1000000/6;//Se eligen el numero de pasos que utilizaremos en nuestro programa para el metodo de euler

   FILE *fptr;
   FILE *fptr1;
   FILE *fptr2;
   FILE *fptr3;
   FILE *fptr4;
   FILE *fptr5; //Dependiendo del numero de threads crearemos la cantidad correspondiente de archivos nesecarios para poder visualizar los valores de cada uno de los threads correspondientes

void Euler(int N,FILE *x);//Creamos la funcion iteracion que sera utilizada despues en cada una de nuestras secciones del codigo


int main()
{  
  omp_set_num_threads(NUM_THREADS);//Esta linea de codigo nos especifica la cantidad de threads que utilizaremos durante la ejecuccion en paralelo de nuestro programa
  const double startTime = omp_get_wtime();//La funcion omp_get_wtime nos ayuda a medir la respuesta del sistema, en este caso la utilizamos al inicio y final de nuestro programa para poder calcular cuanto tiempo tarda todo el programa en correr.

  fptr=fopen("Euler_n_0.txt","w");
  fptr1=fopen("Euler_n_1.txt","w");
  fptr2=fopen("Euler_n_2.txt","w");
  fptr3=fopen("Euler_n_3.txt","w");
  fptr4=fopen("Euler_n_4.txt","w");
  fptr5=fopen("Euler_n_5.txt","w");//Creamos los archivos de texto que almacenaran cada uno de los valores obtenidos por el metodo de euler por thread a utilizar

  #pragma omp parallel//Esta directiva nos permite realizar programas en paralelo dando la instruccion de manera explicita de compilar la parte de codigo de manera paralela. 
{
    #pragma omp sections//Esta directiva nos permite realizar diferentes tareas para cada uno de los threads que nosotros utilizaremos, en este caso como definimos 6 threads utilizaremos cada uno de ellos para realizar una tarea. En caso de no tener suficientes secciones los threads que no se utilizan se quedan esperando sin realizar accion alguna
    {
       #pragma omp section//Dividimos las secciones que utilizaremos en nuestro programa, debido a que tenemos 6 threads utilizaremos 6 secciones para que cada thread realice una tarea de manera independiente. Y vamos de manera ascendente donde la primera seccion utilizara el primer thread y asi de manera sucesiva
         (void)Euler(N,fptr);//Corremos la funcion Euler que se encargara de realizar los calculos para el metodo de euler
       #pragma omp section
         (void)Euler(N,fptr1);//Para esta funcion recibiremos 2 variables, N que sera el numero de pasos previamente definido y fptr que sera el puntero de cada uno de los archivos de texto que creamos con anterioridad
       #pragma omp section
         (void)Euler(N,fptr2);
       #pragma omp section
         (void)Euler(N,fptr3);
       #pragma omp section
         (void)Euler(N,fptr4);
       #pragma omp section
         (void)Euler(N,fptr5);
   }
}
  const double endTime = omp_get_wtime();//La funcion omp_get_wtime nos ayuda a medir la respuesta del sistema, en este caso la utilizamos al inicio y final de nuestro programa para poder calcular cuanto tiempo tarda todo el programa en correr.
  printf("tomo (%lf) segundos\n",(endTime-startTime));
  fclose(fptr);
  fclose(fptr1);
  fclose(fptr2);
  fclose(fptr3);
  fclose(fptr4);
  fclose(fptr5);//Una vez hayamos terminado con todos los valores obtenidos, cerraremos los archivos obtenidos para poder hacer la inspeccion de los datos correspondientes
  return (0);}

void Euler(int N, FILE *x){//Funcion de Euler que se encargara de realizar los calculos correspondientes del metodo de euler
	printf("Numero de pasos:%d Atendido por thread:%d\n", N,omp_get_thread_num());
	fprintf(x, "Datos que encuentra el metodo de Euler(variable ind.\t variable dep.\t numero de thread)\n");
      double h,t,w,ab;
      double w0=0.5,a=0,b=2;
      int i;
      w=w0;
      fprintf(x, "%f\t %f\n", a, w);
      for(i=0;i<N;i++){
          h=(b-a)/N;
          t=a+(h*i);
          ab=t*t;//utilizamos una variable para hacer el calculo de t^2
          w=w+h*(1+(ab-w,2)); //La aplicacion del metodo de Euler nos entrega: ωi+1 = ω + h(ω −t^2 + 1)
          fprintf(x, "%f\t %f \t numero de thread:%d\n", t+h, w,omp_get_thread_num());
         } 
  }
