CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -I sources
TARGET := raytracer

SRCS := \
	main.cpp \
	sources/image/Image.cpp

OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

sources/image/Image.o: sources/image/Image.cpp sources/image/Image.hh sources/Color.hh
	$(CXX) $(CXXFLAGS) -c sources/image/Image.cpp -o sources/image/Image.o

clean:
	rm -f $(OBJS) $(TARGET)