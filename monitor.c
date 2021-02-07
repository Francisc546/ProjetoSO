
/* Cliente do tipo socket stream.
   L▒ linhas do teclado e envia-as para o servidor */

#include "library.h"
#define MAXLINE 512
#include<time.h>
#include <unistd.h> 


struct mensagemMonitor* carregaMonitor(){
	size_t len = 0;
	FILE* abreFile = fopen("frases.conf", "r");

	if(abreFile==NULL)
		printf("Erro ao abrir o ficheiro: frases");
	else
	{
		struct mensagemMonitor *msgMonitor = malloc(sizeof(struct mensagemMonitor));
		len = getline(&(msgMonitor->indicaEstado), &len, abreFile);
		if((msgMonitor->indicaEstado)[len - 1] == '\n') {
			((msgMonitor->indicaEstado))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->simTerminada), &len, abreFile);
		if((msgMonitor->simTerminada)[len - 1] == '\n') {
			((msgMonitor->simTerminada))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->simDecorre), &len, abreFile);
		if((msgMonitor->simDecorre)[len - 1] == '\n') {
			((msgMonitor->simDecorre))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->nUtilizadores), &len, abreFile);
		if((msgMonitor->nUtilizadores)[len - 1] == '\n') {
			((msgMonitor->nUtilizadores))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->nDesistencias), &len, abreFile);
		if((msgMonitor->nDesistencias)[len - 1] == '\n') {
			((msgMonitor->nDesistencias))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->tempoMedioEspera), &len, abreFile);
		if((msgMonitor->tempoMedioEspera)[len - 1] == '\n') {
			((msgMonitor->tempoMedioEspera))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->oPaciente), &len, abreFile);
		if((msgMonitor->oPaciente)[len - 1] == '\n') {
			((msgMonitor->oPaciente))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->entrou), &len, abreFile);
		if((msgMonitor->entrou)[len - 1] == '\n') {
			((msgMonitor->entrou))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->chegou), &len, abreFile);
		if((msgMonitor->chegou)[len - 1] == '\n') {
			((msgMonitor->chegou))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->saiu), &len, abreFile);
		if((msgMonitor->saiu)[len - 1] == '\n') {
			((msgMonitor->saiu))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->espera), &len, abreFile);
		if((msgMonitor->espera)[len - 1] == '\n') {
			((msgMonitor->espera))[len - 1] = '\0';
		}			
		len = getline(&(msgMonitor->desistiu), &len, abreFile);
		if((msgMonitor->desistiu)[len - 1] == '\n') {
			((msgMonitor->desistiu))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->centro), &len, abreFile);
		if((msgMonitor->centro)[len - 1] == '\n') {
			((msgMonitor->centro))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->salaEspera), &len, abreFile);
		if((msgMonitor->salaEspera)[len - 1] == '\n') {
			((msgMonitor->salaEspera))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->filaRua), &len, abreFile);
		if((msgMonitor->filaRua)[len - 1] == '\n') {
			((msgMonitor->filaRua))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->salaTeste), &len, abreFile);
		if((msgMonitor->salaTeste)[len - 1] == '\n') {
			((msgMonitor->salaTeste))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->internamento), &len, abreFile);
		if((msgMonitor->internamento)[len - 1] == '\n') {
			((msgMonitor->internamento))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->morador), &len, abreFile);
		if((msgMonitor->morador)[len - 1] == '\n') {
			((msgMonitor->morador))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->visitante), &len, abreFile);
		if((msgMonitor->visitante)[len - 1] == '\n') {
			((msgMonitor->visitante))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->testePositivo), &len, abreFile);// AQUIIIIIII
		if((msgMonitor->testePositivo)[len - 1] == '\n') {
			((msgMonitor->testePositivo))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->testeNegativo), &len, abreFile);
		if((msgMonitor->testeNegativo)[len - 1] == '\n') {
			((msgMonitor->testeNegativo))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->teve), &len, abreFile);
		if((msgMonitor->teve)[len - 1] == '\n') {
			((msgMonitor->teve))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->filaDriveThru), &len, abreFile);
		if((msgMonitor->filaDriveThru)[len - 1] == '\n') {
			((msgMonitor->filaDriveThru))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->testeDriveThru), &len, abreFile);
		if((msgMonitor->testeDriveThru)[len - 1] == '\n') {
			((msgMonitor->testeDriveThru))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->esperaCidade), &len, abreFile);
		if((msgMonitor->esperaCidade)[len - 1] == '\n') {
			((msgMonitor->esperaCidade))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->ruaCidade), &len, abreFile);
		if((msgMonitor->ruaCidade)[len - 1] == '\n') {
			((msgMonitor->ruaCidade))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->testeCidade), &len, abreFile);
		if((msgMonitor->testeCidade)[len - 1] == '\n') {
			((msgMonitor->testeCidade))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->internamentoCidade), &len, abreFile);
		if((msgMonitor->internamentoCidade)[len - 1] == '\n') {
			((msgMonitor->internamentoCidade))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->drive), &len, abreFile);
		if((msgMonitor->drive)[len - 1] == '\n') {
			((msgMonitor->drive))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->normal), &len, abreFile);
		if((msgMonitor->normal)[len - 1] == '\n') {
			((msgMonitor->normal))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->isolamento_vila), &len, abreFile);
		if((msgMonitor->isolamento_vila)[len - 1] == '\n') {
			((msgMonitor->isolamento_vila))[len - 1] = '\0';
		}
		len = getline(&(msgMonitor->isolamento_cidade), &len, abreFile);
		if((msgMonitor->isolamento_cidade)[len - 1] == '\n') {
			((msgMonitor->isolamento_cidade))[len - 1] = '\0';
		}
		
		fclose(abreFile);
		return msgMonitor;

	}
}


main(void){
	//exporta();
	//printf("teste";)
	apGlobMsgMonitor = carregaMonitor(); 
	printf(apGlobMsgMonitor->morador);
	printf("Time atual :%u",time(NULL));
	cria_socket_servidor();
}
