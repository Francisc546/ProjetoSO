#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "library.h"

/* Servidor do tipo socket stream.
   Recebe linhas do cliente e reenvia-as para o cliente */

//#include "unix.h"




typedef struct config{
        int num_centros;
		int pontos_testagem_vila;
        int sala_de_espera_vila;  //pt = pontos de testagem do centro 
        int fila_rua_vila;
        int casa_povo;
        int hotel_vila; // max_esp = máximo da sala de espera para o teste 
        int sala_internamento_vila;
        int abertura_centro;
		int encerramento_centro;
		int prob_positivo; // max_iso = máximo sala isolamento
		int tempo_morador;
		int tempo_visitante;
		int tempo_resultado_vila;		
		int abertura_centro_cidade;
		int encerramento_centro_cidade;
		int tempo_resultado_cidade;
		int sala_de_espera_cidade;
		int fila_rua_cidade;
		int pontos_testagem_cidade;
		int tempo_convencional;
		int pontos_drivethru;
		int fila_espera_drivethru;
		int tempo_drivethru;
		int internamento_cidade;
		int isolamento_cidade;
		

		
};

struct config dados;
void init(){
	//Trincos	
	pthread_mutex_init(&SocketMensagem,NULL);
	//Semáforo Vila
	sem_init(&sem_filaRua_vila,0,dados.fila_rua_vila);
	sem_init(&sem_sala_espera_vila,0,dados.sala_de_espera_vila);
	sem_init(&sem_internamento_vila,0,dados.sala_internamento_vila);
	sem_init(&sem_isolamento_vila,0,dados.casa_povo+dados.hotel_vila);
	sem_init(&sem_ponto_visitante,0,1);
	sem_init(&sem_ponto_morador,0,2);
	//Semáforos Cidade
	sem_init(&sem_filaRua_cidade,0,dados.fila_rua_cidade);
	sem_init(&sem_internamento_cidade,0,dados.internamento_cidade);
	sem_init(&sem_sala_espera_cidade,0,dados.sala_de_espera_cidade);
	sem_init(&sem_isolamento_cidade,0,dados.isolamento_cidade);
	sem_init(&sem_ponto_convencional,0,dados.pontos_testagem_cidade);
	sem_init(&sem_ponto_driveThru,0,dados.pontos_drivethru);
	sem_init(&sem_fila_espera_driveThru,0,dados.fila_espera_drivethru);
}

