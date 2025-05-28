/* Para executar em terminal, digitar gcc trabalho_cac3202_20242.c -o trabalho_cac3202_20242 -pthread */


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//Struct que representa uma coordenada (X,Y,Z)
typedef struct posicao{
   float x; //coordenada X (longitude)
   float y; //coordenada Y (latitude)
   float z; //coordenada Z (altitude)
}Posicao;


//Struct que representa o conjunto de informações a respeito de um drone
typedef struct droneInfo{
   char id[8]; //identificador do drone
   Posicao posicao; // coordenada Y
   float bateria; //nível da bateria
   struct tm *hora; //hora em que a informação foi gerada
}DroneInfo;




int thread_status = 1;
DroneInfo info; //variável global que armazena a última informação gerada


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


//função que retorna a última informação produzida
DroneInfo ultima_informacao(){
   return info;
}




//gera identficadores dos drones seguindo o padrão de prefixos de aeronaves brasileiras.
char *gerar_id() {
    static char ultimo_prefixo[8] = "";  // Guarda o último prefixo gerado
    static int inicializado = 0;

    if (!inicializado) {
        srand(time(NULL));  // Inicializa o gerador de números aleatórios apenas uma vez
        inicializado = 1;
    }

    // 50% de chance de repetir o último prefixo (se já existir)
    if (strlen(ultimo_prefixo) > 0 && rand() % 2 == 0) {
        return ultimo_prefixo;
    }

    // Geração de novo prefixo
    const char *prefixos_validos[] = {"PT", "PP", "PR", "PU"};
    int indice = rand() % 4;

    // Gera três letras aleatórias de A a Z
    char sufixo[4];
    for (int i = 0; i < 3; i++) {
        sufixo[i] = 'A' + (rand() % 26);
    }
    sufixo[3] = '\0';

    // Monta o prefixo completo (ex: PR-XYZ)
    sprintf(ultimo_prefixo, "%s-%s", prefixos_validos[indice], sufixo);

    return ultimo_prefixo;
}


// Função que simula a geração de valores de sensores
void* gerar_valores_de_sensores(void* arg) {
         
    while (thread_status==1) {
        char drone_id[8]; 
        strcpy(drone_id, gerar_id());
        float gps_x = rand() % 1000;  
        if(rand() % 100 < 50) gps_x = gps_x*-1; //converte para coordenada negativa
        float gps_y = rand() % 1000;  
        if(rand() % 100 < 50) gps_y = gps_y*-1; //converte para coordenada negativa
        float z = rand() % 200;
        float bateria = rand() % 100;
    
        // *** capturar a hora atual *** 
        time_t agora;
        time(&agora); //obter o tempo atual
        
        
        
        strcpy(info.id, drone_id);
        info.posicao.x = gps_x;
        info.posicao.y = gps_y;
        info.posicao.z = z;
        info.bateria = bateria;
        info.hora = localtime(&agora);  
        

        
        // Sinaliza a thread de leitura de sensores pode executar
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

        
        sleep(1);  // Aguarda um segundo até a próxima leitura de sensores
    }
    return NULL;
}



// Função que simula a leitura de valores dos drones
void* ler_valores_de_sensores(void* arg) {
    while (thread_status == 1) {
        // Espera até receber o sinal da thread de geração de valores
        pthread_mutex_lock(&mutex);

        // Verifica se o programa ainda deve continuar antes de esperar pelo sinal
        if (thread_status == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_cond_wait(&cond, &mutex);
        
        if (thread_status == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        
        //*** As duas linhas abaixo ilustram a leitura de sensores. Descomentar para testar 
        //DroneInfo droneInfo = ultima_informacao();
        //printf("Nova leitura: id:%s; posicao:(%f,%f,%f), bateria:%f, hora:%d:%d:%d\n",droneInfo.id, droneInfo.posicao.x, droneInfo.posicao.y, droneInfo.posicao.z, droneInfo.bateria, droneInfo.hora->tm_hour, droneInfo.hora->tm_min, droneInfo.hora->tm_sec   );
        
        /**** Implementar a leitura dos sensores aqui ****/
        
        
        /**** Finalizar a leitura dos sensores aqui  ****/
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


//**** Implementar todas as funções e estruturas de dados aqui ****/



//**** 	 ****/


int main() {
    pthread_t thread_gerar, thread_ler;
    int opcao=0;
    
    // Criação da thread que simula geração de valores de sensores
    if (pthread_create(&thread_gerar, NULL, gerar_valores_de_sensores, NULL) != 0) {
        perror("Erro ao criar thread");
        return 1;
    }
    
    // Criação da thread que lê de valores de sensores simulados
    if (pthread_create(&thread_ler, NULL, ler_valores_de_sensores, NULL) != 0) {
        perror("Erro ao criar thread");
        return 1;
    }


    // Função principal aguarda a opção do usuário
    while (opcao!=9) {
        printf("Selecione uma das opções abaixo: \n");
        printf("1. Imprimir a posição da última leitura\n");
        printf("2. Imprimir o nível da bateria da última leitura\n");
        printf("3. Imprimir a distância média para o obstáculo mais próximo nas primeiras 'x' leituras\n");
        printf("4. Imprimir a distância média para o obstáculo mais próximo nas últimas 'x' leituras\n");
        printf("5. Imprimir o horário da primeira visita a um ponto.\n");
        printf("6. Imprimir o a distância entre o último ponto ponto visitado e o ponto mais distante das coordenadas (0, 0)\n");
        printf("6. Imprimir o a distância entre o último ponto ponto visitado e o ponto mais próximo das coordenadas (0, 0)\n");
        printf("9. Encerrar o programa\n");
        

        printf("\nDigite uma opção: ");
        scanf("%d",&opcao);
        switch(opcao){
           case 1: 
              printf("Posição do drone %s: (%f,%f,%f)\n", info.id, info.posicao.x,info.posicao.y,info.posicao.z); 
              break;
           case 2: 
              printf("Bateria do drone %s: %f\n", info.id, info.bateria);
              break;
              
           /**** Implementar as opções 3 a 6 aqui ****/   
           
           /**** Fim da implementação das opções 3 a 6  ****/
           
           case 9: 
              pthread_mutex_lock(&mutex);
              thread_status = 0;
              pthread_cond_broadcast(&cond); // Sinalizar todas as threads
              pthread_mutex_unlock(&mutex);
              break;     
           default:
              printf("Opção inválida\n");
        }

        
        
        
        
    }

    // Espera as threads finaizarem
    pthread_join(thread_gerar, NULL);
    pthread_join(thread_ler, NULL);

    return 0;
}

