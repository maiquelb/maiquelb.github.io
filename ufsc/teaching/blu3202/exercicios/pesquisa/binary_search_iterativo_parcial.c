#include <stdio.h>


/* 
   Executar pesquisa binária sobre um vetor. Retornar o índice do vetor em que o valor for encontrado. Retornar -1 caso o valor não seja encontrado no vetor.
   Parâmetros:
       - inicio: índice inicial do vetor a ser considerado na pesquisa
       - fim: índice final do vetor a ser considerado na pesquisa
       - *v: endereço do primeiro elemento do vetor
       - x : valor a pesquisar

*/
int binary_search(int inicio, int fim, int *v, int x){
   /* implementar */
}

int main(){
   int i, n, vetor[10] = {1,2,3,4,5,6,7,8,9,10};
   printf("Digite o numero para localizar: ");
   scanf("%d", &n);
   printf("Resultado da busca: %d\n", binary_search(0,9,vetor,n));
}
