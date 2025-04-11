CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = catsoup

SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.c)
HEADERS = $(wildcard $(SRCDIR)/*.h)

OBJDIR = obj
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Cross-compilation settings
TARGET_LINUX_X86_64 = $(TARGET)-linux-x86_64
TARGET_LINUX_ARM64 = $(TARGET)-linux-arm64
TARGET_MACOS = $(TARGET)-macos-arm64
TARGET_WINDOWS = $(TARGET)-windows-x86_64.exe

all: $(TARGET_LINUX_X86_64) $(TARGET_LINUX_ARM64) $(TARGET_MACOS) $(TARGET_WINDOWS)

$(TARGET_LINUX_X86_64): $(OBJS)
	$(CC) $(CFLAGS) -m64 -o $@ $^

$(TARGET_LINUX_ARM64): $(OBJS)
	$(CC) $(CFLAGS) -march=armv8-a -o $@ $^

$(TARGET_MACOS): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_WINDOWS): $(OBJS)
	$(CC) $(CFLAGS) -m64 -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(OBJDIR) # Ensure obj directory exists
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TARGET_LINUX_X86_64) $(TARGET_LINUX_ARM64) $(TARGET_MACOS) $(TARGET_WINDOWS)

.PHONY: all clean run