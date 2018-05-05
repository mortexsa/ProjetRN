all: clean compil
	./main

compil:
	gcc test.c interface.c gestionnaire_IO.c gestionnaire_RN.c  Apprentissage.c `pkg-config --cflags --libs gtk+-2.0` -o main

clean:
	rm -fr main
