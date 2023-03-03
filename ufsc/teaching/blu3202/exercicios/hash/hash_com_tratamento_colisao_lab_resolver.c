#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct aluno{  
   int matricula;
   char nome[30];
   float n1, n2, n3;
} typedef Aluno;


struct lstItem{
   Aluno dado;
   struct lstItem *next;
}typedef listaItem;


struct hash {
   int qtd, TABLE_SIZE;
   listaItem **itens; //os itens são um vetor de ponteiros
} typedef Hash;


/******************** Funções para lista encadeada ****************/

/* Criação da lista: retorna uma lista vazia */
listaItem *cria_lista(){
   return NULL;
}



/* 
   Insere um novo elemento no inicio na lista.
   Retorna um ponteiro para a cabeça da lista.
*/
listaItem* insere_no_inicio(listaItem *lista, Aluno dado){ 
   listaItem* novo = malloc(sizeof(listaItem));
   (*novo).dado = dado;
   (*novo).next = lista;
   lista = novo;   
}

/* 
   Insere um novo elemento no final na lista.
   Retorna um ponteiro para a cabeça da lista.

*/
listaItem* insere_no_fim(listaItem *lista, Aluno dado){
  
   listaItem* novo = malloc(sizeof(listaItem));
   (*novo).dado = dado;
  
   if(lista==NULL){
      lista = novo;
   } 
   else{
       listaItem *ultimo = lista;
       while(ultimo->next!=NULL){
        ultimo = ultimo->next;        
       }
       ultimo->next = novo;
   }

   return lista;     
}




//*************************************************************************

Hash *criaHash(int TABLE_SIZE){
   Hash *h = malloc(sizeof(Hash));
   int i;
   listaItem *p;
   h->TABLE_SIZE = TABLE_SIZE;
   h->itens = malloc(TABLE_SIZE*sizeof(p));
   h->qtd = 0;
   for (i=0;i<h->TABLE_SIZE;i++){  
      h->itens[i]= cria_lista();      
   }
   //enderecos(h);
   return h;
}


int gera_hash(char* s, int TABLE_SIZE){
   int i, hash = 0;
   int len_s = strlen(s);
   for (int i=0;i<len_s;i++){
      hash  = hash + s[i];        
    }
    return hash%TABLE_SIZE;
}


void liberaHash(Hash *h){
   if(h!=NULL){
      int i;
      for(i=0;i<h->TABLE_SIZE;i++){
         if(h->itens[i]!=NULL)
            free(h->itens[i]);
      }
      free(h->itens);
      free(h);
   }
}

void insere(Hash *h, Aluno *a){
   if(h==NULL){
   }
   else{
       /* Implementar a insercao. Se a posicao estiver ocupada, exibir uma mensagem e não inserir. Do contrário, fazer a inserção e exibir uma mensagem informando a posicao em que o elemento foi inserido.
      */
   }
   

}

void excluir(Hash *h, char* nome){
    /* Implementar a insercao. Se a posicao estiver ocupada, exibir uma mensagem e não inserir. Do contrário, fazer a inserção e exibir uma mensagem informando a posicao em que o elemento foi inserido.
      */
}


Aluno *busca(Hash *h, char *nome){
   
}



Aluno *cria_aluno(){
   Aluno *a = malloc(sizeof(Aluno));
   printf("Nome: ");
   scanf("%s",a->nome);
   printf("Nota 1: ");
   scanf("%f", &(a->n1));
   printf("Nota 2: ");
   scanf("%f", &(a->n2));
   printf("Nota 3: ");
   scanf("%f", &(a->n3));
   return a;
}

void print_aluno(Aluno a){
   printf("%s: %f, %f, %f", a.nome, a.n1, a.n2, a.n3);
}

void print_table(Hash *h){
   int i=0;
   for(i=0;i<h->TABLE_SIZE;i++){
      printf("\n%d: ", i);
      listaItem* item = h->itens[i];
      while(item!=NULL){
         print_aluno(item->dado);
         item = item->next;
      }
   }
}

int main(){

   int tamanho = 0;
   printf("Informe o tamanho da tabela: ");
   scanf("%d",&tamanho);
   
   Hash *h = criaHash(tamanho);

   
   int opcao = 1;
   while(opcao!=9){   
      printf("Selecione uma opção\n");
      printf("1 - Inserir\n");
      printf("2 - Buscar\n");
      printf("3 - Excluir\n");
      printf("4 - Imprimir\n");
      printf("9 - Sair\n");
      scanf("%d",&opcao);

     if(opcao==1){
        Aluno *a = cria_aluno();
        insere(h, a);        
     }else
     if(opcao==2){
        char nome[30];
        printf("Digite o nome do aluno: ");
        scanf("%s",nome);
        Aluno *a = busca(h,nome);
        if(a!=NULL){
           printf("Dado localizado: ");
           print_aluno(*a);
           printf("\n");
        }else
           printf("Dados não localizados\n");
     }else
     if(opcao==3){
        char nome[30];
        printf("Digite o nome do aluno: ");
        scanf("%s",nome);
        excluir(h,nome);
      
     }else
     if(opcao==4){
        print_table(h);     
     }    
   }

   liberaHash(h);
}
