CC=g++
GTKLINK=`gtk-config --libs` `gtk-config --cflags`
CPPFLAGS=-Wall -ansi -ggdb2

TESTS = test.histlist test.strlist test.strlist2 \
        test.picbutton test.utils test.history test.searchbar


all: gtkAiksaur tests

tests: $(TESTS)

gtkAiksaur2: gtkAiksaur.t2.cpp AiksaurusGTK_strlist.o AiksaurusGTK.o \
            AiksaurusGTK_histlist.o AiksaurusGTK_history.o AiksaurusGTK_utils.o \
	    AiksaurusGTK_picbutton.o AiksaurusGTK_icons.o 
	$(CC) $(CPPFLAGS) $(GTKLINK) -o gtkAiksaur2 \
            gtkAiksaur.t2.cpp AiksaurusGTK.o AiksaurusGTK_strlist.o \
	    AiksaurusGTK_histlist.o AiksaurusGTK_utils.o AiksaurusGTK_picbutton.o \
	    AiksaurusGTK_history.o AiksaurusGTK_icons.o -lAikSaurus

gtkAiksaur: gtkAiksaur.t.cpp AiksaurusGTK_strlist.o AiksaurusGTK.o \
            AiksaurusGTK_histlist.o AiksaurusGTK_history.o AiksaurusGTK_utils.o \
	    AiksaurusGTK_picbutton.o AiksaurusGTK_icons.o 
	$(CC) $(CPPFLAGS) $(GTKLINK) -o gtkAiksaur \
            gtkAiksaur.t.cpp AiksaurusGTK.o AiksaurusGTK_strlist.o \
	    AiksaurusGTK_histlist.o AiksaurusGTK_utils.o AiksaurusGTK_picbutton.o \
	    AiksaurusGTK_history.o AiksaurusGTK_icons.o -lAikSaurus

AiksaurusGTK.o : AiksaurusGTK.cpp AiksaurusGTK.h AiksaurusGTK_strlist.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -c AiksaurusGTK.cpp




test.history : test.history.cpp AiksaurusGTK_history.o AiksaurusGTK_strlist.o AiksaurusGTK_utils.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -o test.history \
	test.history.cpp AiksaurusGTK_history.o AiksaurusGTK_strlist.o AiksaurusGTK_utils.o

test.histlist : test.histlist.cpp AiksaurusGTK_histlist.o AiksaurusGTK_strlist.o AiksaurusGTK_utils.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -o test.histlist \
	test.histlist.cpp AiksaurusGTK_histlist.o AiksaurusGTK_strlist.o AiksaurusGTK_utils.o

test.strlist : test.strlist.cpp AiksaurusGTK_strlist.o AiksaurusGTK_utils.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -o test.strlist \
	test.strlist.cpp AiksaurusGTK_utils.o AiksaurusGTK_strlist.o 

test.strlist2 : test.strlist2.cpp AiksaurusGTK_strlist.o AiksaurusGTK_utils.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -o test.strlist2 \
	test.strlist2.cpp AiksaurusGTK_utils.o AiksaurusGTK_strlist.o 

test.picbutton : test.picbutton.cpp AiksaurusGTK_utils.o AiksaurusGTK_strlist.o \
                 AiksaurusGTK_picbutton.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -o test.picbutton \
	test.picbutton.cpp AiksaurusGTK_picbutton.o AiksaurusGTK_strlist.o AiksaurusGTK_utils.o

test.utils : test.utils.cpp AiksaurusGTK_utils.o 
	$(CC) $(CPPFLAGS) -o test.utils \
	test.utils.cpp AiksaurusGTK_utils.o 

test.searchbar : test.searchbar.cpp AiksaurusGTK_searchbar.o \
		 AiksaurusGTK_histlist.o AiksaurusGTK_strlist.o \
		 AiksaurusGTK_utils.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -o test.searchbar \
		test.searchbar.cpp AiksaurusGTK_searchbar.o \
		AiksaurusGTK_histlist.o AiksaurusGTK_strlist.o \
		AiksaurusGTK_utils.o
	

AiksaurusGTK_searchbar.o : AiksaurusGTK_searchbar.cpp AiksaurusGTK_searchbar.h \
                           AiksaurusGTK_histlist.o AiksaurusGTK_utils.o
	$(CC) $(CPPFLAGS) $(GTKLINK) -c AiksaurusGTK_searchbar.cpp

AiksaurusGTK_histlist.o : AiksaurusGTK_histlist.cpp AiksaurusGTK_histlist.h AiksaurusGTK_strlist.h
	$(CC) $(CPPFLAGS) $(GTKLINK) -c AiksaurusGTK_histlist.cpp

AiksaurusGTK_history.o : AiksaurusGTK_history.cpp AiksaurusGTK_history.h AiksaurusGTK_strlist.h
	$(CC) $(CPPFLAGS) $(GTKLINK) -c AiksaurusGTK_history.cpp

AiksaurusGTK_strlist.o : AiksaurusGTK_strlist.cpp AiksaurusGTK_strlist.h AiksaurusGTK_utils.h
	$(CC) $(CPPFLAGS) $(GTKLINK) -c AiksaurusGTK_strlist.cpp

AiksaurusGTK_picbutton.o : AiksaurusGTK_picbutton.h AiksaurusGTK_picbutton.cpp \
                           AiksaurusGTK_strlist.h AiksaurusGTK_utils.h
	$(CC) $(CPPFLAGS) $(GTKLINK) -c AiksaurusGTK_picbutton.cpp

AiksaurusGTK_icons.o : AiksaurusGTK_icons.h AiksaurusGTK_icons.cpp
	$(CC) $(CPPFLAGS) $(GTKLINK) -c AiksaurusGTK_icons.cpp

AiksaurusGTK_utils.o : AiksaurusGTK_utils.h AiksaurusGTK_utils.cpp
	$(CC) $(CPPFLAGS) -c AiksaurusGTK_utils.cpp 



clean:
	rm gtkAiksaur $(TESTS) *.o *~


