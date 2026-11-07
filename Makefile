.PHONY: build lint

build:
	gcc -Wall -Wextra -o dealerdesk *.c -lm

lint:
	gcc -Wall -Wextra -Werror -fsyntax-only *.c
