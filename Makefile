all:
	@echo "build - To build executable file"
	@echo "run - To run game"
	@echo "clear - To clear working directory from temporary files"
build:
	@gcc src/main.c src/inits.c src/debug.c src/thread_funcs.c -o bin/snake.exe -lncurses
	@echo "[+]BUILD SUCCESS"
run:
	./bin/snake.exe
clear:
	@rm ./bin/*
	@echo "[+]SUCCESS"
