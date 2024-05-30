CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Target names
TARGET_CV = 20192944-cv
TARGET_MUT = 20192944-mut
TARGET_SEM = 20192944-sem

# Source files
SRCS_CV = 20192944-cv.c
SRCS_MUT = 20192944-mut.c
SRCS_SEM = 20192944-sem.c

# Object files
OBJS_CV = $(SRCS_CV:.c=.o)
OBJS_MUT = $(SRCS_MUT:.c=.o)
OBJS_SEM = $(SRCS_SEM:.c=.o)

all: $(TARGET_CV) $(TARGET_MUT) $(TARGET_SEM)

$(TARGET_CV): $(OBJS_CV)
	$(CC) $(CFLAGS) -o $(TARGET_CV) $(OBJS_CV) -lm

$(OBJS_CV): $(SRCS_CV) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRCS_CV)

$(TARGET_MUT): $(OBJS_MUT)
	$(CC) $(CFLAGS) -o $(TARGET_MUT) $(OBJS_MUT) -lm

$(OBJS_MUT): $(SRCS_MUT) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRCS_MUT)

$(TARGET_SEM): $(OBJS_SEM)
	$(CC) $(CFLAGS) -o $(TARGET_SEM) $(OBJS_SEM) -lm

$(OBJS_SEM): $(SRCS_SEM) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRCS_SEM)

cv: $(TARGET_CV)
	./$(TARGET_CV)

mut: $(TARGET_MUT)
	./$(TARGET_MUT)

sem: $(TARGET_SEM)
	./$(TARGET_SEM)

clean:
	rm -f $(OBJS_CV) $(OBJS_MUT) $(OBJS_SEM) $(TARGET_CV) $(TARGET_MUT) $(TARGET_SEM)
