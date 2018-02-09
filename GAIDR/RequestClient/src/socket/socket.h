#ifndef SRC_SOCKET_SOCKET_H_
#define SRC_SOCKET_SOCKET_H_

#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>

#include "../struct/structs.h"
#include "../utils/stringOper.h"
#include "../variables/variables.h"

void send(string ip,RequestInfo request,string pattern);

void reqEOF();

RequestInfo recevice(string pattern);

#endif
