CC = g++
CPPFLAGS = -Wall     
LIBS =

# Erase all suffixes and set our own
.SUFFIXES:
.SUFFIXES: .o .cpp .h

# $@ = .o file
# $^ = all listed dependancies
.cpp.o:
	$(CC) $(CPPFLAGS) -c $<
.o:
	$(CC) $(CPPFLAGS) -o $@ $^ $(LIBS)

all: fake_all

include MakeTargets
include MakeDepend

fake_all: $(TARGETS)

MakeDepend: *.cpp *.h
	@echo "Generating dependency information..."
	@g++ -MM *.cpp > MakeDepend
	@echo "Dependency information created."

clean:
	rm -f *.o $(TARGETS) MakeDepend
