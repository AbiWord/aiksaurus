CC = g++
CPPFLAGS = -Wall -ansi
ABIROOT=/opt/abiword
ABISRC = $(ABIROOT)/abi/src

INCLUDE = -I$(ABISRC)/af/xap/xp \
          -I$(ABISRC)/af/util/xp \
	  -I$(ABISRC)/af/util/unix \
	  -I$(ABISRC)/text/fmt/xp \
	  -I$(ABISRC)/af/ev/xp \
	  -I$(ABISRC)/text/ptbl/xp \
	  -I$(ABISRC)/af/gr/xp \
	  -I$(ABISRC)/wp/impexp/xp \
	  -I$(ABISRC)/wp/ap/xp \
	  -I$(ABIROOT)/expat/lib
	  
LIBS = -lAikSaurus -lAiksaurusGTK

libAiksaurusABI.so : AiksaurusABI.cpp
	$(CC) $(CPPFLAGS) $(INCLUDE) -shared -o libAiksaurusABI.so AiksaurusABI.cpp $(LIBS)

clean: 
	rm *.so
