CXX      ?= g++
CXXFLAGS ?= -Wall -Wextra -Wpedantic -O3 -std=c++17

M32     ?=

TARGET  = 10.05
SOURCES = 10.05.cpp

.PHONY: all clean run m32

all: $(TARGET)

m32:
	$(MAKE) M32=-m32

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(M32) -o $@ $(SOURCES)

clean:
	rm -f $(TARGET) 10.05_*.csv 10.05_*.png

run: $(TARGET)
	./$(TARGET)
