//Este programa se encargara de calcular el valor de pi y nos dara el tiempo de respuesta obtenido por nuestra maquina, ademas de esto se utiliza la programacion en paralelo para ver como esto afecta el tiempo de respuesta

#include <stdio.h>
#include <omp.h>//Se agregan las librerias adecuadas, debido a que utilizaremos OMP nesecitaremos utilizar la libreria de OMP mas concretamente el archivo omp.h

static long num_pasos = 1000000000;//Se eligen el numero de pasos que utilizaremos en nuestro programa
double paso;
#define NUM_THREADS 1000//Elegimos la cantidad de Threads a utilizar para nuestro programa, esto es nesecario en cada uno de nuestros codigos para que el codigo sepa cuantos hilos a utilizar por el programa

void main(){
	int i, nthreads;
	double pi, sum[NUM_THREADS], t1, t2, tiempo; //Se crean las variables nesecarias que utilizaremos en la ejecuccion de nuestro codigo
	paso = 1.0/num_pasos;
	omp_set_num_threads(NUM_THREADS);
    const double startTime = omp_get_wtime();//La funcion omp_get_wtime nos ayuda a medir la respuesta del sistema, en este caso la utilizamos al inicio y final de nuestro programa para poder calcular cuanto tiempo tarda todo el programa en correr.
	
    #pragma omp parallel//Esta directiva nos permite realizar programas en paralelo dando la instruccion de manera explicita de compilar la parte de codigo de manera paralela. 
	{
		int i, id, nthrds;
		double x; //Se crean las variables nesecarias que utilizaremos en la ejecuccion de nuestro codigo dentro de la paralelizacion
		id = omp_get_thread_num();//obtenemos el thread que estamos utilizando en este momento.
		nthrds = omp_get_num_threads();//obtenemos el numero de threads que estamos utilizando en este momento.
		if(id == 0)
			nthreads = nthrds;
		for(i = id, sum[id]=0.0; i<num_pasos;i=i+nthrds){
			x=(i+0.5)*paso;
			sum[id]+=4.0/(1.0+x*x); //Recorremos el for haciendo uso del numero de pasos asi como tambien la cantidad de threads que utilizaremos en nuestro programa
		}
	}

	for(i=0, pi=0.0; i<nthreads; i++){
		pi+=sum[i]*paso;//Se calcula el valor de pi con cada uno de los threads a utilizar por el tamaño de paso correspondiente defino al inicio del programa
	}
	const double endTime = omp_get_wtime();//La funcion omp_get_wtime nos ayuda a medir la respuesta del sistema, en este caso la utilizamos al inicio y final de nuestro programa para poder calcular cuanto tiempo tarda todo el programa en correr.


	printf("pi = (%lf)\n", pi);
	printf("tomo (%lf) segundos\n", (endTime - startTime)); //Imprimos los valores obtenidos tanto por pi como el tiempo de respuesta
}