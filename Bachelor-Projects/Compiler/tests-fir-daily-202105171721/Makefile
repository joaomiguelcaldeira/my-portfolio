# $Id: Makefile,v 1.1 2014/05/02 22:33:16 david Exp $
#---------------------------------------------------------------
#             CONFIGURE THESE VARIABLES IF NEEDED
#---------------------------------------------------------------

ROOT = ${HOME}/compiladores/root
RTS_LIB_DIR = $(ROOT)/usr/lib
XML_2_DOT_JAR = ../xml2dot.jar

COMPILER=../fir
ASM=yasm
DOT=dot

#---------------------------------------------------------------
#    PROBABLY, NO NEED TO CHANGE ANYTHING BEYOND THIS POINT
#---------------------------------------------------------------

COMPILER_FLAGS = 
LDFLAGS  = -m elf_i386 -L$(RTS_LIB_DIR) -lrts

SOURCES     = $(wildcard *.fir)
OBJECTS     = $(SOURCES:%.fir=%.o)
EXECUTABLES = $(SOURCES:%.fir=%)
ASTS            = $(SOURCES:%.fir=%.jpg)
XMLS            = $(SOURCES:%.fir=%.xml)

#---------------------------------------------------------------
#                DO NOT CHANGE AFTER THIS LINE
#---------------------------------------------------------------

all: $(EXECUTABLES)

%.xml: %.fir
	$(COMPILER) $< -o $@

%.asm: %.fir
	$(COMPILER) $< -o $@

%.o: %.asm
	$(ASM) -felf32 $< -o $@

%:%.o
	$(LD) $< -o $@ $(LDFLAGS)

ast: $(ASTS)

%.jpg: %.dot
	$(DOT) -Tjpg $< -o $@

%.dot: %.xml
	java -cp $(XML_2_DOT_JAR) xml2dot.xml2dot $<; mv $<".dot" $@

.SECONDARY: $(XMLS)
	
clean:
	$(RM) $(OBJECTS) $(EXECUTABLES) $(ASTS) *.c *.asm

#---------------------------------------------------------------
#                           THE END
#---------------------------------------------------------------
