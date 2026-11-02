
# Gravastar GearHub Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude
LIBS = -lpqxx -lpq

TARGET = gearhub.exe
SOURCES = $(wildcard src/*.cpp)

# Default build target
all: $(TARGET)

# Compile all source files
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LIBS)

# Build and run the program
run: $(TARGET)
	./$(TARGET)

# Remove compiled executable
clean:
	if exist $(TARGET) del /Q $(TARGET)

.PHONY: all run clean
