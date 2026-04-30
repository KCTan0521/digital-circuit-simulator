# 1. Variables
CXX = clang++
CXXFLAGS = -Wall -std=c++17
TARGET = $(BUILD_DIR)/Main
BUILD_DIR = build

# 2. List of source files (Auto-discovery)
SRCS = $(wildcard *.cpp)

# 3. Object files mapping
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# --- Rules ---

# Default rule (runs when you just type 'make')
all: $(TARGET)

# Link the executable from object files
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile .cpp files into the build folder
# We add | $(BUILD_DIR) as an "order-only" prerequisite
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean run