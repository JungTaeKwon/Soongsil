CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = minios
SRCDIR = kernel
SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/20192944/*.c)
OBJS = $(SRCS:.c=.o)
HEADERS = $(wildcard $(SRCDIR)/*.h) $(wildcard $(SRCDIR)/20192944/*.h)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lreadline

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
