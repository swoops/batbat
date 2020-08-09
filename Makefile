CC = gcc
CFLAGS = -Wall -O3
TARGET = batbat
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

ALL = $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean install uninstall
install: $(TARGET)
	install -o root -g root -m 555 $(TARGET) /opt/$(TARGET)
uninstall:
	rm /opt/$(TARGET)
clean:
	rm -f $(OBJ) $(TARGET)
