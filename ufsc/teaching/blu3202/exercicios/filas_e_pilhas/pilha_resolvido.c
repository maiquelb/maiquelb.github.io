#include <stdio.h>
#include <stdlib.h>


typedef struct lstItem{
   int dado;
   struct lstItem *next;
}pilhaItem;


typedef struct{
   pilhaItem *top;	
}pilha;



pilha *criaPilha(){
   pilha *p = malloc(sizeof(pilha));
   p->top = NULL;
   return p;
}

void push(pilha *p, int dado){
   pilhaItem *novo = malloc(sizeof(pilhaItem));
   novo->dado = dado;
   novo->next = p->top; 
   p->top = novo;
}


void pop(pilha *p){
   pilhaItem *item = p->top;
   if(item!=NULL)
      p->top = p->top->next;
}



int peek(pilha *p){
   if(p->top!=NULL)
      return p->top->dado;
   else
      return -1;
}

void print(pilha *p){
   pilhaItem *item = p->top;
   while(item!=NULL){
      printf("%d --- ",item->dado);
      item = item->next;
   }
   printf("\n\n");
}



int main(){
   
   pilha *p = criaPilha(); 
   int opcao = 1, i; 

   while(opcao!=5){
      printf("1 - Empilhar\n");
      printf("2 - Desmpilhar\n");
      printf("3 - Consultar cabeça (peek)\n");
      printf("4 - Imprimir a pilha\n");
      printf("5 - Sair\n");
      printf("\nDigite uma opcao: ");
      scanf("%d",&opcao);
      if(opcao==1){
         printf("Digite um número inteiro: ");
         scanf("%d",&i);
         push(p,i) ;
      }else
      if(opcao==2){
         pop(p);
         printf("Item removido com sucesso");
      }else
      if(opcao==3)  {
         printf("%d\n",peek(p));
      }else
      if(opcao==4)  {
         print(p);
      }
   }
}

