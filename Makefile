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
TARGET_WINDOWS = $(TARGET)-windows.exe

all: $(TARGET_LINUX) $(TARGET_MACOS) $(TARGET_WINDOWS)

$(TARGET_LINUX): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_MACOS): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_WINDOWS): $(OBJS)
	$(CC) $(CFLAGS) -m64 -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(OBJDIR) # Ensure obj directory exists
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TARGET_LINUX) $(TARGET_MACOS) $(TARGET_WINDOWS)

.PHONY: all clean run