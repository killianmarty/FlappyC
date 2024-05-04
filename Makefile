# Compilateur
CC = gcc

# Options de compilation avec le standard le plus récent
CFLAGS = -Wall -Wextra -O3

# Bibliothèques SDL2 et SDL2_ttf
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_image -lrt

# Dossiers
OBJDIR = obj
RENDERDIR = render
GLOBALSDIR = globals
SPRITESDIR = sprites
ENGINEDIR = engine

# Fichiers source
SRCS = main.c \
       $(SPRITESDIR)/bird.c \
       $(SPRITESDIR)/tube.c \
       $(SPRITESDIR)/cloud.c \
       $(SPRITESDIR)/poop.c \
       $(RENDERDIR)/renderer.c \
       $(GLOBALSDIR)/utils.c \
	   $(ENGINEDIR)/engine.c

# Fichiers objets correspondants
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

# Exécutable final
TARGET = flappy

# Règle de construction de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Règle de compilation des fichiers source en fichiers objets
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -rf $(OBJDIR) $(TARGET)
