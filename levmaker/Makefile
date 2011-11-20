
OBJS= main.o 

CFLAGS=-Wall -O2 -I/usr/include/mingw
LDFLAGS=-L/usr/lib 
PROGNAME=levmaker

all: $(OBJS)
	gcc  $(OBJS) -o $(PROGNAME)  $(LDFLAGS) 

clean: 
	rm -f *.o *~ *.bak $(PROGNAME)*
