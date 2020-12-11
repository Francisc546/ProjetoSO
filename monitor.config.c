
#include <stdio.h>
#include "library.h"
#define MAXLINE 512

/*Cliente do tipo socket stream
    Lê string de fp e envia para sockfd
    Lê string de sockfd e envia para stdout*/

str_cli(fp,sockfd)
FILE *fp;
int sockfd;
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE+1];
    
    while(fgets(sendline, MAXLINE, fp) != NULL){
/* 
    Aqui o nosso trabalho 
*/
    /* Envia string para sockfd, Note-se que o \0 não é enviado */
        n = strlen(sendline);
        if(written(sockfd, sendline, n) != n)
            err_dump("str_cli: writen error on socket");
        /* Tenta ler string do sockfd. Note-se que tem de terminar a string com \0*/
        n = readline(sockfd, recvline, MAXLINE);
        if (n<0)
            err_dump("str_cli:readline error");
        recvline[n] = 0;
        /* Envia string para stdout */
        fputs(recvline, stdout);
    }
    if(ferror(fp))
        err_dump("str_cli: error reading file");
}