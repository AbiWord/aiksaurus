AUTOMAKE_OPTIONS = foreign

SUBDIRS=data
 
lib_LTLIBRARIES = libAikSaurus.la

CXXFLAGS=@AIK_CXXFLAGS@ @CXXFLAGS@

libAikSaurus_la_SOURCES = \
	bzreader.cpp \
	bzreader.h \
	AikSaurus.cpp \
	AikSaurus.h \
	StringLoopQueue.h 

libAikSaurus_la_LIBADD = -lbz2

libAikSaurus_la_LDFLAGS = -version-info 0:11
 
include_HEADERS = \
	AikSaurus.h

noinst_PROGRAMS = CommandLineDemo InteractiveDemo

CommandLineDemo_SOURCES = \
	CommandLineDemo.cpp

InteractiveDemo_SOURCES = \
	InteractiveDemo.cpp

CommandLineDemo_LDADD = libAikSaurus.la
InteractiveDemo_LDADD = libAikSaurus.la
 
EXTRA_DIST = autogen.sh ChangeLog README LICENSE CHANGES aiksaurus.spec.in
