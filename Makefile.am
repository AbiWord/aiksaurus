DIST_SUBDIRS = core gtk

if AIK_FE_GTK
GTKSRCDIR = gtk
else
GTKSRCDIR = 
endif

SUBDIRS = core $(GTKSRCDIR)

PHPSOURCES = php/*.png php/*.php php/*.phps

COCOASOURCES = cocoa/*.lproj cocoa/*.png cocoa/*.icns cocoa/*.ai \
	cocoa/app \
	cocoa/fmwk \
	cocoa/Aiksaurus.pbproj/project.pbxproj \
	cocoa/main.m

EXTRA_DIST = $(PHPSOURCES) $(COCOASOURCES) autogen.sh ac-helpers/pkg-config/pkg.m4 aiksaurus.spec.in
