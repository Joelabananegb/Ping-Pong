# Compilateur
CC = gcc

# Dossiers
SRC_DIR = src
OBJ_DIR = obj

# Flags
CFLAGS = -Wall -Wextra -g -fsanitize=address `sdl2-config --cflags` -lSDL2_image
LDFLAGS = -lncurses -fsanitize=address `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
ASAN = ASAN_OPTIONS=detect_leaks=0

# Nom de l'exécutable
TARGET = Game

# Fichiers sources
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/game.c $(SRC_DIR)/player.c $(SRC_DIR)/projectile.c $(SRC_DIR)/ennemie.c $(SRC_DIR)/wall.c

# Objets générés automatiquement
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Règle principale
all: $(TARGET)

# Link final
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compilation des .c en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Rebuild complet
re: clean all

# Lancer le programme
run: $(TARGET)
	$(ASAN) ./$(TARGET)
