
CC = gcc
FLAGS = -Wall

###################
# File structure
###################
SRCDIR = src/
OBJDIR = obj/


# Variables that define the exe file

TARGET = hangman
SOURCES = hangman.c input.c
OBJECTS = $(SOURCES:.c=.o)

# Directories 
vpath %.c src/
vpath %.o obj/
vpath %.h src/headers
vpath %.exe bin

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJECTS)

$(OBJDIR)/%.o: %.c
	$(CC) -co $@ $<
	
# BASIC IDEA. Will not work with multiple source files
#$(OBJECTS):
#	$(CC) $(FLAGS) -c -o $(OBJECTS) $(SOURCES)
	
clean :
	rm $(TARGET)
	