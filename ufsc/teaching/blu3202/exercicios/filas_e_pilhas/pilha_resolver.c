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


/* Inserir um novo elemento na pilha */
void *push(pilha *p, int dado){
   pilhaItem *novo = malloc(sizeof(pilhaItem));
   novo->dado = dado;
   /*implementar abaixo o restante da função*/
}


/* Remover um elemento da pilha */
void *pop(pilha *p){
   
}


/* Retornar o dado que se encontra na cabeça da pilha */
int peek(pilha *p){

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
      printf("2 - Desempilhar\n");
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

