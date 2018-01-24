#Chemin de recherche des fichiers
VPATH = src/Engine src/IHM lib/Liste lib/Tab lib/Dessine header/
#Compilateur
CC=gcc
# Recherche des .C pour la cible sans librairies
SRC=$(wildcard src/IHM/*.c src/Engine/*.c lib/Liste/*.c lib/Tab/*.c lib/Dessine/*.c)
OBJ=$(notdir $(patsubst %.c,%.o,$(SRC)))


# Nom de l'éxecutable
PROG=affichage
# Cible appelée par défaut
all: $(PROG)


# Programme sans librairie
$(PROG): $(OBJ)
	$(CC) -g -o $@ $^
	

%.o: %.c %.h
	$(CC) -g -c $< -fPIC

#Nettoyage des fichiers de pré-compilation
clean:
	rm $(PROG) *.o *.a *.so
