AUTOMAKE_OPTIONS = foreign

SUBDIRS = . gtk data
 
INCLUDES = -I. -I$(srcdir) -I$(top_builddir)

DEFS = @DEFS@ -DAIK_DATA_DIR=\"$(pkgdatadir)/\"

CPPFLAGS = @CPPFLAGS@ @aik_bzip2_cppflags@

lib_LTLIBRARIES = libAikSaurus.la

libAikSaurus_la_SOURCES = \
	bzreader.cpp \
	bzreader.h \
	AikSaurus.cpp \
	AikSaurus.h \
	StringLoopQueue.h 

libAikSaurus_la_LIBADD = @aik_bzip2_ldflags@ @aik_bzip2_libs@

libAikSaurus_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) -release $(LT_RELEASE) -export-dynamic

include_HEADERS = AikSaurus.h

noinst_PROGRAMS = CommandLineDemo InteractiveDemo

CommandLineDemo_SOURCES = CommandLineDemo.cpp

CommandLineDemo_LDADD = libAikSaurus.la

InteractiveDemo_SOURCES = InteractiveDemo.cpp

InteractiveDemo_LDADD = libAikSaurus.la
 
EXTRA_DIST = autogen.sh ChangeLog README LICENSE CHANGES aiksaurus.spec.in
