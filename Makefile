.PHONY: depend clean

run : build
	@echo A fost compilata cu succes!
build: sudoku.c
	gcc -o sudoku sudoku.c -Wall -g
clean:
	rm -rf sudoku
