#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "client.h"

// Fonction de creation de paquet
// Param : les datas que l'on veut envoyer

Packet      *createPacket(char * buffer) {
  Packet    *p;
  
  p = malloc(sizeof(Packet));
		      
  p->header.is_data = 1;
  p->header.fragment = 0;
  p->header.last = 0;
  p->header.datalen = strlen(buffer) + sizeof(Packet);
  strncpy(p->data, buffer, strlen(buffer));
  return p;
}

// Fonction principale du client avec la boucle d'ecoute
// Params : addresse IP du serveur, nom du client

static void app(const char *address, const char *name)
{
  SOCKET sock = init_connection(address);
  char buffer[BUF_SIZE];

  fd_set rdfs;
  Packet *pa;

  pa = malloc(PACKET_SIZE);

  strncpy(pa->data, name, strlen(name));

  // Envoi d'un premier paquet de connexion au serveur avec le nom du client en data
  write_server(sock, pa);

  while(1)
    {
      pa = malloc(PACKET_SIZE);

      FD_ZERO(&rdfs);
      FD_SET(STDIN_FILENO, &rdfs);
      FD_SET(sock, &rdfs);

      if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
	{
	  perror("select()");
	  exit(errno);
	}

      if(FD_ISSET(STDIN_FILENO, &rdfs))
	{
	  fgets(buffer, BUF_SIZE - 1, stdin);
	  {
            char *p = NULL;
            p = strstr(buffer, "\n");
            if(p != NULL)
	      *p = 0;
            else
	      buffer[BUF_SIZE - 1] = 0;
	  }

	  pa = createPacket(buffer);

	  printf("data = %s/n", pa->data);
	      
	  write_server(sock, pa);
	}
      else if(FD_ISSET(sock, &rdfs))
	{
	  int n = read_server(sock, pa);

	  if(n == 0)
	    {
	      printf("Server disconnected !\n");
	      break;
	    }
	}
    }
  end_connection(sock);
}

// Fonction d'initialisation de la connexion
// Param : addresse IP du serveur

static int init_connection(const char *address)
{
  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
  SOCKADDR_IN sin = { 0 };
  struct hostent *hostinfo;

  if(sock == INVALID_SOCKET)
    {
      perror("socket()");
      exit(errno);
    }

  hostinfo = gethostbyname(address);
  if (hostinfo == NULL)
    {
      fprintf (stderr, "Unknown host %s.\n", address);
      exit(EXIT_FAILURE);
    }

  sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
  sin.sin_port = htons(PORT);
  sin.sin_family = AF_INET;

  if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
      perror("connect()");
      exit(errno);
    }

  return sock;
}

// Fonction de cloture de socket
// Param : la socket qui doit etre fermee

static void end_connection(int sock)
{
  closesocket(sock);
}

// Fonction de lecture
// Params : SOCKET du client et un Packet vierge pour recuperer les datas

static int read_server(SOCKET sock, Packet *p)
{
  int n = 0;

  if((n = recv(sock, p, PACKET_SIZE, 0)) < 0)
    {
      perror("recv()");
      exit(errno);
    }

  printf("rcv %s\n", p->data);
  return n;
}

// Fonction d'ecriture
// Params : SOCKET du client et le Packet contenant les informations a envoyer

static void write_server(SOCKET sock, const Packet *p)
{
  if(send(sock, p, PACKET_SIZE, 0) < 0)
    {
      perror("send()");
      exit(errno);
    }
}

// Main
// Params d'entree : Adresse IP du serveur et nom du client (pour les tests)

int main(int argc, char **argv)
{
  if(argc < 2)
    {
      printf("Usage : %s [address] [pseudo]\n", argv[0]);
      return EXIT_FAILURE;
    }

  app(argv[1], argv[2]);

  return EXIT_SUCCESS;
}
