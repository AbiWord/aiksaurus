AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = README abiPlugin/AiksaurusABI.cpp abiPlugin/Makefile \
	AiksaurusGTK.Readme \
	AiksaurusGTK_histlist.Readme \
	AiksaurusGTK_history.Readme \
	AiksaurusGTK_icons.Readme \
	AiksaurusGTK_picbutton.Readme \
	AiksaurusGTK_strlist.Readme \
	AiksaurusGTK_utils.Readme

if AIK_BUILD_GTK
AIK_GTK_HDRS = AiksaurusGTK.h
AIK_GTK_LIBS = libAikSaurusGTK.la
AIK_GTK_PROGS = gtkAiksaur
AIK_GTK_TESTS = test.histlist test.strlist test.strlist2 test.picbutton test.utils test.history
else
AIK_GTK_HDRS = 
AIK_GTK_LIBS = 
AIK_GTK_PROGS = 
AIK_GTK_TESTS = 
endif

include_HEADERS = $(AIK_GTK_HDRS)

lib_LTLIBRARIES = $(AIK_GTK_LIBS)

noinst_PROGRAMS = $(AIK_GTK_PROGS) $(AIK_GTK_TESTS)

TESTS = $(AIK_GTK_TESTS)

INCLUDES = -I. -I$(srcdir) -I$(top_builddir)

CPPFLAGS = @CPPFLAGS@ @aik_gtk_cflags@

libAikSaurusGTK_la_SOURCES = \
	AiksaurusGTK.cpp AiksaurusGTK.h \
	AiksaurusGTK_histlist.cpp AiksaurusGTK_histlist.h \
	AiksaurusGTK_history.cpp AiksaurusGTK_history.h \
	AiksaurusGTK_strlist.cpp AiksaurusGTK_strlist.h \
	AiksaurusGTK_picbutton.cpp AiksaurusGTK_picbutton.h \
	AiksaurusGTK_icons.cpp AiksaurusGTK_icons.h \
	AiksaurusGTK_utils.cpp AiksaurusGTK_utils.h

libAikSaurusGTK_la_LIBADD = @aik_gtk_libs@

libAikSaurusGTK_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) -release $(LT_RELEASE) -export-dynamic

gtkAiksaur_SOURCES = gtkAiksaur.t.cpp

gtkAiksaur_LDADD = libAikSaurusGTK.la $(top_builddir)/libAikSaurus.la @aik_gtk_libs@

test_history_SOURCES = test.history.cpp

test_history_LDADD = libAikSaurusGTK.la $(top_builddir)/libAikSaurus.la @aik_gtk_libs@

test_histlist_SOURCES = test.histlist.cpp

test_histlist_LDADD = libAikSaurusGTK.la $(top_builddir)/libAikSaurus.la @aik_gtk_libs@

test_strlist_SOURCES =test.strlist.cpp

test_strlist_LDADD = libAikSaurusGTK.la $(top_builddir)/libAikSaurus.la @aik_gtk_libs@

test_strlist2_SOURCES =test.strlist2.cpp

test_strlist2_LDADD = libAikSaurusGTK.la $(top_builddir)/libAikSaurus.la @aik_gtk_libs@

test_picbutton_SOURCES =test.picbutton.cpp

test_picbutton_LDADD = libAikSaurusGTK.la $(top_builddir)/libAikSaurus.la @aik_gtk_libs@

test_utils_SOURCES =test.utils.cpp

test_utils_LDADD = libAikSaurusGTK.la $(top_builddir)/libAikSaurus.la @aik_gtk_libs@
