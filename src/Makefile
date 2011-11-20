
OBJS=	animated.o bgunfire.o bonus.o common.o construc.o enemy.o gunfire.o \
	imglist.o level.o levitem.o main.o pixmap.o player.o sprite.o \
	explosion.o gameloop.o fssystem.o animation.o

CXX=g++
IRRLICHT_DIR=C:/pastas/devEnv/irrlicht-1.4
CPPFLAGS=-g -Wall -O2 $$(glib-config --cflags) -I$(IRRLICHT_DIR)/include
LDFLAGS=$$(glib-config --libs) -L$(IRRLICHT_DIR)/lib/Win32-gcc -lIrrlicht
PROGNAME=../bin/fastship

all: $(OBJS)
	g++  $(OBJS) -o $(PROGNAME)  $(LDFLAGS) 

clean: 
	rm -f *.o *~ *.bak $(PROGNAME).exe
	
purge: clean 
	rm -f $(PROGNAME).exe
	
