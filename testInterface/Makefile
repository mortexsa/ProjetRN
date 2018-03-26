all: clean compil
	./main

compil:
	gcc main.c `pkg-config --cflags --libs gtk+-2.0` -o main

clean:
	rm -fr main