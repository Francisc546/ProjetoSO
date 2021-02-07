#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "library.h"
#define MAXLINE 512

/* Cliente do tipo socket stream.
   L▒ string de fp e envia para sockfd.
   L▒ string de sockfd e envia para stdout */


void escreve_aux_sockets(FILE *faux, char *mensagem){
		printf("%s\n",mensagem);
        fprintf(faux,"%s\n",mensagem);
} 
char menu()
{
	printf("##################SIMULACAO###################\n");
	printf("# Escolha uma opção:                         #\n");
	printf("#           1 - Iniciar simulação            #\n");
	printf("#           2 - Terminar programa            #\n");
	printf("##############################################\n");
	char opcao[MAXLINE];
	do{
		scanf("%s",opcao);
		if((opcao[0] == '1' || opcao[0] == '2' ) && strlen(opcao) == 1)
		{
			break;
		}
		else
		{
			printf("Opção inválida");
			opcao[0] = '\0';
		}
	}while(strlen(opcao) > 1 || strlen(opcao) <= 0 );

	return opcao[0];
}
str_cli(int sockfd, int tipoPessoa, int acao, long id, int centro){
	int n;
	char msgConcat[MAXLINE] = {};
	//Composicao da stream de envio pro socket
	sprintf(msgConcat,"%i %i %ld %i ",tipoPessoa,acao,id,centro);
	n = write(sockfd,msgConcat,MAXLINE);
	if (n < 0) error("ERROR writing to socket");
}

int str_echo(int sockfd){
	int n ;
	char buffer[MAXLINE];
	char msgConcat[MAXLINE];
	char tid[MAXLINE];
	for(;;){
		bzero(buffer,MAXLINE);
		bzero(msgConcat,MAXLINE);
		char tid[MAXLINE];
		int tipoPessoa, acao, id,centro = -1;
		char _tipoPess[5], _acao[5], _id[200], _centro[5];
		bzero(_tipoPess,5);
		bzero(_id,200);
		bzero(_centro,5);
		bzero(_acao,5);
		n = read(sockfd,buffer,MAXLINE);
		if(n == 0) return 0;
		if (n < 0) error("ERROR reading from socket");
		//No final da simulção o simulador envia para o socket o comando finito.
		if(!strcmp(buffer,"finito"))
		{
			return 1;
		}
		else
		{
			//Desconstroi os codigos do socket e que vao ser escritos
			int j = 0;
			int k = 0;
			for(int i = 0 ;i <= 3;i++)
			{
				k= 0;
				for(;buffer[j] != ' ';j++)
				{
					//Acumula os valores do buffer
					if(i == 0)
					{
						_tipoPess[k] = buffer[j];
					}
					if(i == 1)
					{
						_acao[k]= buffer[j];
					}
					if(i== 2)
					{
						_id[k]= buffer[j];
					}
					if(i == 3)
					{
						_centro[k] = buffer[j];
					}
					k++;
				}
				j++;
			}
			//Converte os valores lidos do buffer para tipo inteiro até ao primeiro valor livre
			tipoPessoa = atoi(_tipoPess);
			acao =	atoi(_acao);
			id = atoi(_id);
			centro = atoi(_centro);			
			strcat(msgConcat, apGlobMsgMonitor->oPaciente);
			
			sprintf(tid, "%ld ", id);



			if(tipoPessoa == MORADOR)
				strcat(msgConcat,apGlobMsgMonitor->morador);
			else if(tipoPessoa == VISITANTE)
				strcat(msgConcat,apGlobMsgMonitor->visitante);
			else if(tipoPessoa == DRIVE)
				strcat(msgConcat,apGlobMsgMonitor->drive);
			else if(tipoPessoa == NORMAL)
				strcat(msgConcat,apGlobMsgMonitor->normal);
			strcat(msgConcat,tid);
			if(acao == CHEGOU)
				strcat(msgConcat,apGlobMsgMonitor->chegou);
			else if(acao == ENTROU)
				strcat(msgConcat,apGlobMsgMonitor->entrou);
			else if(acao == SAIU)
				strcat(msgConcat,apGlobMsgMonitor->saiu);
			else if(acao == ESPERA)
				strcat(msgConcat,apGlobMsgMonitor->espera);
			else if (acao == DESISTIU)
				strcat(msgConcat,apGlobMsgMonitor->desistiu);
			else if (acao == TEVE)
				strcat(msgConcat,apGlobMsgMonitor->teve);
			if(centro == CENTRO)
				strcat(msgConcat,apGlobMsgMonitor->centro);
			else if(centro == SALAESPERA)
				strcat(msgConcat,apGlobMsgMonitor->salaEspera);
			else if(centro == ESPERACIDADE)
				strcat(msgConcat,apGlobMsgMonitor->esperaCidade);
			else if(centro == FILARUA)
				strcat(msgConcat,apGlobMsgMonitor->filaRua);
			else if(centro == FILARUACIDADE)
				strcat(msgConcat,apGlobMsgMonitor->ruaCidade);
			else if(centro == SALATESTE)
				strcat(msgConcat,apGlobMsgMonitor->salaTeste);
			else if(centro == SALATESTECIDADE)
				strcat(msgConcat,apGlobMsgMonitor->testeCidade);
			else if(centro == INTERNAMENTO)
				strcat(msgConcat,apGlobMsgMonitor->internamento);
			else if(centro == INTERNAMENTOCIDADE)
				strcat(msgConcat,apGlobMsgMonitor->internamentoCidade);
			else if(centro == TESTEPOSITIVO)
				strcat(msgConcat,apGlobMsgMonitor->testePositivo);
			else if(centro == TESTENEGATIVO)
				strcat(msgConcat,apGlobMsgMonitor->testeNegativo);
			else if(centro == FILADRIVE)
				strcat(msgConcat,apGlobMsgMonitor->filaDriveThru);
			else if(centro == TESTEDRIVE)
				strcat(msgConcat,apGlobMsgMonitor->testeDriveThru);
			else if(centro == ISOLAMENTOVILA)
				strcat(msgConcat,apGlobMsgMonitor->isolamento_vila);
			else if(centro == ISOLAMENTOCIDADE)
				strcat(msgConcat,apGlobMsgMonitor->isolamento_cidade);
			
			strcat(msgConcat, "\n");


		}
		//Escreve logs

		//pthread_mutex_lock(&protStats);
		//efetuaEstatisticas(centro,acao);
		//pthread_mutex_unlock(&protStats);
		FILE *f = fopen("monitor.log","w");
		escreve_aux_sockets(f,msgConcat);
		
	}
}

