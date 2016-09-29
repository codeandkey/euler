CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g
LDFLAGS = -lm

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

OUTPUT=out

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(OUTPUT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
