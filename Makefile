GCC_F=-Wall -Werror -Wextra
NAME=-o Alias

all: build

build: main.c ./include/main.h
	gcc $(GCC_F) main.c $(NAME)