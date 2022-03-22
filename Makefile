GCC_F=-Wall -Werror -Wextra
NAME=-o Alias

all: build

build: main.c main.h
	gcc $(GCC_F) NAME