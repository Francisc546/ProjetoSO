#include "library.h"
#define MAXLINE 512

/* Servidos do tipo socket stream.
    Manda linhas recebidas de volta para o cliente */

str_echo(sockfd)
int sockfd;
{
    int n, i;
    char line[MAXLINE];

    for(;;){
        /* Lê uma linha do socket */
        n = readline(sockfd, line, MAXLINE);
        if (n == 0){
            return;
        }
        else if (n < 0){
            err_dump("str_echo: readline error");
        }
/* 
    Aqui o nosso trabalho
*/
        for(i = 0; i <n-1; i++){
            line[i] = line[i] +1;
        }
        /*Manda linha de volta para o socket, n conta com o \0 da string, caso contrário perdia-se sempre um caracter! */
        if(written(sockfd, line, n) != n){
            err_dump("str_ercho: writen error");
        }
    }
}
