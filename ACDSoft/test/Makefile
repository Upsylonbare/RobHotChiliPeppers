#
# Makefile des tests du projet.
#

#
# Organisation des sources.
#

# Packages.
PACKAGES = NetworkC Carto Folder Merger Converter

# Wrap des méthodes pour bouchonnage
LDWRAP = -Wl,--wrap=NetworkC_Postman_sendMsg
LDWRAP += -Wl,--wrap=Geographer_ask4Scan
LDWRAP += -Wl,--wrap=Geographer_setCarto
LDWRAP += -Wl,--wrap=Geographer_ackCarto
LDWRAP += -Wl,--wrap=NetworkC_Coder_encode
LDWRAP += -Wl,--wrap=NetworkC_Postman_askSend


# Un niveau de package est accessible.
SRC = $(wildcard */*.c)		
OBJ = $(SRC:.c=.o)

# Point d'entrée du programme.
MAIN = main_test.c

# Gestion automatique des dépendances.
DEP = $(MAIN:.c=.d)

# Executable à générer
EXEC = ../$(TEST)

# Inclusion depuis le niveau du package.
CCFLAGS += -I. -I$(CMOCKA)/include

CCFLAGS += -fprofile-arcs -ftest-coverage

# CCFLAGS += -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

GCDA = $(MAIN:.c=.gcda)
GCNO = $(MAIN:.c=.gcno)

GCOVR = gcovr
GCOVR_DIR = test_coverage

# Liens pour les tests.
LDFLAGS += -L$(CMOCKA)/lib

# Utilisation de la librairie static CMocka
LDFLAGS += -lcmocka-static

#
# Règles du Makefile.
#

# Compilation.
tests: $(PACKAGES) $(EXEC)

$(PACKAGES):
	@$(MAKE) $(MAKECMDGOALS) -C $@

test_report:
	[ -d $(GCOVR_DIR) ] || (mkdir -p $(GCOVR_DIR))
	$(GCOVR) -r .. --html --html-details -o $(GCOVR_DIR)/index.html

$(EXEC): $(OBJ) $(MAIN)
	$(CC) $(CCFLAGS) $(LDWRAP) $(OBJ) $(MAIN) -MF $(DEP) -o $(EXEC) $(LDFLAGS)

# Nettoyage.
.PHONY: clean tests $(PACKAGES)

clean: $(PACKAGES)
	@rm -f $(DEP) $(GCNO) $(GCDA)
	@rm -rf $(GCOVR_DIR)