INCLUDES = -I../..

AM_CPPFLAGS = -DAIK_DATA_DIR=\"$(pkgdatadir)/\"

lib_LTLIBRARIES = libAiksaurus.la

libAiksaurus_la_LDFLAGS = -no-undefined -release $(LT_RELEASE) -version-info $(LT_AIK_VERSION_INFO) -export-dynamic
libAiksaurus_la_LIBADD = 

libAiksaurus_la_SOURCES = \
	Aiksaurus.cpp \
	AiksaurusException.cpp \
	AsciiCompare.cpp \
	MeaningsFile.cpp \
	WordsFile.cpp \
        AiksaurusC.cpp

aikhdrdir = $(includedir)/Aiksaurus

aikhdr_HEADERS = \
	Aiksaurus.h \
	AiksaurusC.h

OTHERHEADERS = \
	AiksaurusException.h \
	AsciiCompare.h \
	MeaningsFile.h \
	MeaningsHash.h \
	WordStream.h \
	WordsFile.h \
	WordsHash.h

bin_PROGRAMS = aiksaurus caiksaurus 

aiksaurus_SOURCES = aiksaurus.t.cpp
aiksaurus_LDADD = libAiksaurus.la

caiksaurus_SOURCES = caiksaurus.cpp
caiksaurus_LDADD = libAiksaurus.la

EXTRA_DIST = $(OTHERHEADERS)
