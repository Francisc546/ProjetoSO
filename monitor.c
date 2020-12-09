#include "library.h"

int main (int argc, char *argv[]){
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

/* Novo para a 2ª Entrega Comunicação do servidor (feito por socket stream) código tirado dos sockets ficheiro "unix-stream-server.c" */

void socket_cliente(){
    int sockfd, newsockfd, clilen, childpid, servlen;
    struct sockaddr_un cli_addr, serv_addr;

    /* Cria socket stream */

    if ((sockfd = socket (AF_UNIX, SOCK_STREAM,0)) < 0)
        err_dump("server: can't open stream socket");
    
    /*Primeiro uma limpeza preventiva! 
      Dados para o socket stream: tipo + nome do ficheiro.
    O ficheiro serve para que os clientes possam identificar o servidor */

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, UNIXSTR_PATH):

    /* O server é quem cria o ficheiro que identifica o socket.
       Elimina o ficheiro, para o caso de algo ter ficado pendurado.
       Em seguida associa o socket ao ficheiro.
       A dimensão a indicar ao bind não é a da estrutura, pois depende
       do nome do ficheiro */

    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
    unlink(UNIXSTR_PATH);
    if(bind(sockfd, (struct sockaddr *) &serv_addr, servlen ) < 0)
        err_dump("server, can't bind local address");
    
    /* Servidor pronto a aceitar 5 clientes para o socket stream */
    
    listen(sockfd, 5);

    for(;;){
        /* Não esquecer que quando o  serviddor aceita um cliente cria ui
           socket para comunicar com ele. O primeiro scoket (sockfd) fica
           à espera de mais clientes. */
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if(newsockfd <0)
            err_dump("server: accept error");
        
        /* Lança processo filho para lidar com o cliente */
        
        if((childpid = fork() ) < 0)
            err_dump("server: fork error");
        else if (childpid == 0){
            /* Processo filho que vai atender o cliente.
               Fechar sockfd é sanitário, já que não é
               utilizado pelo processo filho.
               Os dados recebidos do cliente são reenviados
               para o cliente */
            
            close(sockfd);
            str_echo(newsockfd);
            exit(0);
        }
        
        /* Processo pai.
           Fechar newsockfd é sanitário, já que não é
           utilizado pelo processo pai*/
        close(newsockfd);

    }
}