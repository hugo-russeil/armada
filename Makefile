CC = g++
CC_WIN = i686-w64-mingw32-g++
CFLAGS = -I ~/raylib/src -I $(INCLUDE_DIR) -I /usr/local/include
CFLAGS_WIN = -I ~/raylib/src -I $(INCLUDE_DIR) -I /usr/i686-w64-mingw32/include
LDFLAGS = -L ~/raylib/release/libs/linux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LDFLAGS_WIN = /usr/local/lib/libraylibwin.a -lgdi32 -lwinmm -luser32 -lm -L /usr/i686-w64-mingw32/lib -static-libgcc
SRC_DIR = src
INCLUDE_DIR = include
TARGET = main.out
TARGET_WIN = main.exe
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.c)

all: $(TARGET) $(TARGET_WIN)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	rm -f $(SRC_DIR)/*.o

$(TARGET_WIN): $(SOURCES)
	$(CC_WIN) $(CFLAGS) $^ $(LDFLAGS_WIN) -o $@
	rm -f $(SRC_DIR)/*.o

.PHONY: clean all

clean:
	rm -f $(TARGET)
	rm -f $(TARGET_WIN)