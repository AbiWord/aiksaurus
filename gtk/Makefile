CC=g++
GTKLINK=`gtk-config --libs` `gtk-config --cflags`
CPPFLAGS=-Wall -ansi

all: gtkAiksaur
	
gtkAiksaur: gtkAiksaur.t.cpp gtkAiksaur.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -o gtkAiksaur gtkAiksaur.t.cpp gtkAiksaur.o

gtkAiksaur.o : gtkAiksaur.cpp gtkAiksaur.h
	$(CC) $(CPPFLAGS) $(GTKLINK) -c gtkAiksaur.cpp

clean:
	rm gtkAiksaur *.o *~


