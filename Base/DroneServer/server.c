#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

#define BUFFER_SIZE 8192
#define BUFLEN 10240
#define PORT 9930


void err(char *str)
{
  perror(str);
  exit(1);
}

int main(void)
{
  struct sockaddr_in my_addr, cli_addr;
  int sockfd, i;
  socklen_t slen=sizeof(cli_addr);
  char buf[BUFLEN];
 
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    err("socket");
  else
    printf("Server : Socket() successful\n");
 
  bzero(&my_addr, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(PORT);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
     
  if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)
    err("bind");
  else
    printf("Server : bind() successful\n");

  node *head;
  int singleton = 0;
  Packet tmp;
  unsigned char buffer[BUFFER_SIZE];
  int j, k, count;
  int local_datalen;
  int nbPacket = 0;
  FILE *image;
  int retRecv;
  
  singleton = 1;

  head = malloc(sizeof(node));
  if (head == NULL) {
    exit(EXIT_FAILURE);
  }

  head->p.ID = 1;
  head->next = NULL;

  Packet pa;
  pa.ID = 2;
  add_end(head, pa);
  pa.ID = 3;
  add_end(head, pa);
  show(head);

  //  node * test = generateListFromImage("image.jpg");
  while(1)
    {    


      if (recvfrom(sockfd, &tmp, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen)==-1) 
	err("recvfrom()");
      else if (tmp.code == WAIT && singleton == 1) {
	printf("Wait arrived %i\n", tmp.code);
	tmp.nbckp = count_item(head);
	if (sendto(sockfd, &tmp, BUFLEN, 0, (struct sockaddr *)&cli_addr, slen)==-1) {
	  err("sendto()");
	}
	else {
	  printf("Wait received\n");
	  singleton = 0;
	}
      }      
      else if (singleton == 0) {
	node *current = head;
	while (current != NULL) {
	  printf("Packet ID sent => %i\n", current->p.ID);
	  if (sendto(sockfd, &current->p, BUFLEN, 0, (struct sockaddr *)&cli_addr, slen)==-1) {
	    err("sendto()");
	  }
	  current = current->next;
	}
	singleton = 2;
      }
      else if (tmp.code == MED) {
	printf("MED received\n");
	printf("ID packet %i\nDatalen %i\n", tmp.ID, tmp.datalen);
	
	if (tmp.ID == 0 ) {
	  printf("MED packet no 0 received\n");
	  local_datalen = tmp.datalen;
	  image = fopen("image.jpg", "wb+");
	  fseek(image, count, SEEK_SET);
	  printf("Local datalen %i\n", local_datalen);

	  Packet ret;
	 
	  ret.code = OK;
	  
	  if (sendto(sockfd, &ret, BUFLEN, 0, (struct sockaddr *)&cli_addr, slen)==-1) {
	    err("sendto()");
	  }
	  else
	    printf("OK packet sent\n\n");

	  if (!image)
	    printf("Error on image opening\n");
	  else {
	    count = 0;
	    nbPacket = 0;
	  }
	}
	else if (tmp.ID > 0) {
	  printf("MED for writing\n");
	  fwrite(tmp.data, 1, BUFFER_SIZE, image);
	  printf("%i bytes read from image\n", tmp.datalen);
	  count += tmp.datalen;
	  nbPacket++;
	  
	  printf("Current datalen = %i\n", count);

	  Packet ret;
	 
	  ret.code = OK;
	  
	  if (sendto(sockfd, &ret, BUFLEN, 0, (struct sockaddr *)&cli_addr, slen)==-1) {
	    err("sendto()");
	  }
	  else 
	    printf("OK packet sent\n\n");

	  if (count == local_datalen &&
	      local_datalen > 0) {
	    printf("End writing\n");
	    
	    fclose(image);
	    local_datalen = 0;
	    count = 0;
	    nbPacket = 0;
	    
	    struct stat st;
	    stat("image.jpg", &st);
	    printf("Image size at end %i\n", st.st_size);
	    
	  }

	}
	else
	  printf("Nothing\n");
      }
    }
 
  close(sockfd);
  return 0;
}
