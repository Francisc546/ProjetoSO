#include "library.h"

int main (int argc, char *argv[]){
    socket_cliente();
    int e =  exporta();
    if(e == -1){
        printf("Erro na Exportacao");
    }
    else if (e ==1){
        printf("Sucesso na Exportacao");
    }
    return 1;
}

int exporta(){
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
}

/* Novo para a 2ª Entrega Comunicação do cliente (feito por socket stream) código tirado dos sockets ficheiro "unix-stream-client.c" */

void socket_cliente(){
        int sockfd, servlen;
        struct sockaddr_un serv_addr;

        /*Cria socket stream */

        if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) <0 )
                err_dump("client: can't open stream socket");

        /* Primeiro uma limpeza preventiva!
           Dados para o socket stream: tipo + nome do ficheiro.
           O fichiero identifica o servidor */
        
        bzero((char*) &serv_addr, sizeof(serv_addr));
        serv_addr.sun_family = AF_UNIX;
        strcpy(serv_addr.sun_path, UNIXSTR_PATH);
        servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);

        /* Tenta estabelecer uma ligação, 
           sido lançado primeiro (o servidor tem de criar o ficheiro e associar
           o socket ao ficheiro) */
        
        if(connect(sockfd, (struct sockaddr *) &serv_addr, servlen) < 0)
                err_dump("client: can't connect to server");
        
        /* Envia as linhas do teclado para o socket */

        str_cli(stdin, sockfd);

        /* Fecha o socket e termina */

        close(sockfd);
        exit(0);
}

