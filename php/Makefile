VERSION = 0.12
	
SOURCES = phpAiksaur.php \
          phpAiksaur_embedded.php \
          phpAiksaur_popup.php \
          phpAiksaur_popup_frameset.php \
          phpAiksaur_popup_searchframe.php \
          phpAiksaur_popup_closeframe.php \
	  phpAiksaur_index.php

NAME = phpaiksaur-$(VERSION)
	  
%.phps:%.php
	ln -s $< $<s

all: $(SOURCES:.php=.phps) $(NAME).tar.gz
	 
	
$(NAME).tar.gz: $(SOURCES)
	mkdir -p $(NAME)	
	cp $(SOURCES) $(NAME)
	mv $(NAME)/phpAiksaur_index.php $(NAME)/index.php
	tar cvfz $(NAME).tar.gz $(NAME)

clean:
	rm *.phps
	rm -rf $(NAME)
