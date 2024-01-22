CC = gcc
CFLAGS = -Wall -Wextra -std=c11

LINKER = -lX11 -lm
SOURCE = main.c graphics.c engine.c
TARGET = main

$(TARGET): $(SOURCE)
	clear
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LINKER)

run: $(TARGET)
	clear
	./$(TARGET)

.PHONY: all run
