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
	MeaningsFile.cpp \
	MeaningsFile.h \
	MeaningsHash.h \
	WordStream.h \
	WordsFile.cpp \
	WordsFile.h \
	WordsHash.h \
        AiksaurusC.cpp \
	AiksaurusC.h	

libAiksaurus_la_LDFLAGS = -version-info 0:15

include_HEADERS = \
	Aiksaurus.h \
	AiksaurusC.h

bin_PROGRAMS = aiksaurus caiksaurus 

aiksaurus_SOURCES = aiksaurus.t.cpp
aiksaurus_LDADD = libAiksaurus.la

caiksaurus_SOURCES = caiksaurus.cpp
caiksaurus_LDADD = libAiksaurus.la
