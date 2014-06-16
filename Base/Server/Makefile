CC=gcc
CFLAGS= 
RM=/bin/rm
MAKE=/usr/bin/make
MAKEDEPEND=/usr/X11R6/bin/makedepend

SRC= 	server.c \
	network.c

OBJ=$(subst .c,.o,$(SRC))

SUBDIR= .

.SUFFIXES: .c
.c.o:
	$(CC) -c $(CFLAGS) $<
all:
	for i in $(SUBDIRS); do (cd $$i; $(MAKE) all); done
	$(MAKE) serverCopter

serverCopter: $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $^

clean:
	$(RM) -f $(OBJ) core *~
	for i in $(SUBDIRS); do (cd $$i; $(MAKE) clean); done

depend:
	$(MAKEDEPEND) -- $(CFLAGS) -- $(SRC)
