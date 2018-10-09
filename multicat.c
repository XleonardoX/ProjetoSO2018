//Projeto Sistemas Operacionais

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>   // Cabeçalho especifico para threads POSIX



typedef struct Multicat_integer{
        int *v;
        int top;                  //referente ao tamanho do vetor v
        int argumentos;
        char arquivo[100][20];  //variavel que guarda o nomes de arquivos de entrada e saída
}Multicat;



void *Multicat_integer(Multicat * z);
void Ordena(Multicat * p, int ini, int fim);
void Salva_Arq_Out(Multicat * w);

//===========================================================================================================================

int main(int argc, char *argv[]){ 
         Multicat * x;                           //apontador para a estrutura
         int i;                                  //variavel auxiliar para estruturas de laços
         int Num_de_threads;
         x = (Multicat *) malloc(sizeof(Multicat));
         x->argumentos = argc;
         if (argc < 4){                                                  //mínimo de 4 argumentos
            printf("Comando insuficiente para execução do programa\n");  //"./multicat 16 arq1.in arqSaida.out"
            return 0;                                                    
         }
    
         clock_t start_time;    //para medir o tempo de execução
         start_time = clock();   

         Num_de_threads = atoi(argv[1]);        //argumento 1 referente ao numero de threads
         pthread_t threads[Num_de_threads];     //vetor de threads
         
         for(i=0; i<((x->argumentos)-2); i++){
              strcpy(x->arquivo[i],argv[i+2]);
         }
         //for(i=0; i<Num_de_threads; i++){
         //   pthread_create(&threads[i],NULL,Multicat_integer,NULL);    
         //}
         //for (i=0;i<Num_de_threads;i++){
         //     pthread_join(threads[i],NULL); //A funcao bloqueia o processo ate que o thread indicado termine
         //}
         Multicat_integer(x); 
         double time_SEC = (clock() - start_time) / (double)CLOCKS_PER_SEC;  //tempo total de execução

         printf("Tempo de execução = %f segundos.\n",time_SEC);
         pthread_exit(NULL);
    
    return 0;
}

//==========================================================================================================================

void *Multicat_integer(Multicat *z){  //le os arquivos e grava os inteiros num vetor desordenado
    
         FILE *f;
         int aux;
         int j=0;
         z->top=0;       //inicia top para acompanhar o tamanho do vetor
    
         for(int i=0; i<(z->argumentos)-3; i++){        //desconsidera os comandos "./multicat" "Num threads" "arqSaida.out"
              f = fopen((z->arquivo[i]),"r");           //EOF representa o fim do arquivo de entrada
              while(fscanf(f,"%d\n",&aux)!=EOF){        //para saber o tamanho do vetor que deve ser alocado           
                    z->top++;                           //apos passar por todos arquivos de entrada
              }
           fclose(f);
         } 

         z->v= (int*) malloc(z->top*sizeof(int));       //alocação do vetor resultante

         for(int i=0; i<(z->argumentos)-3; i++){        //desconsidera os comandos "./multicat" "Num threads" "arqSaida.out"
              f = fopen((z->arquivo[i]),"r");
              while(fscanf(f,"%d\n",&aux)!=EOF){                   
                   z->v[j] = aux;
                   j++;
              }
           fclose(f);
         } 

    Ordena(z ,0, (z->top));

}

//================================================================================================================================

void Ordena(Multicat * p, int ini, int fim){   //função para ordenação

         int j, i, aux;  

         for(j=(fim-1); j>0; j--){      
              for(i=ini; i<j; i++){
                 if(p->v[i] > p->v[i+1]){
                    aux = p->v[i];
                    p->v[i] = p->v[i+1];
                    p->v[i+1] = aux;
                 }
              }
         }

         for(i=0; i<fim; i++){
             printf("%d\n", p->v[i]);
         }  
      
  Salva_Arq_Out(p);

}

//===============================================================================================================================

void Salva_Arq_Out(Multicat * w){   //função que salva os vetor ordenado num arquivo de saida

         FILE *f;
         f = fopen((w->arquivo[(w->argumentos)-3]), "w+");  //referente ao arquivo "arqSaida.out"
         for(int i=0; i<(w->top); i++){
            fprintf(f,"%d\n",w->v[i]);  //grava no arquivo
         }
 
   fclose(f);
}

