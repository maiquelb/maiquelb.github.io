#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


//Struct que representa uma coordenada (X,Y)
typedef struct ponto{
   int x; //coordenada X
   int y; // coordenada Y
}Ponto;


//Struct que representa uma visita a um determinado ponto em uma determinada hora
typedef struct visita{
   Ponto coordenada;
   struct tm *hora; //hora em que a visita aconteceu   
}Visita;


int thread_status = 1;
Visita v; //variável global que armazena a última visita realizada
float distancia; //variável global que armazena a distância para o obstáculo mais próximo


// Função que simula a leitura de sensores
void* simular_leitura_de_sensores(void* arg) {
         
    while (thread_status==1) {
        //*** gerar valores aleatórios para distância do obstáculo e coordenadas X,Y:
        srand(time(NULL));
        int x = rand() % 100;    // Inteiro entre 0 e 99
        int y = rand() % 100;    // Inteiro entre 0 e 99
        distancia = (float)rand() / (float)(RAND_MAX) * 100.0;  // Float entre 0.0 e 100.0

        
        // *** capturar a hora atual *** 
        time_t agora;
        time(&agora); //obter o tempo atual
        
        
        
        v.coordenada.x = x;
        v.coordenada.y = y;
        v.hora = localtime(&agora);  
        
        sleep(1);  // Aguarda um segundo até a próxima leitura de sensores
    }
    return NULL;
}



//função que retorna os dados da última visita
Visita ultima_visita(){
   return v;
}


//função que retorna a distância atual para o obstáculo mais próximo
float distancia_obstaculo(){
   return distancia;
}

int main() {
    pthread_t thread_id;
    Visita visita; 
    int opcao=0;
    
    // Criação da thread que irá incrementar o contador
    if (pthread_create(&thread_id, NULL, simular_leitura_de_sensores, NULL) != 0) {
        perror("Erro ao criar thread");
        return 1;
    }

    // Função principal aguarda a tecla ENTER para imprimir o contador
    while (opcao!=9) {
        printf("Selecione uma das opções abaixo: \n");
        printf("1. Imprimir distância para o obstáculo mais próximo\n");
        printf("2. Imprimir os dados do último ponto visitado\n");
        printf("3. Imprimir a distância média para o obstáculo mais próximo nas primeiras 'x' leituras\n");
        printf("4. Imprimir a distância média para o obstáculo mais próximo nas últimas 'x' leituras\n");
        printf("9. Encerrar o programa\n");
        

        printf("\nDigite uma opção: ");
        scanf("%d",&opcao);
        switch(opcao){
           case 1: 
              printf("%f\n", distancia_obstaculo()); 
              break;
           case 2: 
              visita = ultima_visita();
              printf("(%d,%d) - %02d:%02d:%02d\n",visita.coordenada.x, visita.coordenada.y, visita.hora->tm_hour, visita.hora->tm_min, visita.hora->tm_sec);
              break;
           case 9: 
              thread_status=0; 
              break;     
           default:
              printf("Opção inválida\n");
        }

        
        
    
        //printf("Pressione ENTER para ver o valor do contador...\n");
        //getchar();  // Aguarda o usuário pressionar ENTER
        //printf("%f -(%d,%d) - %02d:%02d:%02d",distancia, v.coordenada.x, v.coordenada.y, v.hora->tm_hour, v.hora->tm_min, v.hora->tm_sec);
        
        /*printf("Valor do contador: %d\n", contador);
        // Exiba a hora atual
    printf("Hora atual: %02d:%02d:%02d\n",
           info_tempo->tm_hour,
           info_tempo->tm_min,
           info_tempo->tm_sec);

        */
        //printf("1. Distância até o obstáculo.\n");
        
        
    }

    // Espera a thread
    pthread_join(thread_id, NULL);

    return 0;
}

