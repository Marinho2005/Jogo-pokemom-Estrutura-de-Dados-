CC = gcc
CFLAGS = -Iinclude
TARGET = jogoAED
SRC = $(wildcard src/*.c)
HEADERS = $(wildcard include/*.h)

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
