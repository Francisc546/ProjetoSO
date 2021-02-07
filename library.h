#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <semaphore.h>
#define UNIXSTR_PATH "/tmp/so20212044718"
#define UNIXDG_PATH "/tmp/s.unixdfddffdfdgx"
#define UNIXDG_TMP "/tmp/dgXXXXXfdjhfdjhfdXX"


//Definir secções da discoteca

#define CENTRO 1
#define SALAESPERA 2
#define ESPERACIDADE 12
#define FILARUA 7
#define FILARUACIDADE 11
#define SALATESTE 4
#define SALATESTECIDADE 4
#define INTERNAMENTO 5
#define INTERNAMENTOCIDADE 10
#define TESTEPOSITIVO 6
#define TESTENEGATIVO 3
#define FILADRIVE 8
#define TESTEDRIVE 9
#define ISOLAMENTOVILA 13
#define ISOLAMENTOCIDADE 14

//Definir comandos que as tarefas podem executar
#define ENTROU 1
#define SAIU 2
#define ESPERA 3
#define CHEGOU 4
#define TEVE 5
#define DESISTIU 6

//Definir tipos de tarefas
#define MORADOR 1
#define VISITANTE 2
#define DRIVE 3
#define NORMAL 4 

//Socket que irá ser responsável pela comunicalão
int sockfd;

//Trincos	
pthread_mutex_t SocketMensagem, prot_dados;
//Vila
sem_t sem_filaRua_vila, sem_internamento_vila, sem_sala_espera_vila, sem_isolamento_vila,sem_ponto_visitante,sem_ponto_morador;
int total_rua_vila;
int total_sala_espera_vila;
int total_internamento_vila;
int total_isolamento_vila;
int total_tempo_vila;
int total_testes_vila;
int total_positivos_vila;
int total_negativos_vila;

//Cidade
sem_t sem_filaRua_cidade, sem_internamento_cidade, sem_sala_espera_cidade, sem_isolamento_cidade, sem_ponto_convencional,sem_ponto_driveThru, sem_fila_espera_driveThru;
int total_fila_espera_drive;
int total_internamento_cidade;
int total_isolamento_cidade;
int total_rua_cidade;
int total_sala_espera_cidade;
int total_tempo_cidade;
int total_testes_cidade;
int total_positivos_cidade;
int total_negativos_cidade;

//Global
int total_tempo;
int total_testes;
int total_positivos;
int total_negativos;







struct mensagemMonitor{
	char* indicaEstado;		//Mensagem que precede a indicacao do estado da simulacao
	char* simTerminada;		//Mensagem que indica que a simulacao esta a decorrer
	char* simDecorre;		//Mensagem que indica que a simulacao esta a decorrer
	char* nUtilizadores;	//Mensgem que antecede o numero de utilizadores
	char* nDesistencias;	//Mensgem que antecede o numero de desistentes
	char* tempoMedioEspera; //Mensgem que antecede a indicacao do tempo medio de espera
	char* oPaciente;		//O cliente
	char* entrou;			//entrou
	char* chegou;			//chegou
	char* saiu;				//saiu
	char* espera;			//espera
	char* desistiu;			//desisitiu
	char* centro;			
	char* salaEspera;		
	char* filaRua;		
	char* salaTeste;			
	char* internamento;				
	char* morador;				
	char* visitante;				
	char* testePositivo;
	char* testeNegativo;
	char* teve;
	char* filaDriveThru;
	char* testeDriveThru;
	char* esperaCidade;
	char* ruaCidade;
	char* testeCidade;
	char* internamentoCidade;
	char* drive;
	char* normal;
	char* isolamento_vila;
	char* isolamento_cidade;

}*apGlobMsgMonitor;