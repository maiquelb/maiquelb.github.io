#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 1024
#define MAX_CAMPOS 10
#define DELIMITER ";"
#define RADIUS_EARTH 6371000 // Raio médio da Terra em quilômetros

int num_linhas = 0; // variável global que determina a quantidade de registros a serem tratadoss	

typedef struct ubs{
   char cnes[7];
   int uf;
   int ibge;
   char nome[50];
   char logradouro[80];
   char bairro[30];
   float latitude;
   float longitude;
} Ubs;



/*
  Exercício 2: Fazer as seguintes mudanças na função processa_ubs:
                - A função deve retornar um ponteiro para um vetor de Ubs cujo tamanho corresponda à variável global num_linhas
                - A função deve receber apenas o parâmetro filename

*/
/*
   Processa o arquivo .csv passado no parâmetro "filename".
   Para cada linha do arquivo, cria-se um novo dado do tipo "Ubs" (defnido pela struct apropriada).
   O dado criado é adicionado ao vetor "ubs" passado como parâmetro.   
*/
Ubs *processa_csv(char *filename) {

    //criar um vetor de UBS com a quantidade de posições adequada
    Ubs *ubs = malloc(sizeof(Ubs)*num_linhas);

    int linha = 0; //contador para contar quantas linhas foram processadas

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    char *campos[MAX_CAMPOS];
    
    char nomes_campos[8][1024] = {"CNES","UF","IBGE","NOME","LOGRADOURO","BAIRRO", "LATITUDE","LONGITUDE"};
    int indice = 0;

    fgets(line, sizeof(line), file); //ler e desprezar a primeira linha	

    //para cada linha, produz-se um vetor de strings de 8 posições. Cada posição armazena um campo, conforme definido na variável "nomes_campos"	
    while (fgets(line, sizeof(line), file)&& ++linha<=num_linhas) {    
        int num_campos = 0;
        char *token = strtok(line, DELIMITER);
        while (token != NULL && num_campos < MAX_CAMPOS) {
            if (token[0] == '"') {
                memmove(token, token + 1, strlen(token)); // Remove leading quote
                token[strlen(token) - 1] = '\0'; // Remove trailing quote
            }
            campos[num_campos++] = token;
            token = strtok(NULL, DELIMITER);
        }

        
        /*  
        // Impressão dos campos
        for (int i = 0; i < num_campos; i++) {
            printf("%s(%d): %s ", nomes_campos[i] , i, campos[i]);
        }
        */

        strcpy(ubs[indice].cnes,campos[0]);
        ubs[indice].uf = atoi(campos[1]);
        ubs[indice].ibge = atoi(campos[2]);
        strcpy(ubs[indice].nome,campos[3]);
        strcpy(ubs[indice].logradouro,campos[4]);
        strcpy(ubs[indice].bairro,campos[5]);
        ubs[indice].latitude = atof(campos[6]);
        ubs[indice].longitude = atof(campos[7]);
        
        printf("** longigude %d - %f\n, ", indice, ubs[indice].longitude);
        
        indice++;
        
        
    }

    fclose(file);
    return ubs;
}



// Função para converter graus em radianos
double grausParaRadianos(double degree) {
    return degree * (M_PI / 180);
}

// Função para calcular a distância entre dois pontos em coordenadas (latitude, longitude)
double calcular_distancia(double lat1, double lon1, double lat2, double lon2) {
    double dLat = grausParaRadianos(lat2 - lat1);
    double dLon = grausParaRadianos(lon2 - lon1);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(grausParaRadianos(lat1)) * cos(grausParaRadianos(lat2)) *
               sin(dLon / 2) * sin(dLon / 2);
    
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    double distance = RADIUS_EARTH * c;
    return distance;
}

/*
   Imprime a lista de todas as UBSs contidas no vetor "ubs" passado como parâmetro
*/
void lista_ubs(Ubs *ubs){
   int i = 0;
   for(i=0;i<num_linhas;i++)
      printf("%d: %s - %s, %f, %f\n",i,(*(ubs+i)).cnes, (*(ubs+i)).nome, (*(ubs+i)).latitude, (*(ubs+i)).longitude);
}


