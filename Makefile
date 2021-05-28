1: all

all: Obrazy2.o Zewn_przet.o Funkcje.o
	gcc Obrazy2.o Zewn_przet.o Funkcje.o -o images2

2: Obrazy2.o
	gcc Obrazy2.c

3: Zewn_przet.o
	gcc Zewn_przet.h Zewn_przet.c

4: Funkcje.o
	gcc Funkcje.h Funkcje.c

clean:
	rm -rf *o images