void carrega_config(){

	FILE *fconf = fopen("simulador.conf","r"); //abre o ficheiro da configuração em modo leitura

	char vect[100];
	char n[5];

	if(!fconf){
		printf("ERRO! Não foi possível abrir o ficheiro!");
		return;
	}
	while (fscanf(fconf, "%s = %s", vect, n) != EOF){

                if(strcmp(vect,"num_centros") == 0)
                        dados.num_centros = atoi(n);
                if(strcmp(vect,"sala_de_espera_vila") == 0)
                        dados.sala_de_espera_vila = atoi(n);
                if(strcmp(vect,"fila_rua_vila") == 0)
                        dados.fila_rua_vila = atoi(n);
                if(strcmp(vect,"casa_povo") == 0)
                        dados.casa_povo = atoi(n);

                if(strcmp(vect,"hotel_vila") == 0)
                        dados.hotel_vila = atoi(n);
                if(strcmp(vect,"sala_internamento_vila") == 0)
                        dados.sala_internamento_vila = atoi(n);
                if(strcmp(vect,"abertura_centro") == 0)
                        dados.abertura_centro = atoi(n);
				if(strcmp(vect,"encerramento_centro") == 0)
                        dados.encerramento_centro = atoi(n);
                if(strcmp(vect,"prob_positivo") == 0)
                        dados.prob_positivo = atoi(n);
                if(strcmp(vect,"tempo_morador") == 0)
                        dados.tempo_morador = atoi(n);
				if(strcmp(vect,"tempo_visitante") == 0)
                        dados.tempo_visitante = atoi(n);
				if(strcmp(vect,"pontos_testagem_vila") == 0)
                        dados.pontos_testagem_vila = atoi(n);
                if(strcmp(vect,"abertura_centro_cidade") == 0)
                        dados.abertura_centro_cidade = atoi(n);
				if(strcmp(vect,"encerramento_centro_cidade") == 0)
                        dados.encerramento_centro_cidade = atoi(n);
				if(strcmp(vect,"tempo_resultado_cidade") == 0)
                        dados.tempo_resultado_cidade = atoi(n);
					if(strcmp(vect,"tempo_resultado_vila") == 0)
                        dados.tempo_resultado_vila = atoi(n);
				if(strcmp(vect,"sala_de_espera_cidade") == 0)
                        dados.sala_de_espera_cidade = atoi(n);
				if(strcmp(vect,"fila_rua_cidade") == 0)
                        dados.fila_rua_cidade = atoi(n);
				if(strcmp(vect,"pontos_testagem_cidade") == 0)
                        dados.pontos_testagem_cidade = atoi(n);
				if(strcmp(vect,"tempo_convencional") == 0)
                        dados.tempo_convencional = atoi(n);
				if(strcmp(vect,"pontos_drivethru") == 0)
                        dados.pontos_drivethru = atoi(n);
				if(strcmp(vect,"fila_espera_drivethru") == 0)
                        dados.fila_espera_drivethru = atoi(n);
				if(strcmp(vect,"tempo_drivethru") == 0)
                        dados.tempo_drivethru = atoi(n);
				if(strcmp(vect,"internamento_cidade") == 0)
                        dados.internamento_cidade = atoi(n);
				if(strcmp(vect,"isolamento_cidade") == 0)
                        dados.isolamento_cidade = atoi(n);
				
					
                

        }

        fclose(fconf);
}
void escreve_aux(FILE *faux, char x[100], int dados){
		printf("%s",x);
        printf("%d\n",dados);
        fprintf(faux,"%s",x);
        fprintf(faux,"%d\n",dados);
}
void escreve_log(){
	FILE *f = fopen("simulador.log","w");
	if (!f){
        printf("Erro a abrir o ficheiro!\n");
		return;
	}
	escreve_aux(f,"Numero de centros de testagem: ",dados.num_centros);

	fprintf(f, "\n--Centro de Testagem Vila--\n");
    printf("\n--Centro de Testagem Vila--\n");
	escreve_aux(f,"Pontos de testagem: ",dados.pontos_testagem_vila);
	escreve_aux(f,"Capacidade máxima sala de espera: ",dados.sala_de_espera_vila);
	escreve_aux(f,"Capacidade máxima fila da rua: ",dados.fila_rua_vila);
	escreve_aux(f,"Capacidade máxima sala de isolamento: ",dados.casa_povo + dados.hotel_vila);
	escreve_aux(f,"Capacidade máxima internamento: ",dados.sala_internamento_vila);
	escreve_aux(f,"Hora de abertura: ",dados.abertura_centro);
	escreve_aux(f,"Hora de encerramento: ",dados.encerramento_centro);
	escreve_aux(f,"Tempo de espera resultado (horas): ",dados.tempo_resultado_vila);
	escreve_aux(f,"Tempo teste Visitante (minutos): ",dados.tempo_visitante);
	escreve_aux(f,"Tempo teste Morador (minutos): ",dados.tempo_morador);

	fprintf(f, "\n--Centro de Testagem Cidade--\n");
    printf("\n--Centro de Testagem Cidade--\n");
	escreve_aux(f,"Pontos de testagem normais: ",dados.pontos_testagem_cidade);
	escreve_aux(f,"Pontos de testagem Drive-Thru: ",dados.pontos_drivethru);
	escreve_aux(f,"Capacidade máxima sala de espera: ",dados.sala_de_espera_cidade);
	escreve_aux(f,"Capacidade máxima fila da rua: ",dados.fila_rua_cidade);
	escreve_aux(f,"Capacidade máxima isolamento: ",dados.isolamento_cidade);
	escreve_aux(f,"Capacidade máxima internamento: ",dados.internamento_cidade);
	escreve_aux(f,"Hora de abertura: ",dados.abertura_centro_cidade);
	escreve_aux(f,"Hora de encerramento: ",dados.encerramento_centro_cidade);
	escreve_aux(f,"Tempo de espera resultado (horas): ",dados.tempo_resultado_cidade);
	escreve_aux(f,"Tempo teste convencional (minutos): ",dados.tempo_convencional);
	escreve_aux(f,"Tempo teste Drive-Thru (minutos): ",dados.tempo_drivethru);
	
	fprintf(f, "\n--Outros Dados--\n");
    printf("\n--Outros Dados--\n");
	/*escreve_aux(f,"Número de pacientes por minuto: ",dados.freq_ent_pacientes);
	escreve_aux(f,"Teste Rápido: ",dados.prob_teste_rapido);*/
	escreve_aux(f,"Teste Positivo: ",dados.prob_positivo);
	//escreve_aux(f,"Teste Inconclusivo: ",dados.prob_inconclusivo);
	

	fclose(f);
}

