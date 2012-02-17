# Makefile for bytebear
# Creative Commons Attribution 3.0 License
# http://creativecommons.org/licenses/by/3.0/

CC=g++
SIZE=$(shell echo $$((4 * 1024 * 1024)) )
MODULES=$(patsubst %.cc,%, \
	    $(shell find songs -name \*.cc))
TARGETS=$(patsubst %,%.wav,$(MODULES))
CPPFLAGS=-g -I $(PWD)

all:
	@echo ""
	@echo " n___n"
	@echo "(=9v9=) bytebear"
	@echo "(\")_(\")"
	@echo ""
	@echo "To make all songs in wav format: make wav"
	@echo "To make all songs in mp3 format: make mp3"
	@echo "To clean up afterwards: make clean"

wav: $(patsubst %,%.wav,$(MODULES))
	@echo Done.

mp3: $(patsubst %,%.mp3,$(MODULES))
	@echo Done.

clean:
	rm -f *.o songs/*/*.{bb,o,wav,pgm,ppm,mp3.png,jpg}

bytebear_main.o: bytebear_main.cc bytebear.h

%.bb: %.o bytebear_main.o
	$(CC) $(LDFLAGS) -o $@ $^

%.wav: %.bb
	./$< $(SIZE) > $@.raw
	sox -r 44100 -c 1 -t u8 $@.raw $@ && rm $@.raw

%.mp3: %.wav
	lame --quiet --alt-preset standard -m m $< $@
