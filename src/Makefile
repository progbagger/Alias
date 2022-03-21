CC = gcc
CFLAGS = -Wall -Werror -Wextra
PTH = ../build/
EXEC = Alias
CFILES = data.c
MAIN = alias.c
OBJECTS = $(CFILES:.c=.o)
HEADERS = $(CFILES:.c=.h)

all: build clean

build: $(EXEC)

$(EXEC): $(OBJECTS) $(MAIN)
	$(CC) $(CFLAGS) $^ -o $(PTH)$(EXEC)

$(OBJECTS): $(CFILES) $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *.gch

clean_exe:
	rm -rf ../build/[!.gitkeep]*

force_clean: clean clean_exe