void *PacienteMorador (pthread_t* appthread){
	int tipoPaciente = MORADOR;
	int estado;
	long id = pthread_self();
	int seccao;	
	time_t horaChegada, horaSaida;
	sem_wait(&sem_filaRua_vila); // decrementa o semáforo que começou a 5
	horaChegada = tempoAtual();
	pthread_mutex_lock(&SocketMensagem);
	estado = ENTROU;
	seccao = FILARUA;
	total_rua_vila = total_rua_vila+1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);
	pthread_mutex_unlock(&SocketMensagem);
	sem_wait(&sem_sala_espera_vila); //decrementa o semáforo que começou a 10	 equivalente ao produtor
	pthread_mutex_lock(&SocketMensagem);
	total_rua_vila = total_rua_vila-1;
	total_sala_espera_vila = total_sala_espera_vila+1;
	estado = ENTROU;
	seccao = SALAESPERA;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);
	pthread_mutex_unlock(&SocketMensagem);
	sem_post(&sem_filaRua_vila); // Como o paciente entrou na sala de espera liberta 1 lugar na fila de espera
	sem_wait(&sem_ponto_morador); // Entra sala de teste
	sem_post(&sem_sala_espera_vila); // Liberta vaga sala de espera
	pthread_mutex_lock(&SocketMensagem);
	estado = CHEGOU;
	seccao = SALATESTE;
	total_sala_espera_vila = total_sala_espera_vila-1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);
	sleep(3); // Simula tempo de realizar teste/limpar sala 3 segundos = 12 minutos
	horaSaida = tempoAtual();
	pthread_mutex_lock(&prot_dados);
	total_tempo_vila= total_tempo_vila + (horaSaida - horaChegada);
	total_testes_vila= total_testes_vila+1;
	pthread_mutex_unlock(&prot_dados);
	sem_wait(&sem_isolamento_vila);
	sem_post(&sem_ponto_morador);
	pthread_mutex_lock(&SocketMensagem);
	estado = ENTROU;
	seccao = ISOLAMENTOVILA;
	total_isolamento_vila = total_isolamento_vila+1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);
	sleep(180); // Simula tempo de esperar pelo teste 24 horas = 6 minutos = 360 segundos
	pthread_mutex_lock(&SocketMensagem);
	int teste_res  = (rand() % 100 ) +1;
	if(teste_res > dados.prob_positivo){		
		seccao = TESTENEGATIVO;
		total_negativos_vila= total_negativos_vila+1;
	}else{		
		seccao = TESTEPOSITIVO;
		total_positivos_vila= total_positivos_vila+1;
	}
	estado = TEVE;	
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);	 
	sem_post(&sem_isolamento_vila);
	pthread_mutex_lock(&SocketMensagem);
	if(seccao == TESTENEGATIVO){
		estado = SAIU;
		seccao = ISOLAMENTOVILA;
		total_isolamento_vila = total_isolamento_vila-1;
		str_cli(sockfd,tipoPaciente,estado,id,seccao);	
		pthread_mutex_unlock(&SocketMensagem);	
		pthread_kill(appthread);
		
	}else if(seccao== TESTEPOSITIVO){
		int intern = (rand() % 100) +1;
		if(intern <31){
			estado = ENTROU;
			seccao = INTERNAMENTO;
			total_isolamento_vila = total_isolamento_vila-1;
			total_internamento_vila = total_internamento_vila+1;
			str_cli(sockfd,tipoPaciente,estado,id,seccao);	
			pthread_mutex_unlock(&SocketMensagem);
			
		}else{
			estado = SAIU;
			seccao = ISOLAMENTOVILA;
			total_isolamento_vila = total_isolamento_vila-1;
			str_cli(sockfd,tipoPaciente,estado,id,seccao);	
			pthread_mutex_unlock(&SocketMensagem);
			pthread_kill(appthread);
		}
			
		
	}	
	
}

