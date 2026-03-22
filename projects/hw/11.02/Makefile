CXX      ?= g++
CXXFLAGS ?= -Wall -Wextra -Wpedantic -O3 -std=c++17

BENCHMARK_CFLAGS := $(shell pkg-config --cflags benchmark 2>/dev/null)
BENCHMARK_LIBS   := $(shell pkg-config --libs benchmark 2>/dev/null)
ifeq ($(BENCHMARK_LIBS),)
    BENCHMARK_CFLAGS := -I/opt/homebrew/include -I/usr/local/include
    BENCHMARK_LIBS   := -L/opt/homebrew/lib -L/usr/local/lib -lbenchmark -lpthread
endif

TARGET  = 11.02
SOURCES = 11.02.cpp

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(BENCHMARK_CFLAGS) -o $@ $(SOURCES) $(BENCHMARK_LIBS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
