#include "library.h"

int main (int argc, char *argv[]){
    /*int e =  exporta();
    if(e == -1){
        printf("Erro na Exportacao");
    }
    else if (e ==1){
        printf("Sucesso na Exportacao");
    }*/
    return 1;
}

FILE* log = fopen("monitor.log","a");
fprintf(log, "%s \n","TESTE");
int utilizadores = 203;
int positivos = 18;
int estudo = 11;
int tempo_m = 13;
fprintf(log,"Utilizadores:%d \n",utilizadores);
fprintf(log,"Casos positivos: %d \n",positivos);
fprintf(log,"Casos em estudo: %d \n",estudo );
fprintf(log,"Tempo medio de espera:%d \n",tempo_m);
fclose(log);

/*int exporta(){
   int fd = open("monitor.log",O_WRONLY |O_CREAT , S_IRUSR | S_IWUSR);
    if (fd == 0){
        return -1; //erro de exportação
    }
    else{
        dup2(fd,1);
        int utilizadores = 203;
        int positivos = 18;
        int estudo = 11;
        int tempo_m = 13;
        printf("Utilizadores:%d \n",utilizadores);
        printf("Casos positivos: %d \n",positivos);
        printf("Casos em estudo: %d \n",estudo );
        printf("Tempo medio de espera:%d \n",tempo_m);
        dup2(1,fd);
        close(fd);
        return 1; //sucesso na exportação
    }
}*/