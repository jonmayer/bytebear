# Makefile for bytebear
# Creative Commons Attribution 3.0 License
# http://creativecommons.org/licenses/by/3.0/

CC=g++
SIZE=$(shell echo $$((4 * 1024 * 1024)) )
MODULES=$(patsubst %.cc,%,$(filter-out bytebear_main.cc,$(wildcard *.cc)))
TARGETS=$(patsubst %,%.wav,$(MODULES))
CPPFLAGS=-g


all: $(TARGETS)
	@echo ""
	@echo " n___n"
	@echo "(=9v9=) bytebear"
	@echo "(\")_(\") $(MODULES)"
	@echo ""

clean:
	rm -f *.bb *.o *.wav *.pgm *.ppm

bytebear_main.o: bytebear_main.cc bytebear.h

%.bb: %.o bytebear_main.o
	$(CC) $(LDFLAGS) -o $@ $^

%.wav: %.bb
	./$< $(SIZE) > $@.raw
	sox -r 44100 -c 1 -t u8 $@.raw $@ && rm $@.raw
