TEMPS = meanings.text.sort2 \
        meanings.text.sort1 \
        words.text \
        links.dat

FINALS = words.dat \
         meanings.dat \
	 MeaningsHash.h

	 
all: $(TEMPS) $(FINALS)
	@echo ""
	@echo "All done with data conversion."
	@echo ""
	@echo "Relevant files are: "
	@echo "   words.dat         (words side of thesaurus data)"
	@echo "   meanings.dat      (meanings side of thesaurus data)"
	@echo "   MeaningsHash.h    (hash table for meanings file)"
	@echo ""
	@echo "Copy these files into your impl directory to continue."
	@echo ""
	@echo "  Run \"make clean\" to delete intermediate (temporary) files."
	@echo "  Run \"make clobber\" to delete all generated files."
	@echo ""

start:
	@echo ""
	@echo "Beginning Data Conversion."
	@echo ""
	@echo "This makefile is creating implementation data for the "
	@echo "thesaurus.  This is an involved process, but should "
	@echo "complete in under a minute on any reasonably fast "
	@echo "system."
	@echo ""
	
clean: 
	rm -f $(TEMPS)

clobber: 
	rm -f $(FINALS) $(TEMPS)

	
meanings.text.sort1: meanings.text start
	@echo "  > Sorting meanings.text (pass 1 of 2)" 
	@../src/SortMeanings < meanings.text > meanings.text.sort1
	@echo ""

meanings.text.sort2 : meanings.text.sort1
	@echo "  > Sorting meanings.text (pass 2 of 2)"
	@../src/InsensitiveSorter < meanings.text.sort1 > meanings.text.sort2
	@echo ""

words.text : meanings.text
	@echo "  > Building words.text from meanings.text"
	@../src/ExtractWords < meanings.text | ../src/InsensitiveSorter > words.text
	@echo ""

links.dat : words.text 
	@echo "  > Building links.dat from words.text..."
	@../src/LinkWords --words=words.text --meanings=meanings.text.sort2 \                                      --output=links.dat.temp
	@../src/InsensitiveSorter < links.dat.temp > links.dat
	@rm links.dat.temp
	@echo ""
	
words.dat : links.dat
	@echo "  > Creating Words Implementation"
	@../src/ImplWords --links=links.dat --maxchars=17 --maxlinks=5 --out=words.dat
	@echo ""

meanings.dat : meanings.text.sort2 words.text
	@echo "  > Creating Meanings Implementation"
	@../src/ImplMeanings -m=meanings.text.sort2 -w=words.text -o=meanings.dat
	@echo ""
	
MeaningsHash.h : meanings.dat
	@echo "  > Creating Meanings Hash Data"
	@../src/MkOffsetTable --input=meanings.dat --split=4 > MeaningsHash.h
	@echo ""
	
