# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude -std=c++20 -I/usr/local/include
LDFLAGS = -lgtest_main -lgtest -pthread  # Link gtest and gtest_main

BUILD_DIR = build
TEST_DIR = test

# Targets
TARGET = $(BUILD_DIR)/poker_sim
SRCS = src/PokerSim.cpp src/Card.cpp src/CardParser.cpp
OBJS = $(SRCS:src/%.cpp=$(BUILD_DIR)/%.o)


TEST_APP = $(BUILD_DIR)/test
TEST_SRCS = $(TEST_DIR)/CardParsingTest.cpp
TEST_OBJS = $(TEST_SRCS:test/%.cpp=$(BUILD_DIR)/%.o)


# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compiling source files to object files in build
$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compiling source files to object files in build
$(BUILD_DIR)/%.o: test/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build Tests
$(TEST_APP): $(TEST_OBJS) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(TEST_OBJS) $(OBJS)

# Tests
test: $(TEST_APP)
	./$(TEST_APP)


# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
