##
## Makefile for my_irc in /home/croux_g//local/system_unix/IRC
## 
## Made by geoffrey croux
## Login   <croux_g@epitech.net>
## 
## Started on  Mon Apr 16 16:13:36 2012 geoffrey croux
## Last update Sun Apr 22 22:34:42 2012 geoffrey croux
##

CLIENT_NAME	=		client

SERVEUR_NAME	=		serveur


CLIENT_SRC	=		client.c \
				client_connect.c \
				client_loop.c \
				client_parsCommand.c \
				client_sendAndReceiveServer.c \
				client_socket.c


SERVEUR_SRC	=		serveur.c \
				serveur_socket.c \
				serveur_bind.c \
				serveur_listen.c \
				serveur_accept.c \
				serveur_interpreter.c \
				serveur_cmd_nick.c \
				serveur_cmd_list.c \
				serveur_cmd_join.c \
				serveur_cmd_users.c \
				serveur_cmd_msg.c \
				serveur_cmd_msg_all.c \
				serveur_cmd_file.c


CLIENT_OBJ	=		$(CLIENT_SRC:.c=.o)

SERVEUR_OBJ	=		$(SERVEUR_SRC:.c=.o)

CC		=		gcc

CFLAGS		=		-W -Wall -Wextra

AUTEUR		=		echo > auteur "croux_g;crusem_m"

all		:		$(SERVEUR_NAME) $(CLIENT_NAME)
				$(AUTEUR)

$(CLIENT_NAME)	:		$(CLIENT_OBJ)
				$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJ) $(CFLAGS)

$(SERVEUR_NAME)	:		$(SERVEUR_OBJ)
				$(CC) -o $(SERVEUR_NAME) $(SERVEUR_OBJ) $(CFLAGS)

clean		:		
				rm -f *~
				rm -f *.o

fclean		:		clean
				rm -f $(SERVEUR_NAME) $(CLIENT_NAME)

re		:		fclean all
