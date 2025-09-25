#include <stdio.h>
#include <stdlib.h>


typedef struct lstItem{
   int dado;
   struct lstItem *next;
}filaItem;


typedef struct{
   filaItem *inicio;	
   filaItem *fim;
}fila;



fila *criaFila(){
   fila *f = malloc(sizeof(fila));
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
      printf("Fila vazia.\n");   
   }else{
      f->inicio = f->inicio->next;
      if(f->inicio==NULL) //se a fila ficou vazia
        f->fim = NULL;     
   }
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
   printf("\n\n");
}

int main(){
   
   fila *f = criaFila(); 
   int opcao = 1, i; 

   while(opcao!=9){
      printf("1 - Inserir\n");
      printf("2 - Remover\n");
      printf("3 - Consultar cabeça (peek)\n");
      printf("4 - Imprimir a fila\n");
      printf("9 - Sair\n");
      printf("\nDigite uma opcao: ");
      scanf("%d",&opcao);
      if(opcao==1){
         printf("Digite um número inteiro: ");
         scanf("%d",&i);
         push(f,i);
      }else
      if(opcao==2){
         pop(f);
         printf("Item removido com sucesso\n"); 
      }
      if(opcao==3){
         printf("%d\n", peek(f));
      }else
      if(opcao==4){
         print(f);
      }
   }
}

