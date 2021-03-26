all: ./src/compiler/main.c ./src/compiler/mlib.c ./src/compiler/parser.c
	@gcc -o main ./src/compiler/main.c ./src/compiler/parser.c ./src/compiler/mlib.c
	@./main
	@rm ./main
test: ./src/compiler/mlib.c ./src/compiler/parser.c ./tests/test.py ./src/compiler/main.c
	@gcc -o main ./src/compiler/parser.c ./src/compiler/main.c ./src/compiler/mlib.c
	@python3 ./tests/test.py
	@rm ./main
#	@rm ./tests/test.sa
debug: ./src/compiler/main.c ./src/compiler/mlib.c ./src/compiler/parser.c
	@gcc -g -o debug  ./src/compiler/main.c ./src/compiler/parser.c ./src/compiler/mlib.c
	
