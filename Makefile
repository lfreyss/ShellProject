#Chemin de recherche des fichiers
VPATH = src/ header/
#Compilateur
CC=gcc
# Recherche des .C pour la cible sans librairies
SRC=$(wildcard src/*.c)
OBJ=$(notdir $(patsubst %.c,%.o,$(SRC)))
# documentation path
DOC_DIR=./doc
# gcov stuff
GCOV_DIR=./gcov
GCOVFLAGS=-O0 --coverage -lgcov -Wall -g
LCOV_REPORT=report.info

# Nom de l'éxecutable
PROG=shell

# gcov exec
GEXEC=$(PROG).cov 

# Cible appelée par défaut
all: $(PROG)

# Programme sans librairie
$(PROG): $(OBJ)
	$(CC) -g -o $@ $^


%.o: %.c %.h
	$(CC) -g -c $<

# Doxygen
#doc:
#  doxygen $(DOC_DIR)/doxygen.conf
  
# Test Coverage
gcov: $(GEXEC)
	# generate some data for gcov by calling the generated binary with various options
	$(GCOV_DIR)/$(GEXEC) -h
	$(GCOV_DIR)/$(GEXEC) -i input -o output -v

	find ./ -maxdepth 1 -name "*.gcno" -exec mv {} $(GCOV_DIR) \;
	find ./ -maxdepth 1 -name "*.gcda" -exec mv {} $(GCOV_DIR) \;

	gcov -o $(GCOV_DIR) $(GEXEC)
	lcov -o $(GCOV_DIR)/$(LCOV_REPORT) -c -f -d $(GCOV_DIR)
  genhtml -o $(GCOV_DIR)/report $(GCOV_DIR)/$(LCOV_REPORT)

#Nettoyage des fichiers de pré-compilation
clean:
	rm $(PROG) *.o
