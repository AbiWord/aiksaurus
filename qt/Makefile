CC=g++
CPPFLAGS=-Wall -ansi
KDEDIR=/usr/lib/kde2
QTDIR=/usr/lib/qt2
MOC=moc

all: kaiksaur

install: all
	cp kaiksaur /usr/bin/
	chmod 755 /usr/bin/kaiksaur
	chown root.root /usr/bin/kaiksaur

uninstall: clean
	rm -f /usr/bin/kaiksaur

kaiksaur : Kaiksaur.o moc_Kaiksaur.o QAikSaurusHistory.o 
	$(CC) $(CPPFLAGS) -o kaiksaur \
	Kaiksaur.o moc_Kaiksaur.o QAikSaurusHistory.o \
	-L$(KDEDIR)/lib -lkdeui -lkdecore -lqt -ldl -lbz2 -lAikSaurus

Kaiksaur.o : Kaiksaur.cpp QAikSaurusHistory.h
	$(CC) $(CPPFLAGS) -c Kaiksaur.cpp -I$(QTDIR)/include

moc_Kaiksaur.o : moc_Kaiksaur.cpp
	$(CC) $(CPPFLAGS) -c moc_Kaiksaur.cpp -I$(QTDIR)/include 

moc_Kaiksaur.cpp : Kaiksaur.h
	$(MOC) Kaiksaur.h -o moc_Kaiksaur.cpp

QAikSaurusHistory.o : QAikSaurusHistory.h QAikSaurusHistory.cpp
	$(CC) $(CPPFLAGS) -c QAikSaurusHistory.cpp -I$(QTDIR)/include

clean:
	rm -f kaiksaur *.o

