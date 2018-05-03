all: clear neurone
	

run: all
	./neurone
	

test: all
	./test
	

neurone: gestionnaire_IO.o gestionnaire_RN.o Apprentissage.o interface.o test.o neurone.o
	gcc -o neurone gestionnaire_IO.o gestionnaire_RN.o Apprentissage.o interface.o neurone.o -lm -lpthread -Wall
	gcc -o test gestionnaire_IO.o gestionnaire_RN.o Apprentissage.o interface.o test.o -lm -lpthread -Wall
	

Apprentissage.o: Apprentissage.h Apprentissage.c gestionnaire_RN.h gestionnaire_IO.h
	gcc -c -o Apprentissage.o Apprentissage.c -Wall -lm
	

gestionnaire_RN.o: gestionnaire_RN.h gestionnaire_RN.c Structures.h
	gcc -c -o gestionnaire_RN.o gestionnaire_RN.c -Wall -lm
	

gestionnaire_IO.o: gestionnaire_IO.h gestionnaire_IO.c Structures.h
	gcc -c -o gestionnaire_IO.o gestionnaire_IO.c -Wall
	

interface.o: interface.h interface.c Apprentissage.h gestionnaire_RN.h gestionnaire_IO.h
	gcc -c -o interface.o interface.c -Wall -lpthread
	

test.o: test.h test.c interface.h
	gcc -c -o test.o test.c -Wall
	

neurone.o: neurone.c interface.h
	gcc -c -o neurone.o neurone.c -Wall
	

clear:
	clear
	

clean:
	rm -f *.o
	rm -f neurone
	
