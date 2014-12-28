
CC = gcc
FLAGS = -Wall

###################
# File structure
###################
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# File variables

TARGET = $(BINDIR)/hangman
SOURCES = hangman.c input.c
OBJECTS = $(SOURCES:.c=.o)

# Directories 
VPATH = src;bin;obj

vpath %.c src/
vpath %.o obj/
vpath %.h src/headers/
vpath %.exe bin/

all : $(TARGET)

$(TARGET) : $(addprefix $(OBJDIR)/, $(OBJECTS))
	$(CC) $(FLAGS) -o $(TARGET) $^

$(OBJDIR)/%.o: %.c
	$(CC) -c $< -o $@
	
# BASIC IDEA. Will not work with multiple source files
#$(OBJECTS):
#	$(CC) $(FLAGS) -c -o $(OBJECTS) $(SOURCES)
	
clean :
	rm $(TARGET)
	