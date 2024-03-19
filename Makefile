run: main.c
	@mkdir -p bin
	@gcc -W -Wall -Wextra -pedantic -o bin/poem main.c
	@bin/poem