void *pacienteDrive (pthread_t* appthread){
	int tipoPaciente = DRIVE;
	int estado;
	long id = pthread_self();
	int seccao;	
	time_t horaChegada, horaSaida;
	sem_wait(&sem_fila_espera_driveThru); // decrementa o semáforo que começou a 5
	horaChegada = tempoAtual();
	pthread_mutex_lock(&SocketMensagem);
	estado = ENTROU;
	seccao = FILADRIVE;
	total_fila_espera_drive = total_fila_espera_drive+1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);
	pthread_mutex_unlock(&SocketMensagem);
	sem_wait(&sem_ponto_driveThru); // Entra sala de teste visitantes
	sem_post(&sem_fila_espera_driveThru); // Liberta vaga fila da rua
	pthread_mutex_lock(&SocketMensagem);
	estado = CHEGOU;
	seccao = TESTEDRIVE;
	total_fila_espera_drive = total_fila_espera_drive-1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);
	sleep(1); // Simula tempo de realizar teste/limpar sala 1 segundos = 4 minutos
	horaSaida = tempoAtual();
	pthread_mutex_lock(&prot_dados);
	total_tempo= total_tempo + (horaSaida - horaChegada);
	total_testes= total_testes+1;
	pthread_mutex_unlock(&prot_dados);
	sem_wait(&sem_isolamento_cidade);
	sem_post(&sem_ponto_driveThru);
	pthread_mutex_lock(&SocketMensagem);
	estado = ENTROU;
	seccao = INTERNAMENTOCIDADE;
	total_isolamento_cidade = total_isolamento_cidade+1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);
	sleep(150); // Simula tempo de esperar pelo teste 20 horas = 5 minutos = 300 segundos
	pthread_mutex_lock(&SocketMensagem);
	int teste_res  = (rand() % 100 ) +1;
	if(teste_res > dados.prob_positivo){		
		seccao = TESTENEGATIVO;
		total_negativos_cidade= total_negativos_cidade+1;
	}else{		
		seccao = TESTEPOSITIVO;
		total_positivos_cidade= total_positivos_cidade+1;
	}
	estado = TEVE;	
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);	 
	sem_post(&sem_isolamento_cidade);
	pthread_mutex_lock(&SocketMensagem);
	if(seccao == TESTENEGATIVO){
		estado = SAIU;
		seccao = ISOLAMENTOCIDADE;
		total_isolamento_cidade = total_isolamento_cidade-1;
		str_cli(sockfd,tipoPaciente,estado,id,seccao);	
		pthread_mutex_unlock(&SocketMensagem);	
		pthread_kill(appthread);
		
	}else if(seccao== TESTEPOSITIVO){
		int intern = (rand() % 100) +1;
		if(intern <31){
			estado = ENTROU;
			seccao = INTERNAMENTOCIDADE;
			total_isolamento_cidade = total_isolamento_cidade-1;
			total_internamento_cidade = total_internamento_cidade+1;
			str_cli(sockfd,tipoPaciente,estado,id,seccao);	
			pthread_mutex_unlock(&SocketMensagem);
			
		}else{
			estado = SAIU;
			seccao = ISOLAMENTOCIDADE;
			total_isolamento_cidade = total_isolamento_cidade-1;
			str_cli(sockfd,tipoPaciente,estado,id,seccao);	
			pthread_mutex_unlock(&SocketMensagem);
			pthread_kill(appthread);
		}
			
		
	}
	
}

