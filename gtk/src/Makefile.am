AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = libAiksaurusGTK.la

CXXFLAGS = @AIK_CXXFLAGS@ @CXXFLAGS@

libAiksaurusGTK_la_SOURCES = \
	AiksaurusGTK.cpp \
	AiksaurusGTK.h \
	AiksaurusGTK_histlist.cpp \
	AiksaurusGTK_histlist.h \
	AiksaurusGTK_history.cpp \
	AiksaurusGTK_history.h \
	AiksaurusGTK_picbutton.cpp \
	AiksaurusGTK_picbutton.h \
	AiksaurusGTK_strlist.cpp \
	AiksaurusGTK_strlist.h \
	AiksaurusGTK_utils.cpp \
	AiksaurusGTK_utils.h \
	DialogMediator.h \
	Display.cpp \
	Display.h \
	Exception.cpp \
	Exception.h \
	Icons.cpp \
	Icons.h \
	Meaning.cpp \
	Meaning.h \
	Replacebar.cpp \
	Replacebar.h \
	Toolbar.cpp \
	Toolbar.h \
        AiksaurusGTK-C.h \
	AiksaurusGTK-C.cpp

libAiksaurusGTK_la_LDFLAGS = -version-info 0:14

include_HEADERS = \
	AiksaurusGTK.h \
	AiksaurusGTK-C.h

bin_PROGRAMS = AiksaurusGTK

AiksaurusGTK_SOURCES = gtkAiksaur.t.cpp
AiksaurusGTK_LDADD = libAiksaurusGTK.la

