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



void *Multicat_integer_sort(void *z);
void Salva_Arq_Out(Multicat *w);

//===========================================================================================================================

int main(int argc, char *argv[]){ 
         Multicat * x;                           //apontador para a estrutura
         int i;                                  //variavel auxiliar para estruturas de laços
         int Num_de_threads;

         x = (Multicat *) malloc(sizeof(Multicat));
         x->argumentos = argc;
         
         if (argc < 4){                                                     //mínimo de 4 argumentos
            printf("Comando insuficiente para execução do programa\n");     //"./multicat 16 arq1.in arqSaida.out"
            return 0;                                                    
         }
         
         Num_de_threads = atoi(argv[1]);        //argumento 1 referente ao numero de threads
         pthread_t threads[Num_de_threads];     //vetor de threads
         
         for(i=0; i<((x->argumentos)-2); i++){
              strcpy(x->arquivo[i],argv[i+2]);
         }
         
         clock_t start_time;    //para medir o tempo de execução
         start_time = clock(); 

         for(i=0; i<(Num_de_threads); i++){                                                 
            pthread_create(&threads[i],NULL,Multicat_integer_sort,(void *)x);    //metade das threads para a função multicat
         }
         
         for (i=0;i<Num_de_threads;i++){
              pthread_join(threads[i],NULL); //A funcao bloqueia o processo ate que o thread indicado termine
         }
         
         double time_SEC = (clock() - start_time) / (double)CLOCKS_PER_SEC;  //tempo total de execução

         Salva_Arq_Out(x);
         printf("Tempo de execução usando %d threads: %f segundos.\n", Num_de_threads, time_SEC);
         
         free(x);
         pthread_exit(NULL);

    return 0;
}

//==========================================================================================================================

void *Multicat_integer_sort(void *z){  //le os arquivos e grava os inteiros num vetor desordenado
     
         FILE *f;
         int aux, i;
         int j=0;
         ((Multicat *)z)->top = 0;

         for(int i=0; i<(((Multicat *)z)->argumentos)-3; i++){        //desconsidera os comandos "./multicat" "Num threads" "arqSaida.out"
              f = fopen((((Multicat *)z)->arquivo[i]),"r");           //EOF representa o fim do arquivo de entrada
              while(fscanf(f,"%d\n",&aux)!=EOF){                      //para saber o tamanho do vetor que deve ser alocado           
                    ((Multicat *)z)->top++;                           //apos passar por todos arquivos de entrada
              }
              fclose(f);
         } 

         ((Multicat *)z)->v= (int*) malloc(((Multicat *)z)->top*sizeof(int));       //alocação do vetor resultante

         for(int i=0; i<(((Multicat *)z)->argumentos)-3; i++){        //desconsidera os comandos "./multicat" "Num threads" "arqSaida.out"
              f = fopen((((Multicat *)z)->arquivo[i]),"r");
              while(fscanf(f,"%d\n",&aux)!=EOF){                   
                   ((Multicat *)z)->v[j] = aux;
                   j++;
              }
            fclose(f);
         } 

         for(j=(((Multicat *)z)->top-1); j>0; j--){      //Ordenação Bublle Sort
              for(i=0; i<j; i++){
                 if(((Multicat *)z)->v[i] > ((Multicat *)z)->v[i+1]){
                    aux = ((Multicat *)z)->v[i];
                    ((Multicat *)z)->v[i] = ((Multicat *)z)->v[i+1];
                    ((Multicat *)z)->v[i+1] = aux;
                 }
              }
         }
         
}

//===============================================================================================================================

void Salva_Arq_Out(Multicat *w){   //função que salva os vetor ordenado num arquivo de saida

         FILE *f;
         f = fopen((w->arquivo[(w->argumentos)-3]), "w+");  //referente ao arquivo "arqSaida.out"
         for(int i=0; i<(w->top); i++){
            fprintf(f,"%d\n",(w->v[i]));  //grava no arquivo
         }
 
   fclose(f);
}

