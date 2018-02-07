#Chemin de recherche des fichiers
VPATH = src/ header/
#Compilateur
CC=gcc
# Recherche des .C pour la cible sans librairies
SRC=$(wildcard src/*.c)
OBJ=$(notdir $(patsubst %.c,%.o,$(SRC)))


# Nom de l'éxecutable
PROG=shell
# Cible appelée par défaut
all: $(PROG)


# Programme sans librairie
$(PROG): $(OBJ)
	$(CC) -g -o $@ $^


%.o: %.c %.h
	$(CC) -g -c $< 

#Nettoyage des fichiers de pré-compilation
clean:
	rm $(PROG) *.o
