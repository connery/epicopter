/*
** serveur_accept.c for my_irc in /home/croux_g//local/system_unix/IRC/serveur
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Mon Apr 16 16:27:36 2012 geoffrey croux
** Last update Sun Apr 22 22:28:54 2012 geoffrey croux
*/

#include "serveur.h"

int	serveur_control(list * p, fd_set * n)
{
  FD_ZERO(n);

  for (; p ; p = p->next)
    {
      FD_SET(p->client_fd, n);
    }

  return (EXIT_SUCCESS);
}

int	serveur_old(int m, list * p)
{
  int	fd;

  for (fd = m; p; p = p->next)
    {
      if (p->client_fd > fd)
	fd = p->client_fd;
    }

  return (fd + 1);
}

list	* serveur_nickname_exist(char * nickname, list * p)
{
  for (; p ; p = p->next)
    {
      if (p->client_nickname != 0)
	{
	  if ((strcmp(p->client_nickname, nickname)) == 0)
	    return (p);
	}
    }
  
  return (list *)(0);
}

list	* serveur_do_client(list ** p, channel_list ** c, fd_set * readfds, fd_set * writefds)
{
  list	* begin = (*p);

  for((*p) = begin; (*p); (*p) = (*p)->next)
    {
      if (FD_ISSET((*p)->client_fd, readfds))
      	{
      	  rcv_client((*p), (*p)->client_fd, 0);

      	  if ((*p) && (*p)->message_len == 0)
      	    {
      	      printf("SUCCESS: Deconnexion d'un client\n");
      	      (*p) = serveur_del_client(begin, (*p)->client_fd);

      	      return (*p);
      	    }
	  
	  if ((*p)->message != 0)
	    {
	      write(1, "SUCCESS: RECEPTION DE LA COMMANDE: ", 35);
	      write(1, (*p)->message, (*p)->message_len);
	      write(1, "\n", 1);

	      // Ecriture sur pipe d'entree arduino
	      write(dest, (*p)->message, (*p)->message_len);
	    }

      	  serveur_interpreter(begin, p, c, writefds);
      	}
    }

  return (begin);
}

list	* serveur_del_client(list * p, int client)
{
  list	* begin = p;

  if (p && p->client_fd == client)
    {
      close(client);
      return (p->next);
    }

  for (;p && p->next; p = p->next)
    {
      if (p->next->client_fd == client)
      	{
      	  close(client);     
      	  p->next = p->next->next;
	  
   	  return (begin);
      	}
    }

  return (list *)(EXIT_FAILURE);
}

channel_list	* serveur_add_channel(channel_list * c)
{
  channel_list	* new;

  if ((new = malloc(sizeof(channel_list))) == (channel_list *)(-1))
    {
      write(2, "malloc failure.\n", strlen("malloc failure.\n"));
      exit(0);
    }
  
  new->next = c;
  new->channel = 0;

  return (new);
}

list	* serveur_add_client(list * p, int client)
{
  list	* new;

  if ((new = malloc(sizeof(list))) == (list *)(-1))
    {
      write(2, "malloc failure.\n", strlen("malloc failure.\n"));
      exit(0);
    }

  new->next = p;

  new->client_nickname	= 0;
  new->client_receiver	= 0;
  new->channel		= 0;
  
  memset(new->message, '0', BUFFER_SIZE);

  new->message_len	= 0;
  new->client_fd	= client;

  return (new);
}

int	serveur_accept(int fd)
{
  struct sockaddr_in	sin_client;
  int	client_len = sizeof(sin_client), client;
  fd_set	readfds, writefds;
  list	* p = 0;

  channel_list * c = 0;

  list	* begin;
  int	w;

  while (1)
    {
      FD_ZERO(&readfds);

      serveur_control(p, &readfds);
      FD_SET(fd, &readfds);
      
      serveur_control(p, &writefds);


      /* for (w = 0, begin = p; begin; begin = begin->next) */
      /* 	{ */
      /* 	  if (begin && begin->message_len != 0 && w == 0) */
      /* 	    { */
      /* 	      w = 1; */
      /* 	    } */
      /* 	} */

     

      /* if (w != 0) */
      /* 	{ */
      /* 	  if ((select(serveur_old(fd, p), &readfds, &writefds, NULL, NULL)) == (-1)) */
      /* 	    return (EXIT_FAILURE); */
      /* 	} */
      /* else */
      /* 	{ */
      if ((select(serveur_old(fd, p), &readfds, NULL, NULL, NULL)) == (-1))
	return (EXIT_FAILURE);
	/* } */

      if (FD_ISSET(fd, &readfds))
	{
	  if ((client = accept(fd, (struct sockaddr *)&sin_client, (socklen_t *)&client_len)) == -1)
	    {
	      for (write(2, ERROR_04, strlen(ERROR_04)), close (fd); 0; ) ;
	    }
	  else
	    {
	      printf("SUCCESS: Connexion d'un client\n");
	      p = serveur_add_client(p, client);
	    }
	}

      p = serveur_do_client(&p, &c, &readfds, &writefds);
    }
  
  return (EXIT_SUCCESS);
}


list	* rcv_client(list * p, int client_01, int client_02)
{
  (void) client_01;
  (void) client_02;

  if ((p->message_len = read(client_01, p->message, BUFFER_SIZE)) == -1)
    {
      return (list *)(EXIT_FAILURE);
    }

  return (p);
}

list	* send_client(list * p, int client_01, int client_02, char * res)
{
  (void) client_01;
  (void) client_02;

  if (res == (char *)(0) && p->message != 0 && p->message_len != 0)
    {
      write(client_02, p->message, p->message_len);
    }
  else if (res != (char *)(0) && strlen(res) > 0)
    {
      write(client_02, res, strlen(res));
    }

  return (p);
}
