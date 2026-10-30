CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = 1uzd
SOURCES = 1uzd.cpp
HEADERS = 1uzd_def.h 1uzd_list.h 1uzd_papildai.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET)
