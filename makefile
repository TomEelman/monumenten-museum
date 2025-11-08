# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Wconversion
LDFLAGS = -lSDL3 -lSDL3_ttf -lm -L/opt/homebrew/lib -Wl,-rpath,/opt/homebrew/lib
TARGET = museum

# Source files
SRCS = main.c museum-exhibit.c museum-guide.c museum-hall.c museum-object.c museum-navigator.c src/obj_geometry/kaaba.c src/obj_geometry/pyramide.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean