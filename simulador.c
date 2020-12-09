#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "library.h"

typedef struct config{
        int num_centros;
		
        int pt_0;  //pt = pontos de testagem do centro 
        int pt_1;
        int pt_2;
		
        

        int max_esp0; // max_esp = máximo da sala de espera para o teste 
        int max_esp1;
        int max_esp2;
		
		int max_iso0; // max_iso = máximo sala isolamento
		int max_iso1;
		int max_iso2;
		
		int max_int0; //max_int = máximo internado
		int max_int1;
		int max_int2;

        int freq_ent_pacientes; //n de pacientes por minuto
		
		int prob_teste_rapido; // probabilidade se usar teste rápido
        int prob_positivo; // probabilidade do teste ser positivo
        int prob_inconclusivo; // probabilidade do teste ser inconclusivo
		
        int tempo_rapido; //tempo que demora teste rápido
        int tempo_normal; // tempo que demora teste normal
};

struct config dados;

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
                if(strcmp(vect,"pt_0") == 0)
                        dados.pt_0 = atoi(n);
                if(strcmp(vect,"pt_1") == 0)
                        dados.pt_1 = atoi(n);
                if(strcmp(vect,"pt_2") == 0)
                        dados.pt_2 = atoi(n);

                if(strcmp(vect,"max_esp0") == 0)
                        dados.max_esp0 = atoi(n);
                if(strcmp(vect,"max_esp1") == 0)
                        dados.max_esp1 = atoi(n);
                if(strcmp(vect,"max_esp2") == 0)
                        dados.max_esp2 = atoi(n);
					
				if(strcmp(vect,"max_iso0") == 0)
                        dados.max_iso0 = atoi(n);
                if(strcmp(vect,"max_iso1") == 0)
                        dados.max_iso1 = atoi(n);
                if(strcmp(vect,"max_iso2") == 0)
                        dados.max_iso2 = atoi(n);
					
				if(strcmp(vect,"max_int0") == 0)
                        dados.max_int0 = atoi(n);
                if(strcmp(vect,"max_int1") == 0)
                        dados.max_int1 = atoi(n);
                if(strcmp(vect,"max_int2") == 0)
                        dados.max_int2 = atoi(n);

                if(strcmp(vect,"freq_ent_pacientes") == 0)
                        dados.freq_ent_pacientes = atoi(n);
                if(strcmp(vect,"prob_teste_rapido") == 0)
                        dados.prob_teste_rapido = atoi(n);
                if(strcmp(vect,"prob_positivo") == 0)
                        dados.prob_positivo = atoi(n);
                if(strcmp(vect,"prob_inconclusivo") == 0)
                        dados.prob_inconclusivo = atoi(n);
                if(strcmp(vect,"tempo_rapido") == 0)
                        dados.tempo_rapido = atoi(n);
                if(strcmp(vect,"tempo_normal") == 0)
                        dados.tempo_normal = atoi(n);
                
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
	
	fprintf(f, "\n--Centro 1--\n");
    printf("\n--Centro 1--\n");
	escreve_aux(f,"Pontos de testagem: ",dados.pt_0);
	escreve_aux(f,"Capacidade máxima sala de espera: ",dados.max_esp0);
	escreve_aux(f,"Capacidade máxima sala de isolamento: ",dados.max_iso0);
	escreve_aux(f,"Capacidade máxima internamento: ",dados.max_int0);
	
	fprintf(f, "\n--Centro 2--\n");
    printf("\n--Centro 2--\n");
	escreve_aux(f,"Pontos de testagem: ",dados.pt_1);
	escreve_aux(f,"Capacidade máxima sala de espera: ",dados.max_esp1);
	escreve_aux(f,"Capacidade máxima sala de isolamento: ",dados.max_iso1);
	escreve_aux(f,"Capacidade máxima internamento: ",dados.max_int1);
	
	fprintf(f, "\n--Centro 3--\n");
    printf("\n--Centro 3--\n");
	escreve_aux(f,"Pontos de testagem: ",dados.pt_2);
	escreve_aux(f,"Capacidade máxima sala de espera: ",dados.max_esp2);
	escreve_aux(f,"Capacidade máxima sala de isolamento: ",dados.max_iso2);
	escreve_aux(f,"Capacidade máxima internamento: ",dados.max_int2);
	
	fprintf(f, "\n--Outros Dados--\n");
    printf("\n--Outros Dados--\n");
	escreve_aux(f,"Número de pacientes por minuto: ",dados.freq_ent_pacientes);
	escreve_aux(f,"Teste Rápido: ",dados.prob_teste_rapido);
	escreve_aux(f,"Teste Positivo: ",dados.prob_positivo);
	escreve_aux(f,"Teste Inconclusivo: ",dados.prob_inconclusivo);
	escreve_aux(f,"Tempo de espera resultado rápido: ",dados.tempo_rapido);
	escreve_aux(f,"Tempo de espera resultado normal: ",dados.tempo_normal);
	
	fclose(f);
}

int main(){
	carrega_config();
	escreve_log();
	printf("\n--CONCLUIDO--\n");
	return 0;
}
