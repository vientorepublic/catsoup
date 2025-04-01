CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = src/main.c
TARGET = catsoup

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)