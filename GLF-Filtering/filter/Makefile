# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11
ifdef VERBOSE
CFLAGS += -D VERBOSE
endif

# Source files
SRCS = graph.cpp filter.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = filter

# Default target
all: $(TARGET)

# Rule to compile each .cpp file to object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