void *pacienteConv (pthread_t* appthread){
	int tipoPaciente = NORMAL;
	int estado;
	long id = pthread_self();
	int seccao;	
	time_t horaChegada, horaSaida;
	sem_wait(&sem_filaRua_cidade); // decrementa o semáforo que começou a 5
	horaChegada = tempoAtual();
	pthread_mutex_lock(&SocketMensagem);
	estado = ENTROU;
	seccao = FILARUACIDADE;
	total_rua_cidade = total_rua_cidade+1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);
	pthread_mutex_unlock(&SocketMensagem);
	sem_wait(&sem_sala_espera_cidade); //decrementa o semáforo que começou a 10	 equivalente ao produtor
	pthread_mutex_lock(&SocketMensagem);
	total_rua_cidade = total_rua_cidade-1;
	total_sala_espera_cidade = total_sala_espera_cidade+1;
	estado = ENTROU;
	seccao = SALAESPERA;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);
	pthread_mutex_unlock(&SocketMensagem);
	sem_post(&sem_filaRua_cidade); // Como o paciente entrou na sala de espera liberta 1 lugar na fila de espera
	sem_wait(&sem_ponto_convencional); // Entra sala de teste
	sem_post(&sem_sala_espera_cidade); // Liberta vaga sala de espera
	pthread_mutex_lock(&SocketMensagem);
	estado = CHEGOU;
	seccao = SALATESTECIDADE;
	total_sala_espera_cidade = total_sala_espera_cidade-1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);
	sleep(3); // Simula tempo de realizar teste/limpar sala 3 segundos = 12 minutos
	horaSaida = tempoAtual();
	pthread_mutex_lock(&prot_dados);
	total_tempo_cidade= total_tempo_cidade + (horaSaida - horaChegada);
	total_testes_cidade= total_testes_cidade+1;
	pthread_mutex_unlock(&prot_dados);
	sem_wait(&sem_isolamento_cidade);
	sem_post(&sem_ponto_convencional);
	pthread_mutex_lock(&SocketMensagem);
	estado = ENTROU;
	seccao = INTERNAMENTOCIDADE;
	total_isolamento_cidade = total_isolamento_cidade+1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);
	sleep(150); // Simula tempo de esperar pelo teste 20 horas = 5 minutos = 300 segundos
	pthread_mutex_lock(&SocketMensagem);
	int teste_res  = (rand() % 100 ) +1;
	if(teste_res > dados.prob_positivo){		
		seccao = TESTENEGATIVO;
		total_negativos_cidade= total_negativos_cidade+1;
	}else{		
		seccao = TESTEPOSITIVO;
		total_positivos_cidade= total_positivos_cidade+1;
	}
	estado = TEVE;	
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);	 
	sem_post(&sem_isolamento_cidade);
	pthread_mutex_lock(&SocketMensagem);
	if(seccao == TESTENEGATIVO){
		estado = SAIU;
		seccao = ISOLAMENTOCIDADE;
		total_isolamento_cidade = total_isolamento_cidade-1;
		str_cli(sockfd,tipoPaciente,estado,id,seccao);	
		pthread_mutex_unlock(&SocketMensagem);	
		pthread_kill(appthread);
		
	}else if(seccao== TESTEPOSITIVO){
		int intern = (rand() % 100) +1;
		if(intern <31){
			estado = ENTROU;
			seccao = INTERNAMENTOCIDADE;
			total_isolamento_cidade = total_isolamento_cidade-1;
			total_internamento_cidade = total_internamento_cidade+1;
			str_cli(sockfd,tipoPaciente,estado,id,seccao);	
			pthread_mutex_unlock(&SocketMensagem);
			
		}else{
			estado = SAIU;
			seccao = ISOLAMENTOCIDADE;
			total_isolamento_cidade = total_isolamento_cidade-1;
			str_cli(sockfd,tipoPaciente,estado,id,seccao);	
			pthread_mutex_unlock(&SocketMensagem);
			pthread_kill(appthread);
		}
			
		
	}
	
}


