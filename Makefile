all:
	@echo "build - To build executable file"
	@echo "run - To run game"
	@echo "clear - To clear working directory from temporary files"
build:
	@mkdir bin
	@gcc src/main.c src/inits.c src/debug.c src/thread_funcs.c src/game.c src/menu.c -o bin/snake.exe -lncurses
	@echo "[+]BUILD SUCCESS"
run:
	@./bin/snake.exe
clear:
	@rm ./bin/*
	@rm -rf bin
	@echo "[+]SUCCESS"
