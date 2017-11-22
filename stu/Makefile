CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lsqlite3
OBJS= add.cgi del.cgi mod.cgi sel.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)	

.PHONY:clean
clean:
	rm ./*.cgi