void *pacienteVisitante (pthread_t* appthread){
	int tipoPaciente = VISITANTE;
	int estado;
	long id = pthread_self();
	int seccao;	
	time_t horaChegada, horaSaida;
	sem_wait(&sem_filaRua_vila); // decrementa o semáforo que começou a 5
	horaChegada = tempoAtual();
	pthread_mutex_lock(&SocketMensagem);
	estado = ENTROU;
	seccao = FILARUA;
	total_rua_vila = total_rua_vila+1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);
	pthread_mutex_unlock(&SocketMensagem);
	sem_wait(&sem_ponto_visitante); // Entra sala de teste visitantes
	sem_post(&sem_filaRua_vila); // Liberta vaga fila da rua
	pthread_mutex_lock(&SocketMensagem);
	estado = CHEGOU;
	seccao = SALATESTE;
	total_rua_vila = total_rua_vila-1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);
	sleep(2); // Simula tempo de realizar teste/limpar sala 3 segundos = 12 minutos
	horaSaida = tempoAtual();
	pthread_mutex_lock(&prot_dados);
	total_tempo_vila= total_tempo_vila + (horaSaida - horaChegada);
	total_testes_vila= total_testes_vila+1;
	pthread_mutex_unlock(&prot_dados);
	sem_wait(&sem_isolamento_vila);
	sem_post(&sem_ponto_visitante);
	pthread_mutex_lock(&SocketMensagem);
	estado = ENTROU;
	seccao = ISOLAMENTOVILA;
	total_isolamento_vila = total_isolamento_vila+1;
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);
	sleep(180); // Simula tempo de esperar pelo teste 24 horas = 6 minutos = 360 segundos
	pthread_mutex_lock(&SocketMensagem);
	int teste_res  = (rand() % 100 ) +1;
	if(teste_res > dados.prob_positivo){		
		seccao = TESTENEGATIVO;
		total_negativos_vila= total_negativos_vila+1;
	}else{		
		seccao = TESTEPOSITIVO;
		total_positivos_vila= total_positivos_vila+1;
	}
	estado = TEVE;	
	str_cli(sockfd,tipoPaciente,estado,id,seccao);	
	pthread_mutex_unlock(&SocketMensagem);	 
	sem_post(&sem_isolamento_vila);
	pthread_mutex_lock(&SocketMensagem);
	if(seccao == TESTENEGATIVO){
		estado = SAIU;
		seccao = ISOLAMENTOVILA;
		total_isolamento_vila = total_isolamento_vila-1;
		str_cli(sockfd,tipoPaciente,estado,id,seccao);	
		pthread_mutex_unlock(&SocketMensagem);
		pthread_kill(appthread);
		
	}else if(seccao== TESTEPOSITIVO){
		int intern = (rand() % 100) +1;
		if(intern <31){
			estado = ENTROU;
			seccao = INTERNAMENTO;
			total_isolamento_vila = total_isolamento_vila-1;
			total_internamento_vila = total_internamento_vila+1;
			str_cli(sockfd,tipoPaciente,estado,id,seccao);	
			pthread_mutex_unlock(&SocketMensagem);
			
		}else{
			estado = SAIU;
			seccao = ISOLAMENTOVILA;
			total_isolamento_vila = total_isolamento_vila-1;
			str_cli(sockfd,tipoPaciente,estado,id,seccao);	
			pthread_mutex_unlock(&SocketMensagem);
			pthread_kill(appthread);
		}
			
		
	}
	
	
}


