CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET   = game

SRCS = src/main.cpp \
       src/core/Player.cpp \
       src/core/Enemy.cpp \
       src/core/Item.cpp \
       src/core/Room.cpp \
       src/core/Map.cpp \
       src/ds/Stack.cpp \
       src/ds/Queue.cpp \
       src/ds/HashTable.cpp \
       src/ds/BST.cpp \
       src/ds/MergeSort.cpp \
       src/systems/ItemLoader.cpp \
       src/systems/Dijkstra.cpp \
       src/systems/Display.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
