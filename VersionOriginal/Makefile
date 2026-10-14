# Compilateur
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -g -fsanitize=address
LDFLAGS = -lncurses -fsanitize=address

# Nom de l'exécutable
TARGET = jeu

# Fichiers sources
SRC = main.c Affichage.c Canon.c Flechette.c Canar.c

# Objets générés automatiquement
OBJ = $(SRC:.c=.o)

# Règle principale
all: $(TARGET)

# Link final
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f *.o *~ $(TARGET)

# Rebuild complet
re: clean all

# Lancer le programme
run: $(TARGET)
	./$(TARGET) 50 25 1
