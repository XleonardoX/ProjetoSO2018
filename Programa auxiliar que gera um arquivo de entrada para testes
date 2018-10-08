//gera 500 numeros aleatorios entre 0 e 1000 e salva num arquivo para teste

#include<stdio.h>
#include<stdlib.h>

#define fname "arq1.txt"

int main(){
     int x[500];
     int i;
     FILE *f;


     for(i=0; i<500; i++){
         x[i]= rand()%1001;
     } 
     
     f = fopen(fname, "w+");

     for(i=0; i<500; i++){
         fprintf(f,"%d\n",x[i]);
     } 

  fclose(f);
}
