#include <stdio.h>
#include <stdlib.h>
#include<omp.h>
#define NUM_THREADS 2
FILE *image, *imageGray, *lecturas,*imageFlipHorizontal,*imageFlipVertical;

unsigned char r, g, b;               //Pixel
unsigned char* ptr,* ptr1;
int cuenta = 0;

void RGBtoGray(FILE *image,long ancho,long alto);
void FlipHorizontal(FILE *image,long ancho,long alto);
void FlipVertical(FILE *image,long ancho,long alto);

int main()
{
    const double startTime = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
    printf("Numero de THREADS: %d. \n", NUM_THREADS); 

    image = fopen("one-piece-burning-blood-button-01ajpg-b6a236.bmp","rb");          //Imagen original a transformar
    imageGray = fopen("ImageGray.bmp","wb");    //Imagen transformada en escala de grises
    imageFlipHorizontal=fopen("ImageHorizontal.bmp","wb");
    imageFlipVertical=fopen("ImageVertical.bmp","wb");

    long ancho;
    long alto;
    int avgB = 0, avgG = 0, avgR = 0;
    int ile = 0;


    unsigned char xx[54];

    for(int i=0; i<54; i++) {
        xx[i] = fgetc(image);
        fputc(xx[i], imageGray);   
        // fputc(xx[i], imageFlipHorizontal);
        // fputc(xx[i], imageFlipVertical);//Copia cabecera a nuevas imagenes
    }


    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);

    (void)RGBtoGray(image,alto,ancho);
    //(void)FlipVertical(image,alto,ancho);
    //(void)FlipHorizontal(image,alto,ancho);

    
    //fclose(imageFlipVertical); 
    //fclose(imageFlipHorizontal); 


    const double endTime = omp_get_wtime();
    printf("tomo (%lf) segundos\n", (endTime - startTime));
    
}

void RGBtoGray(FILE *image,long ancho,long alto){

ptr = (unsigned char*)malloc(alto*ancho*3* sizeof(unsigned char));

 while(!feof(image)){

        b = fgetc(image);
        g = fgetc(image);
        r = fgetc(image);
            
        unsigned char pixel = 0.21*r+0.72*g+0.07*b;

        ptr[cuenta]= pixel; //b
        ptr[cuenta+1] = pixel; //g
        ptr[cuenta+2] = pixel; //r
        cuenta++;
    }
    
    for(int xx = 0; xx < ancho; xx++){
        for(int yy = 0; yy < alto; yy++){
            fputc(ptr[(xx) * ancho + (yy) ], imageGray);
            fputc(ptr[(xx) * ancho + (yy) + 1], imageGray);
            fputc(ptr[(xx) * ancho + (yy) + 2], imageGray);
        }
    }
    free(ptr);
    fclose(image);
    fclose(imageGray);
}

void FlipVertical(FILE *image,long ancho,long alto){


//"x" van a ser mis columnas, "y" las filas
    for(int xx = alto; xx > 0; xx--){
        for(int yy = ancho; yy > 0; yy--){
            fputc(ptr[(xx) * ancho + (yy) ], imageFlipVertical);
            fputc(ptr[(xx) * ancho + (yy) + 1], imageFlipVertical);
            fputc(ptr[(xx) * ancho + (yy) + 2], imageFlipVertical);
        }
    }

}

void FlipHorizontal(FILE *image,long ancho,long alto){

//"x" van a ser mis columnas, "y" las filas
    for(int xx = 0; xx < ancho; xx++){
        for(int yy = 0; yy < alto; yy++){
            fputc(ptr[(yy) * ancho + (xx) ], imageFlipHorizontal);
            fputc(ptr[(yy) * ancho + (xx) + 1], imageFlipHorizontal);
            fputc(ptr[(yy) * ancho + (xx) + 2], imageFlipHorizontal);
        }
    }

}