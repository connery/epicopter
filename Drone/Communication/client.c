#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "client.h"

// Fonction de creation de paquet
// Param : les datas que l'on veut envoyer

Packet      *createPacket(char * buffer, OPcode op, const char *name) {
  Packet    *p;
  
  p = malloc(sizeof(Packet));
		      
  p->header.opcode = op;
  p->header.ID = 1;
  p->header.datalen = strlen(buffer);
  strncpy(p->data, buffer, strlen(buffer));
  strncpy(p->header.name, name, strlen(name));
  return p;
}

static void initializeConnection(Packet *pa, SOCKET sock, const char* name) {
  printf("--- Asking for connection ---\n");
  pa->header.opcode = CON;
  pa->header.ID = 1;
  pa->header.datalen = strlen(name);
  strncpy(pa->data, name, strlen(name));
  strncpy(pa->header.name, name, strlen(name));
  write_server(sock, pa);
}


// Fonction principale du client avec la boucle d'ecoute
// Params : addresse IP du serveur, nom du client


static void app(const char *address, const char *name, const int manage_filedescriptor)
{
  SOCKET sock = init_connection(address);
  char buffer[BUF_SIZE];

  fd_set rdfs;
  Packet *pa;

  pa = malloc(PACKET_SIZE);

  initializeConnection(pa, sock, name);

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

	}
      else if(FD_ISSET(sock, &rdfs))
	{
	  char buffer[BUF_SIZE];

	  int n = read_server(sock, &buffer);
	 
	  if (strncmp(buffer, "CON", 3) == 0)
	    {
	      printf("--- Connection accepted ---\n");


	      //write(manage_filedescriptor, "X#", 2); // TEST


	      //pa = createPacket("", DEC, name);
	      //printf("--- Asking for deconnection ---\n");
	      //write_server(sock, pa);

	      while(1) {}
	    }

	  /* if (pa->header.opcode == CON) { */
	  /*   printf("--- Connection accepted ---\n"); */
	  /*   pa = createPacket("", DEC, name); */
	  /*   printf("--- Asking for deconnection ---\n"); */
	  /*   write_server(sock, pa); */
	  /* } */
	  /* else if (pa->header.opcode == DEC) { */
	  /*   printf("--- Disconnection accepted ---\n"); */
	  /*   end_connection(sock); */
	  /*   printf("--- Quitting ---\n"); */
	  /*   exit(EXIT_SUCCESS); */
	  /* } */




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

static int read_server(SOCKET sock, char ** buffer)
{
  //char  buffer[SIZE_BUFFER];
  int   size;

  memset(buffer, 0, sizeof(buffer));
  size = recv(sock, buffer, BUF_SIZE, 0);
  
  if (size < 0)
    {
      perror("recv()");
      exit(errno);
    }
  
  /* if((n = recv(sock, p, PACKET_SIZE, 0)) < 0) */
  /*   { */
  /*     perror("recv()"); */
  /*     exit(errno); */
  /*   } */


  return size;
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
  if (argc < 2)
    {
      printf("Usage : %s [address] [pseudo]\n", argv[0]);
      return EXIT_FAILURE;
    }

  if (argc < 4)
    {
      app(argv[1], argv[2], 0);
    }
  else
    {
      app(argv[1], argv[2], atoi(argv[3]));
    }

  return EXIT_SUCCESS;
}
