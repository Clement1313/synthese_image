CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -I.

TARGET := raycast

SRCS := \
	main.cc \
	camera/Camera.cpp \
	image/Image.cc \
	object/Sphere.cc \
	vector3/Vector3.cc

OBJS := $(SRCS:.cpp=.o)
OBJS := $(OBJS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
