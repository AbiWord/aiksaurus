AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = libAiksaurus.la

CXXFLAGS=@AIK_CXXFLAGS@ @CXXFLAGS@

libAiksaurus_la_SOURCES = \
	Aiksaurus.cpp \
	Aiksaurus.h \
	AiksaurusException.cpp \
	AiksaurusException.h \
	AsciiCompare.cpp \
	AsciiCompare.h \
	FileArray.cpp \
	FileArray.h \
	MeaningsFile.cpp \
	MeaningsFile.h \
	MeaningsHash.h \
	WordStream.h \
	WordsFile.cpp \
	WordsFile.h 

libAiksaurus_la_LDFLAGS = -version-info 0:13

libAiksaurus_la_CXXFLAGS = -s

include_HEADERS = \
	Aiksaurus.h

bin_PROGRAMS = aiksaurus 

aiksaurus_SOURCES = aiksaurus.cpp
aiksaurus_LDADD = libAiksaurus.la
	
