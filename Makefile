.PHONY: build lint test

build:
	gcc -Wall -Wextra -o dealerdesk *.c -lm

lint:
	gcc -Wall -Wextra -Werror -fsyntax-only *.c -I. tests/*.c

test: build
	gcc -Wall -Wextra -I. -o tests/test_calc tests/test_calc.c calc.c -lm
	./tests/test_calc
