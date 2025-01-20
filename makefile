# Compilers and flags
CXX = g++        # C++ compiler
CC = gcc         # C compiler
CXXFLAGS = -Wall -g  # C++ compiler flags
CFLAGS = -Wall -g    # C compiler flags

# Target executable
TARGET = statistics

# Directories
SRC_DIR = src
INC_DIR = include

# Source and object files
C_SRCS = $(wildcard $(SRC_DIR)/*.c)     # C source files
CPP_SRCS = $(wildcard $(SRC_DIR)/*.cpp) # C++ source files
OBJS = $(C_SRCS:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o) \
       $(CPP_SRCS:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o) # Object files

# Build the target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile C files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Compile C++ files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJS)
