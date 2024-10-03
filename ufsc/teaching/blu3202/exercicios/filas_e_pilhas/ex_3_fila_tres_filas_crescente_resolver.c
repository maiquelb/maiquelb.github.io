/*
   Implemente uma função que receba três filas, duas já preenchidas em ordem crescente e preencha a última com os valores das duas primeiras em ordem crescente.
*/

#include <stdio.h>
#include <stdlib.h>


/* ************** Início da implementação da fila ******************** */

typedef struct lstItem {
   int dado;
   struct lstItem *next;
}filaItem;


typedef struct{
   filaItem *inicio;	
   filaItem *fim;
}fila;



fila *criaFila(){
   fila *f = malloc(sizeof(fila	));
   f->inicio = f->fim = NULL;
   return f;
}

void push(fila *f, int dado){
   filaItem *novo = malloc(sizeof(filaItem));   
   novo->dado = dado;
   novo->next = NULL;
   if(f->fim!=NULL) //verifica se a fila está vazia
      f->fim->next = novo;
   else
      f->inicio = novo;
   f->fim = novo; 
}


void pop(fila *f){
   if(f->inicio==NULL){
      prin'tf("Fila vazia.\n");   
   }
   int dado = f->inicio->dado;
   f->inicio = f->inicio->next;
   if(f->inicio==NULL) //se a fila ficou vazia
     f->fim = NULL;     
}

int peek(fila *f){
   if(f->inicio!=NULL)
      return f->inicio->dado;
   return -1;
}


void print(fila *f){
   filaItem *item = f->inicio;
   while(item!=NULL){
      printf("%d --- ",item->dado);
      item = item->next;
   }
   printf("\n");
}


/* ************** Fim da implementação da fila ******************** */

void *mescla_filas(fila *f1, fila *f2, fila *f3){
 //implementar a solução do exercício aqui
}

int main(){
   
   fila *f1 = criaFila();
   fila *f2 = criaFila();
   fila *f3 = criaFila();          
   int i;

   /* ***** Preenchimento das filas ******************
   /* preenche f1 com valores multiplos de 3 */
   for(i=1;i<=5;i++){
      push(f1,i*3);
   } 
   /* preenche f1 com valores multiplos de 5 */
   for(i=1;i<=5;i++){
      push(f2,i*5);
   }



   printf("Filas originais antes da inclusão na nova fila:\n");
   printf("Fila 1: "); print(f1);
   printf("Fila 2: "); print(f2);
   
   mescla_filas(f1,f2,f3); 
   
   

   printf("\n\nFilas depois da inclusão na nova fila:\n");
   printf("Fila 1: "); print(f1);
   printf("Fila 2: "); print(f2);
   printf("Fila 3: "); print(f3);



}

