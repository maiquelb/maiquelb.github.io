#include <stdio.h>


int binary_search(int inicio, int fim, int *v, int x){
   /* implementar */
}

int main(){
   int i, n, vetor[10] = {1,2,3,4,5,6,7,8,9,10};
   printf("Digite o numero para localizar: ");
   scanf("%d", &n);
   printf("Resultado da busca: %d\n", binary_search(0,9,vetor,n));
}