myshell: obj/main.o obj/functions.o
	gcc obj/main.o obj/functions.o -o myshell
obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o
obj/functions.o: src/functions.c
	gcc -c src/functions.c -o obj/functions.o