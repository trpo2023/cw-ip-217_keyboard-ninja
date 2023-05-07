all: bin/app.exe

bin/app.exe:
	gcc src/app/app.c -o bin/app.exe -lgdi32 -lmingw32

run:
	bin/app.exe

format: 
	clang-format -i --verbose src/app/app.c src/libapp/randtext.c

.PHONY: bin/app.exe