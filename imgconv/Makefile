
OBJS= main.o 

CFLAGS=-Wall -O2 -I/usr/include/mingw
LDGLIB=-lglib-1.3 -lgthread-1.3 -liconv-1.3 -lgmodule-1.3 
LDALLEGRO=-s -mno-cygwin -mwindows -lalleg
LDFLAGS=-L/usr/lib $(LDGLIB) $(LDALLEGRO)
PROGNAME=imgconv

all: $(OBJS)
	gcc  $(OBJS) -o $(PROGNAME)  $(LDFLAGS) 

clean: 
	rm -f *.o *~ *.bak
