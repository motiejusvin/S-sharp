all: ./src/compiler/main.c ./src/compiler/parser.c
	@gcc -o main ./src/compiler/main.c ./src/compiler/parser.c
	@./main
	@rm ./main
test: ./src/compiler/parser.c ./tests/test.py ./src/compiler/main.c
	@gcc -o main ./src/compiler/parser.c ./src/compiler/main.c
	@python3 ./tests/test.py
	@rm ./main

