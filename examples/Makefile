exampledir = $(datarootdir)/doc/tapecrypt
example_DATA = sample1.dat sample2.dat

clean: cleantape
all: freshtape


freshtape:
	if [ ! -f tape.example ]; then ../src/tapegenerator 1024 20000 > tape.example; fi
cleantape:
	rm -f tape.example