void * criaPacientes(pthread_t* appthread){
	
	int total = 0;
	time_t tempoAtual = time(NULL); // Simulação começa as 08H (Hora de abertura do centro da vila)
	time_t open_centro_cidade = tempoAtual + 15; // O centro da cidade abre as 09H (1 hora = 15 segundos simulados)
	time_t fecho_centro = tempoAtual +180; //Ambos fecham as 20h
	time_t tempoSimulacao = tempoAtual + 200;//Tempo total da simulação 2 dias	mudar para 720 (2 dias)	
	while (verificaPassagemTempo(tempoSimulacao)==0)
	{
		if(time(NULL) < open_centro_cidade /*|| tempoAtual+360< time(NULL)< open_centro_cidade+360*/){ // Antes da abertura do centro 
			//	printf("\n TESTE WHILE \n");
			int aleatorio  = (rand() % 100 ) +1; 
			sleep(1); //consome tempo
			if(aleatorio > 25)
			{
				pthread_t  paciente;
				paciente = malloc (sizeof (pthread_t));
				if(paciente != NULL)
				{
					total++;
					int n =  pthread_create(paciente, NULL, PacienteMorador, paciente);
					if(n)
					{
						printf("Erro ao criar pacienteMorador ");
						exit(1);
					}
				}
				else
				{
					printf("Erro ao alocar memoria");
				}
			}
			else{
				pthread_t  paciente;
				paciente = malloc (sizeof (pthread_t));
				if(paciente != NULL)
				{
					total++;
					int n =  pthread_create(paciente, NULL, pacienteVisitante, paciente);
					if(n)
					{
						printf("Erro ao criar pacienteVisistante ");
						exit(1);
					}
				}
				else
				{
					printf("Erro ao alocar memoria");
				}
			}
		}
		else if( open_centro_cidade<time(NULL) <fecho_centro || open_centro_cidade+360<time(NULL) <fecho_centro+360){
			//	printf("\n TESTE WHILE \n");
			int aleatorio  = (rand() % 100 ) +1; 
			sleep(1); //consome tempo
			if( 86 >aleatorio > 50) // Cria Paciente Morador
			{
				pthread_t  paciente;
				paciente = malloc (sizeof (pthread_t));
				if(paciente != NULL)
				{
					total++;
					int n =  pthread_create(paciente, NULL, PacienteMorador, paciente);
					if(n)
					{
						printf("Erro ao criar pacienteMorador ");
						exit(1);
					}
				}
				else
				{
					printf("Erro ao alocar memoria");
				}
			}
			else if(aleatorio >85){ // Cria Paciente Visitante
				pthread_t  paciente;
				paciente = malloc (sizeof (pthread_t));
				if(paciente != NULL)
				{
					total++;
					int n =  pthread_create(paciente, NULL, pacienteVisitante, paciente);
					if(n)
					{
						printf("Erro ao criar pacienteVisistante ");
						exit(1);
					}
				}
				else
				{
					printf("Erro ao alocar memoria");
				}
			}
			else if(aleatorio <26){ // Cria paciente que irá ao drive thru Cidade
				pthread_t  paciente;
				paciente = malloc (sizeof (pthread_t));
				if(paciente != NULL)
				{
					total++;
					int n =  pthread_create(paciente, NULL, pacienteDrive, paciente);
					if(n)
					{
						printf("Erro ao criar pacienteDrive ");
						exit(1);
					}
				}
				else
				{
					printf("Erro ao alocar memoria");
				}
			}
			else{ // Cria paciente que irá fazer teste convencional Cidade
				pthread_t  paciente;
				paciente = malloc (sizeof (pthread_t));
				if(paciente != NULL)
				{
					total++;
					int n =  pthread_create(paciente, NULL, pacienteConv, paciente);
					if(n)
					{
						printf("Erro ao criar pacienteConv ");
						exit(1);
					}
				}
				else
				{
					printf("Erro ao alocar memoria");
				}
			}
		}
		
		

	}
	printf("\n##### VILA #####\n");
	printf("Testes realizados: %i. \n",total_testes_vila);
	int media_vila = (total_tempo_vila/total_testes_vila)*4;
	printf("Média: %i. \n", (total_tempo_vila/total_testes_vila)*4);
	printf("Positivos: %i. \n", total_positivos_vila);
	printf("Negativos: %i. \n", total_negativos_vila);
	printf("Rua_Vila: %i. \n", total_rua_vila);
	printf("Sala Espera Vila: %i. \n", total_sala_espera_vila);
	printf("Isolamento Vila: %i. \n", total_isolamento_vila);
	printf("Internamento Vila: %i. \n", total_internamento_vila);
	//printf("Threads Criadas: %i. \n",total);
	
	printf("\n##### CIDADE #####\n");
	
	//printf("Tempo total: %i. \n",total_tempo);
	printf("Testes realizados: %i. \n",total_testes_cidade);
	int media_cidade = (total_tempo_cidade/total_testes_cidade)*4;
	printf("Média: %i. \n", (total_tempo_cidade/total_testes_cidade)*4);
	printf("Positivos: %i. \n", total_positivos_cidade);
	printf("Negativos: %i. \n", total_negativos_cidade);
	printf("Rua Cidade: %i. \n", total_rua_cidade);
	printf("Sala Espera Cidade: %i. \n", total_sala_espera_cidade);
	printf("Isolamento Cidade: %i. \n", total_isolamento_cidade);
	printf("Internamento Cidade: %i. \n", total_internamento_cidade);
	//printf("Threads Criadas: %i. \n",total);
	
	printf("\n##### TOTAL #####\n");
	//printf("Tempo total: %i. \n",total_tempo);
	printf("Testes realizados: %i. \n",total_testes_vila+total_testes_cidade);
	int total_test =total_testes_vila+total_testes_cidade;
	int total_time =total_tempo_vila/total_tempo_cidade;
	//printf("Média: %i. \n", total_time/total_test);
	printf("Média: %i. \n", (media_cidade+media_vila)/2);
	printf("Positivos: %i. \n", total_positivos_vila+total_positivos_cidade);
	printf("Negativos: %i. \n", total_negativos_cidade+total_negativos_vila);
	printf("Isolamento Total: %i. \n", total_isolamento_vila+total_isolamento_cidade);
	printf("Internamento Total: %i. \n", total_internamento_vila+total_internamento_cidade);
	printf("Threads Criadas: %i. \n",total);
}

main(void){
	
	carrega_config();
	init();
	//escreve_log();
	printf("\n--Configuração Completa--\n");
	criaSocketCliente();
	printf("\n--Socket cliente criado--\n");
	pthread_t pacientes;
	printf("TESTe");
	int n = pthread_create(&pacientes,NULL,criaPacientes,NULL);
	if(n)
		{
			printf("Não foi possivel criar uma tarefa. ERRO %i",n);
			exit(1);
		}
	pthread_join(pacientes,NULL);
}
