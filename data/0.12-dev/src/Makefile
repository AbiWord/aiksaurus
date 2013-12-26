CC = g++
CFLAGS = -Wall -O3 -s  
LDFLAGS =

# Erase all suffixes and set our own
.SUFFIXES:
.SUFFIXES: .o .cpp .h

# $@ = .o file
# $^ = all listed dependancies
.cpp.o:
	$(CC) $(CFLAGS) -c $<
.o:
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

all: fake_all

include MakeTargets
include MakeDepend

fake_all: $(TARGETS)

MakeDepend: *.cpp *.h
	g++ -MM *.cpp > MakeDepend

clean:
	rm -f *.o $(TARGETS) MakeDepend
