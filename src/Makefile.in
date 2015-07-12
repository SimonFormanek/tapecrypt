CFLAGS = -g --pedantic -Wall -std=c99 -O2
CPPFLAGS = -g --pedantic -Wall -std=c99 -O2

#LDFLAGS =

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = crypt decrypt 
crypt_SOURCES = crypt.c
decrypt_SOURCES = decrypt.c
#targetbinary1_SOURCES = targetbinary1.c myheader.h [...]
#targetbinary2_SOURCES = targetbinary2.c
#.
#.
#targetbinaryN_SOURCES = targetbinaryN.c
.PHONY: clean

clean:
	rm -f $(bin_PROGRAMS) *.o


all: crypt decrypt
