all: neurone
	

neurone: Apprentissage.o gestionnaire_RN.o gestionnaire_IO.o interface.o neurone.o
	gcc -o neurone Apprentissage.o gestionnaire_RN.o gestionnaire_IO.o interface.o neurone.o
	

Apprentissage.o: Apprentissage.c Apprentissage.h gestionnaire_RN.h gestionnaire_IO.h
	gcc -c -o Apprentissage.o Apprentissage.c -Wall -lm
	

gestionnaire_RN.o: gestionnaire_RN.c gestionnaire_RN.h gestionnaire_IO.h
	gcc -c -o gestionnaire_RN.o gestionnaire_RN.c -Wall -lm
	

gestionnaire_IO.o: gestionnaire_IO.c gestionnaire_IO.h gestionnaire_RN.h
	gcc -c -o gestionnaire_IO.o gestionnaire_IO.c -Wall
	

interface.o: interface.c interface.h Apprentissage.h gestionnaire_RN.h gestionnaire_IO.h
	gcc -c -o interface.o interface.c -Wall
	

neurone.o: neurone.c neurone.h interface.h
	gcc -c -o neurone.o neurone.c -Wall
	
