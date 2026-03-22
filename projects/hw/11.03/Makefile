CXX      ?= g++
CXXFLAGS ?= -Wall -Wextra -Wpedantic -O3 -std=c++17

GTEST_CFLAGS := $(shell pkg-config --cflags gtest 2>/dev/null)
GTEST_LIBS   := $(shell pkg-config --libs gtest 2>/dev/null)
ifeq ($(GTEST_LIBS),)
    GTEST_CFLAGS := -I/opt/homebrew/include -I/usr/local/include
    GTEST_LIBS   := -L/opt/homebrew/lib -L/usr/local/lib -lgtest -lgtest_main -lpthread
else
    GTEST_LIBS   := $(GTEST_LIBS) -lgtest_main -lpthread
endif

TARGET  = 11.03
SOURCES = 11.03.cpp

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(GTEST_CFLAGS) -o $@ $(SOURCES) $(GTEST_LIBS)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	./$(TARGET)
