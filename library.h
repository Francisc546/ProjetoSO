#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>

void socketCliente();
void socketServidor();

#define UNIXSTR_PATH "/tmp/so20212044718"
#define UNIXDG_PATH "/tmp/s.unixdfddffdfdgx"
#define UNIXDG_TMP "/tmp/dgXXXXXfdjhfdjhfdXX"