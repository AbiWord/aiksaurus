CC=g++
GTKLINK=`gtk-config --libs` `gtk-config --cflags`
CPPFLAGS=-Wall -ansi

all: gtkAiksaur

gtkAiksaur: gtkAiksaur.t.cpp AiksaurusGTK_strlist.o \
            AiksaurusGTK_histlist.o AiksaurusGTK_utils.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -o gtkAiksaur \
            gtkAiksaur.t.cpp gtkAiksaur.o AiksaurusGTK_strlist.o \
	    AiksaurusGTK_histlist.o AiksaurusGTK_utils.o -lAikSaurus

gtkAiksaur.o : gtkAiksaur.cpp gtkAiksaur.h AiksaurusGTK_strlist.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -c gtkAiksaur.cpp

AiksaurusGTK_strlist.o : AiksaurusGTK_strlist.cpp AiksaurusGTK_strlist.h AiksaurusGTK_utils.h
	$(CC) $(CPPFLAGS) $(GTKLINK) -c AiksaurusGTK_strlist.cpp

AiksaurusGTK_histlist.o : AiksaurusGTK_histlist.cpp AiksaurusGTK_histlist.h AiksaurusGTK_strlist.h
	$(CC) $(CPPFLAGS) $(GTKLINK) -c AiksaurusGTK_histlist.cpp

histlist.test : histlist.test.cpp AiksaurusGTK_histlist.o AiksaurusGTK_strlist.o AiksaurusGTK_utils.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -o histlist.test histlist.test.cpp AiksaurusGTK_histlist.o AiksaurusGTK_strlist.o AiksaurusGTK_utils.o

strlist.test : strlist.test.cpp AiksaurusGTK_strlist.o AiksaurusGTK_utils.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -o strlist.test strlist.test.cpp AiksaurusGTK_utils.o AiksaurusGTK_strlist.o 

strlist.test2 : strlist.test2.cpp AiksaurusGTK_strlist.o AiksaurusGTK_utils.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -o strlist.test2 strlist.test2.cpp AiksaurusGTK_utils.o AiksaurusGTK_strlist.o 

AiksaurusGTK_utils.o : AiksaurusGTK_utils.h AiksaurusGTK_utils.cpp
	$(CC) $(CPPFLAGS) -c AiksaurusGTK_utils.cpp 

clean:
	rm gtkAiksaur *.o *~


