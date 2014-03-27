#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server.h"

void getPacket(Packet *p, SOCKET s) {
  Packet *pa;

  pa = malloc(sizeof(PACKET_SIZE));
  
  if (p->header.opcode == CON) {
    printf("--- Client asking for connection ---\n");
    
    pa->header.opcode = CON;
    pa->header.ID = 0;
    pa->header.datalen = strlen("opbase");
    strncpy(pa->data, "opbase", strlen("opbase"));
    strncpy(pa->header.name, "opbase", strlen("opbase"));
    write_client(s, pa);

    printf("--- Sending acknowledgement ---\n");
  }
  else if (p->header.opcode == DEC) {
    printf("--- Client asking for deconnection ---\n");
    
    pa->header.opcode = DEC;
    pa->header.ID = 0;
    pa->header.datalen = strlen("opbase");
    strncpy(pa->data, "opbase", strlen("opbase"));
    strncpy(pa->header.name, "opbase", strlen("opbase"));
    write_client(s, pa);

    printf("--- Sending acknowledgement ---\n");
  }    
    
}


static int readClient(Client* clients, int i, Packet *p) {
  Client client = clients[i];

  p = malloc(PACKET_SIZE);
  int c = read_client(clients[i].sock, p);

  if (c == 0)
    return 1;

  getPacket(p, clients[i].sock);
  return 0;
}

static void app(void)
{
  SOCKET sock = init_connection();

  char buffer[BUF_SIZE];
  int actual = 0;
  int max = sock;
  Packet *p;
  Client clients[MAX_CLIENTS];

  fd_set rdfs;

  while(1)
    {
      int i = 0;
      p = malloc(PACKET_SIZE);

      FD_ZERO(&rdfs);
      FD_SET(STDIN_FILENO, &rdfs);
      FD_SET(sock, &rdfs);

      for(i = 0; i < actual; i++)
	  FD_SET(clients[i].sock, &rdfs);

      if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
	{
	  perror("select()");
	  exit(errno);
	}

      if (FD_ISSET(STDIN_FILENO, &rdfs))
	  break;
      
      else if(FD_ISSET(sock, &rdfs))
	{

	  SOCKADDR_IN csin = { 0 };
	  socklen_t sinsize = sizeof csin;
	  int csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
	  if(csock == SOCKET_ERROR)
	    {
	      perror("accept()");
	      continue;
	    }

	  if (read_client(csock, p) == -1)
	      continue;

	  max = csock > max ? csock : max;

	  FD_SET(csock, &rdfs);

	  Client c = { csock };
	  strncpy(c.name, buffer, BUF_SIZE - 1);
	  clients[actual] = c;

	  getPacket(p, c.sock);

	  actual++;
	}
      else
	{
	  int i = 0;

	  for(i = 0; i < actual; i++)
	    {
	      if (FD_ISSET(clients[i].sock, &rdfs))
		{
		  if (readClient(clients, i, p) == 1) {
		    closesocket(clients[i].sock);
		    remove_client(clients, i, &actual);
		  }
		  break;
		  
		}
	    }
	}
    }

  clear_clients(clients, actual);
  end_connection(sock);
}

static void clear_clients(Client *clients, int actual) {
  int i = 0;

  for (i = 0; i < actual; i++) 
		  closesocket(clients[i].sock);
}

static void remove_client(Client *clients, int to_remove, int *actual)
{
  /* we remove the client in the array */
  memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(Client));
  /* number client - 1 */
  (*actual)--;
}

static int init_connection(void)
{
  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
  SOCKADDR_IN sin = { 0 };

  if(sock == INVALID_SOCKET)
    {
      perror("socket()");
      exit(errno);
    }

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(PORT);
  sin.sin_family = AF_INET;

  if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
    {
      perror("bind()");
      exit(errno);
    }

  if(listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
    {
      perror("listen()");
      exit(errno);
    }

  return sock;
}

static void end_connection(int sock)
{
  closesocket(sock);
}

static int read_client(SOCKET sock, Packet *p)
{
  int n = 0;

  if((n = recv(sock, p, PACKET_SIZE, 0)) < 0)
    {
      perror("recv()");
      n = 0;
    }
  return n;
}

static void write_client(SOCKET sock, const Packet *p)
{
  if(send(sock, p, PACKET_SIZE, 0) < 0)
    {
      perror("send()");
      exit(errno);
    }
}

int main(int argc, char **argv)
{
  app();

   return EXIT_SUCCESS;
}
