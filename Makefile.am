DIST_SUBDIRS = base gtk gtk2 data po

if AIK_FE_GTK
GTKSRCDIR = gtk
else
GTKSRCDIR = 
endif

if AIK_FE_GTK2
GTK2SRCDIR = gtk2
else
GTK2SRCDIR = 
endif

SUBDIRS = base $(GTKSRCDIR) $(GTK2SRCDIR) data po

# PHPSOURCES = php/*.png php/*.php php/*.phps

# COCOASOURCES = cocoa/*.lproj cocoa/*.png cocoa/*.icns cocoa/*.ai \
#	cocoa/app \
#	cocoa/fmwk \
#	cocoa/Aiksaurus.pbproj/project.pbxproj \
#	cocoa/main.m

# WINSOURCES = win/src/*.*

desktopdir = $(datadir)/applications
desktop_in_files = gaiksaurus.desktop.in.in
desktop_DATA = $(desktop_in_files:.desktop.in.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

CLEANFILES = \
	$(desktop_DATA)	\
	$(NULL)

EXTRA_DIST =	\
	$(PHPSOURCES)			\
	$(COCOASOURCES)			\
	$(WINSOURCES)			\
	README.W32			\
	autogen.sh			\
	ac-helpers/pkg-config/pkg.m4	\
	aiksaurus.spec.in		\
	aiksaurus.spec
