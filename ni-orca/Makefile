# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11
ifdef VERBOSE
CFLAGS += -D VERBOSE
endif

# Source files
SRCS = src/graph.cpp src/orbit.cpp src/orbit_counter.cpp

BUILD_DIR = build
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:src/%.cpp=%.o))

# Executable name - Enumeration-based non-induced orbit counter
TARGET = enum_orca

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

# Default target
all: $(TARGET)

# Rule to compile each .cpp file to object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into executable
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	$(CC) $(CFLAGS) src/orca-reduced.cpp -o orca

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET) orca