void criaSocketCliente()
{
	int servlen;
	struct sockaddr_un serv_addr;
	int n;
	char buffer[MAXLINE];

	/* Cria socket stream */

	if ((sockfd= socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		err_dump("client: can't open stream socket");


	bzero((char *) &serv_addr, sizeof(serv_addr)); // Limpa o socket coloca 0 em todas as posicoes de memoria
	serv_addr.sun_family = AF_UNIX; //Dominio que se vai utilizar

	strcpy(serv_addr.sun_path, UNIXSTR_PATH);
	servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
	//Tenta ligar-se ao ao servidor
	if (connect(sockfd, (struct sockaddr *) &serv_addr, servlen) < 0)
		err_dump("client: can't connect to server");
	//Fica à escuta do simulador
	for (;;)
	{
		bzero(buffer,MAXLINE);
		n = read(sockfd,buffer,MAXLINE);
		if (n < 0) error("ERROR reading from socket");

		if(!strcmp(buffer,"inicia"))
		{
			break;
		}
		else if(!strcmp(buffer,"finito"))
		{
			exit(1);
		}
	}

}

void cria_socket_servidor(){
	int newsockfd, clilen, childpid, servlen;
	struct sockaddr_un cli_addr, serv_addr;
	int n ;
	char option;
	/* Cria socket stream */
	if ((sockfd = socket(AF_UNIX,SOCK_STREAM,0)) < 0)
		err_dump("server: can't open stream socket");
	//Apontador pra buffer e tamanho buffer limpa o buffer
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, UNIXSTR_PATH);


	servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
	//Elimina o socket pré existente
	unlink(UNIXSTR_PATH);
	//sockfd nome do socket
	if (bind(sockfd, (struct sockaddr *) &serv_addr, servlen) < 0)
		err_dump("server, can't bind local address");

	listen(sockfd, 5);

	clilen = sizeof(cli_addr);
	printf("\n A aguardar pelo simulador ... \n");
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0)
		error("ERROR on accept");

	//Interface para o utilizador 
	option = menu();

	switch(option){
	case '1':
		//printf("Teste1");
		//Envia comando para o simulador para que este inicie
		n = write(newsockfd,"inicia",6);
		if (n < 0){ error("ERROR writing to socket");}

		//sem_post(&aguardaSimulStart);
		break;
	case '2':
		//printf("Teste2");
		n = write(newsockfd,"finito",6);
		if (n < 0) error("ERROR writing to socket");
		close(newsockfd);
		close(sockfd);
		printf("Prima [ENTER] para terminar... \n");
		getchar();

		//exit(1);
		return;
	}

	//Depois irá ficar a escutar
	for(;;)
	{
		if(str_echo(newsockfd) == 1)
		{
			break;
		};
	}

	//espera por enter termina
	close(newsockfd);
	close(sockfd);
	//exit(0);
	return;

}

