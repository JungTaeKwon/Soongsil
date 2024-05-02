CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = 20192944
SRCS = 20192944.c
OBJS = $(SRCS:.c=.o)
HEADERS = 20192944.h

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	$(CC) $(CFLAGS) -o test test.c

$(OBJS): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRCS)


run:
	./$(TARGET) ./test

clean:
	rm -f $(OBJS) $(TARGET)
	rm test
