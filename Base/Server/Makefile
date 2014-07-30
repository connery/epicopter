CC = gcc

CFLAGS = 

INCLUDES = -I/usr/include/postgresql

LFLAGS = -L/usr/lib 

LIBS = -lpq `mysql_config --cflags --libs` -lpthread

SRCS = utils.c network.c msql_manager.c pgsql_manager.c server.c 

OBJS = $(SRCS:.c=.o)

MAIN = ServerCopter

.PHONY: depend clean

all:    $(MAIN)
	@echo  ServerCopter has been compiled

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

