INCLUDES = -I../.. -I$(top_srcdir)/core/src

AM_CXXFLAGS = @GTK_CFLAGS@ @GTK_DEFS@

lib_LTLIBRARIES = libAiksaurusGTK.la

libAiksaurusGTK_la_LDFLAGS = -no-undefined -release $(LT_RELEASE) -version-info $(LT_AIKGTK_VERSION_INFO) -export-dynamic

libAiksaurusGTK_la_LIBADD = $(GTK_LIBS) ../../core/src/libAiksaurus.la

libAiksaurusGTK_la_SOURCES = \
	AiksaurusGTK.cpp \
	AiksaurusGTK_histlist.cpp \
	AiksaurusGTK_history.cpp \
	AiksaurusGTK_picbutton.cpp \
	AiksaurusGTK_strlist.cpp \
	AiksaurusGTK_utils.cpp \
	Display.cpp \
	Exception.cpp \
	Icons.cpp \
	Meaning.cpp \
	Replacebar.cpp \
	Toolbar.cpp \
	AiksaurusGTK-C.cpp

aikhdrdir = $(includedir)/Aiksaurus

aikhdr_HEADERS = \
	AiksaurusGTK.h \
	AiksaurusGTK-C.h

OTHERHEADERS = \
	AiksaurusGTK_histlist.h \
	AiksaurusGTK_history.h \
	AiksaurusGTK_picbutton.h \
	AiksaurusGTK_strlist.h \
	AiksaurusGTK_utils.h \
	DialogMediator.h \
	Display.h \
	Exception.h \
	Icons.h \
	Meaning.h \
	Replacebar.h \
	Toolbar.h

bin_PROGRAMS = AiksaurusGTK

AiksaurusGTK_SOURCES = gtkAiksaur.t.cpp
AiksaurusGTK_LDADD = libAiksaurusGTK.la

EXTRA_DIST = $(OTHERHEADERS)