/* 
   Retorna a linha que contém o CNES passado como parâmetro. 
   Retorna -1 caso não encontre o CNES.
*/
int procura_ubs(Ubs *ubs, char *cnes){
   int i, comparacoes = 0;
   for(i=0;i<num_linhas;i++){
      comparacoes++;
      if(strcmp((ubs+i)	->cnes,cnes)==0){
         printf("Comparacoes: %d\n", comparacoes);
         return i;
      }
   }
   printf("Comparacoes: %d\n", comparacoes);
   return -1;
}




/*
  Localiza as duas UBS mais próxima entre si (descartando aquelas que estão na mesma latitude-longitude).
*/
Ubs *ubs_mais_proximas(Ubs *ubs, double *dist){
   Ubs *u = malloc(sizeof(Ubs)*2);
   double menor_distancia = 999999999; //a variável "menor_distância" armazena a menor distância já calculada
   double distancia;
   int i, j, ubs1=-1, ubs2=-1; //as variáveis ubs1 e ubs2 armazenam as linhas que correspondem às UBSs mais próximas entre si
   for(i=0;i<num_linhas-1;i++){ //para cada UBS a partir da primeira
      for(j=i+1;j<num_linhas;j++){ //compara a i-ésima UBS com todas as próximas         
         printf("------------ 22 - %d,%d, %s, %f, %f, %f, %f \n", i, j,(ubs+i)->nome, ubs[i].latitude,(ubs+i)->longitude,(ubs+j)->latitude,(ubs+j)->longitude);
         distancia = calcular_distancia((ubs+i)->latitude,(ubs+i)->longitude,(ubs+j)->latitude,(ubs+j)->longitude); //calcula a distância entre as UBSs
         comparacoes++;
         if(distancia<menor_distancia && distancia>0){ //se encontrou uma distância menor do que a já computada             
             menor_distancia = distancia;
             ubs1 = i;
             ubs2 = j;
         }
      }
   }      
   
   u[0] = ubs[ubs1]; 
   u[1] = ubs[ubs2];    
   *dist = menor_distancia;
   return u;            
}


int main() {
   printf("dist: %f\n", calcular_distancia(-8,-35,-8,-30));
    printf("Informe a quantidade de registros a processar: ");
    scanf("%d",&num_linhas); //definir quantos registros serão processados

    char *filename = "Unidades_Basicas_Saude-UBS_10000.csv";    
    
    // Exercício 1: comparar a linha comentada abaixo (versão antiga) com a linha posterior, que é a nova vesão. O que muda?
    //Ubs ubs[num_linhas]; //vetor para quardar cada uma das UBSs            
    Ubs *ubs = processa_csv(filename); //carregar os dados das UBSs no arquivo .csv para dentro de um vetor
    
    
    
    int opcao = 0;
    while(opcao!=9){
       printf("Opções:\n");
       printf("1 - Listar todas as UBS\n");
       printf("2 - Procurar uma UBS pelo CNES\n");
       printf("3 - Procurar UBSs mais próximas CNES\n");
       printf("9 - Encerrar o programa\n\n");
       printf("Digite a opção desejada: ");
       scanf("%d",&opcao);
    
       if(opcao==1)
          lista_ubs(ubs);
       else
       if(opcao==2){
          printf("Digite o CNES a localizar: ");
          char cnes[8], c;
          while ((c = getchar()) != '\n' && c != EOF); //limpeza do buffer do teclado
          fgets(cnes,8, stdin); //ler a entrada do teclado e salvá-la na variável "cnes"
          printf("Valor encontrado na linha %d\n", procura_ubs(ubs,cnes));
       }
       else
       if(opcao==3){
          // Exercício 4: Adaptar a chamada à função ubs_mais_próxima para as mudanças feitas na função original, caso necessário. 
          //                Além disso, imprimir o nome das duas UBSs mais próximas entre si, bem como a distância entre elas.
          double d;   
          Ubs *proximas = ubs_mais_proximas(ubs, &d);
          printf("UBSs mais próximas: (%s-%s),(%s-%s), %f\n", proximas[0].cnes, proximas[0].nome, proximas[1].cnes, proximas[1].nome, d);
       }
    }
    
    return 0;
}