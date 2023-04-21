all: bin/app.exe
	gcc src/app/app.c -o bin/app.exe -lgdi32 -lmingw32

run:
	bin/app.exe