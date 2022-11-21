#include <stdio.h>
#include <stdlib.h>
#include<omp.h>
#define NUM_THREADS 1

int main()
{
    FILE *image, *outputImage, *lecturas;
    const double startTime = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
    printf("Numero de THREADS: %d. \n", NUM_THREADS); 

    image = fopen("Haachama.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("tst.bmp","wb");    //Imagen transformada
    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    unsigned char* ptr;
    int avgB = 0, avgG = 0, avgR = 0;
    int ile = 0;

    unsigned char xx[54];
    int cuenta = 0;
    for(int i=0; i<54; i++) {
    xx[i] = fgetc(image);
    fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);

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
    //-------------------------blur
    #pragma omp parallel
    {
        #pragma omp for nowait

            for(int xx = ancho; xx >= 0; xx--){
                for(int yy = 0; yy < alto; yy++){
                    avgB = avgG = avgR = 0;
                    ile = 0;

                    for(int x = xx ;x >= 0 &&  x > xx-7 ; x--){
                        for(int y = yy; y < alto && y < yy + 7; y++){
                            avgB += ptr[(x) * alto + (y) ];
                            avgG += ptr[(x) * alto + (y) + 1];
                            avgR += ptr[(x) * alto + (y) + 2];
                            ile++;
                        }
                    }
                    avgB = avgB / ile;
                    avgG = avgG / ile;
                    avgR = avgR / ile;

                    fputc(ptr[(xx) * alto + (yy) ] = avgB, outputImage);
                    fputc(ptr[(xx) * alto + (yy) + 1] = avgG, outputImage);
                    fputc(ptr[(xx) * alto + (yy) + 2] = avgR, outputImage);

                }
            }
        free(ptr);
        fclose(image);
        fclose(outputImage);
    }

    /*for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fputc(ptr[(i) * ancho + (j) ], outputImage);
            fputc(ptr[(i) * ancho + (j)  + 1], outputImage);
            fputc(ptr[(i) * ancho + (j)  + 2], outputImage);
        }
    }*/

    /*for (int i = 0; i < (alto * ancho); ++i)
    {
        fputc(ptr[i], outputImage);
        fputc(ptr[i + 1], outputImage);
        fputc(ptr[i + 2], outputImage);
    }*/

    const double endTime = omp_get_wtime();
    printf("tomo (%lf) segundos\n", (endTime - startTime));
    
}
