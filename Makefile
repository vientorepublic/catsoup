CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = catsoup

SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.c)
HEADERS = $(wildcard $(SRCDIR)/*.h)

OBJDIR = obj
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Cross-compilation settings
TARGET_LINUX = $(TARGET)-linux
TARGET_MACOS = $(TARGET)-macos

all: $(TARGET_LINUX) $(TARGET_MACOS)

$(TARGET_LINUX): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_MACOS): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(OBJDIR) # Ensure obj directory exists
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TARGET_LINUX) $(TARGET_MACOS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run