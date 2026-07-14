CC      = gcc
CFLAGS  = -Wall -Wextra -Iinclude
LDFLAGS = -lm

SRC     = src/main.c src/sensor.c
TARGET  = sensor_logger

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
