/* Para compilar em terminal, digitar gcc trabalho.c -o trabalho -pthread */


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


// Struct que representa uma leitura de sensor em um equipamento industrial
typedef struct leitura {
    int id_equipamento;
    float vibracao;
    struct tm *instante;
} Leitura;


// Struct que representa um evento de manuten��o
typedef struct manutencao {
    int id_equipamento;
    struct tm *instante;
    int codigo_tipo;
} Manutencao;


int thread_status = 1;
Leitura l; //vari�vel global que armazena a �ltima visita realizada
Manutencao m;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


//fun��o que retorna os dados da �ltima leitura de sensores
Leitura ultima_leitura(){
   return l;
}



//fun��o que retorna os dados da �ltima manutencao
Manutencao ultima_manutencao(){
   return m;
}


// Gerar uma leitura de sensores
Leitura gerar_leitura() {
    Leitura leitura;    
    
    //*** gerar valores aleat�rios para id_equipamento e vibracao
    srand(time(NULL));
    int id_equipamento = rand() % 100;    // Inteiro entre 0 e 99
    float vibracao = (float)rand() / (float)(RAND_MAX) * 100.0;  // Float entre 0.0 e 100.0
        
    // *** capturar a hora atual *** 
    time_t agora;
    time(&agora); //obter o tempo atual
                
    leitura.id_equipamento = id_equipamento;
    leitura.vibracao = vibracao;
    leitura.instante = localtime(&agora);  
    return leitura;
}


// Fun��o que simula a gera��o de valores de sensores
void* gerar_leitura_de_sensores(void* arg) {
         
    while (thread_status==1) {                
        l = gerar_leitura();

        // Sinaliza a thread de leitura de sensores pode executar
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

        
        sleep(1);  // Aguarda um segundo at� a pr�xima leitura de sensores
    }
    return NULL;
}



// Gerar um evento de manutencao
Manutencao gerar_manutencao() {
    Manutencao manutencao;
    
    // Gerar valores aleatórios para id_equipamento e codigo_tipo
    manutencao.id_equipamento = rand() % 100; // Inteiro entre 0 e 99
    manutencao.codigo_tipo = rand() % 100;   // Inteiro entre 0 e 99
    
    // Capturar a hora atual
    time_t agora;
    time(&agora);
    manutencao.instante = localtime(&agora);
    
    return manutencao;
}

// Fun��o que simula a gera��o eventos de manutencao
void* gerar_evento_manutencao(void* arg) {
         
     while (thread_status==1) {
        m = gerar_manutencao();
        
        // Sinaliza a thread de leitura de sensores pode executar
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

        
        sleep(1);  // Aguarda um tempo aleat�rio entre 15 e 30 segundos at� a pr�xima gera��o de evento de manutencao
    }
    return NULL;
}


// Fun��o que simula a leitura de valores de sensores
void* ler_valores_de_sensores(void* arg) {
    while (thread_status == 1) {
        // Espera at� receber o sinal da thread de gera��o de valores
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
        
        // //*** As tres linhas abaixo ilustram a leitura de sensores. Descomentar para testar 
        // Leitura leitura = ultima_leitura();        
        // printf("[Ultima leitura] equipamento: %d; vibracao: %f - %02d:%02d:%02d\n",
        //     leitura.id_equipamento, leitura.vibracao, leitura.instante->tm_hour, leitura.instante->tm_min, leitura.instante->tm_sec);

        //*** As tres linhas abaixo a leitura do ultimo evento de manutencao. Descomentar para testar 
        // Manutencao manutencao = ultima_manutencao();
        // printf("[Ultima manutencao] equipamento: %d; tipo: %d - %02d:%02d:%02d\n",
        //      manutencao.id_equipamento, manutencao.codigo_tipo, manutencao.instante->tm_hour, manutencao.instante->tm_min, manutencao.instante->tm_sec);
        
        /**** Implementar a leitura dos sensores aqui ****/
        
        
        /**** Finalizar a leitura dos sensores aqui  ****/
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


//**** Implementar todas as fun��es e estruturas de dados aqui ****/



//**** 	 ****/


int main() {
    pthread_t thread_gerar, thread_ler;
    Leitura leitura; 
    Manutencao manutencao;
    int opcao=0;
    
    // Cricao da thread que simula geracao de valores de sensores
    if (pthread_create(&thread_gerar, NULL, gerar_leitura_de_sensores, NULL) != 0) {
        perror("Erro ao criar thread");
        return 1;
    }

    m = gerar_manutencao(); //gerar o evento de manutencao inicial para que a thread de leitura de sensores tenha algo para ler
    // Criacao da thread que simula geracao de valores de sensores
    if (pthread_create(&thread_gerar, NULL, gerar_evento_manutencao, NULL) != 0) {
        perror("Erro ao criar thread");
        return 1;
    }
    
    
    // Cria��o da thread que l� de valores de sensores simulados
    if (pthread_create(&thread_ler, NULL, ler_valores_de_sensores, NULL) != 0) {
        perror("Erro ao criar thread");
        return 1;
    }

    // Fun��o principal aguarda a tecla ENTER para imprimir o contador
    while (opcao!=9) {
        printf("Selecione uma das op��es abaixo: \n");
        printf("1. Imprimir a ultima leitura de sensores\n");
        printf("2. Imprimir a ultima manutencao\n");
        printf("3. Imprimir a dist�ncia m�dia para o obst�culo mais pr�ximo nas primeiras 'x' leituras\n");
        printf("4. Imprimir a dist�ncia m�dia para o obst�culo mais pr�ximo nas �ltimas 'x' leituras\n");
        printf("5. Imprimir o hor�rio da primeira visita a um ponto.\n");
        printf("6. Imprimir o hor�rio da ultima visita a um ponto.\n");
        printf("7. Imprimir a coordenada visitada mais pr�xima de um ponto\n");
        printf("8. Imprimir a coordenada visitada a uma certa dist�ncia da origem\n");
        printf("9. Encerrar o programa\n");
        

        printf("\nDigite uma op��o: ");
        scanf("%d",&opcao);
        switch(opcao){
           case 1: 
              leitura = ultima_leitura();        
              printf("[Ultima leitura] equipamento: %d; vibracao: %f - %02d:%02d:%02d\n",
                    leitura.id_equipamento, leitura.vibracao, leitura.instante->tm_hour, leitura.instante->tm_min, leitura.instante->tm_sec);
              break;
           case 2: 
              manutencao = ultima_manutencao();         
            printf("[Ultima manutencao] equipamento: %d; tipo: %d - %02d:%02d:%02d\n",
              manutencao.id_equipamento, manutencao.codigo_tipo, manutencao.instante->tm_hour, manutencao.instante->tm_min, manutencao.instante->tm_sec);
              break;
           /**** Implementar as op��es 3 a 7 aqui ****/   
           
           /**** Fim da implementa��o das op��es 3 a 7  ****/
           case 9: 
              pthread_mutex_lock(&mutex);
              thread_status = 0;
              pthread_cond_broadcast(&cond); // Sinalizar todas as threads
              pthread_mutex_unlock(&mutex);
              break;     
           default:
              printf("Op��o inv�lida\n");
        }

        
        
        
        
    }

    // Espera as threads finaizarem
    pthread_join(thread_gerar, NULL);
    pthread_join(thread_ler, NULL);

    return 0;
}

