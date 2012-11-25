CC=gcc
CFLAGS=-c -std=c99
LDFLAGS=-lgmp
SOURCES=dsa_genkey.c dsa_sign.c dsa_validate_params.c dsa_verify.c dsa_test.c
OBJECTS=$(SOURCES:.c=.o)
BINARY=dsa_test

all: $(SOURCES) $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(BINARY)

