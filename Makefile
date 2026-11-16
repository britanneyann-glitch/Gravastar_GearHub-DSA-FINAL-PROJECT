

CXX = C:/msys64/ucrt64/bin/g++.exe

CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude

# PostgreSQL and libpqxx configuration
PQXX_CFLAGS = $(shell pkg-config --cflags libpqxx)
PQXX_LIBS = $(shell pkg-config --libs libpqxx)

TARGET = gearhub.exe

SOURCES = $(wildcard src/*.cpp)

# Default build target
all: $(TARGET)

# Compile all C++ source files
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(PQXX_CFLAGS) $(SOURCES) -o $(TARGET) $(PQXX_LIBS)

# Build and run the program
run: $(TARGET)
	./$(TARGET)

# Remove compiled executable
clean:
	rm -f $(TARGET)

.PHONY: all run clean
