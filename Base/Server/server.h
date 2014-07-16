#ifndef SERVER_H
#define SERVER_H

#ifdef WIN32

#include <winsock2.h>

#elif defined (linux)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */


#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else

#error not defined for this platform

#endif

#define PORT 48888
#define MAX_CLIENTS 100

#define BUF_SIZE 1024

#include "client.h"
#include "checkpoint.h"
#include "flightplan.h"
#include "network.h"
#include "msql_manager.h"
#include "pgsql_manager.h"

static void run(void);

#endif /* guard */
