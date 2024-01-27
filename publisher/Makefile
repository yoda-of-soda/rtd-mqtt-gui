CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra

LIBS := -lpaho-mqttpp3 -lpaho-mqtt3as

SRC := *.cpp
TARGET := mqtt_publisher

QUEUE_URL := "tcp://127.0.0.1:1883"
CLIENT_ID := "publisher"

# Directories
SRC_DIR := src
INCLUDE_DIR := ./include

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))
MAIN_FILE := main.cpp

# Include directories
INC := -I$(INCLUDE_DIR)

all: $(TARGET)

# Build target
# $(TARGET): $(SRC)
# 	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
$(TARGET): $(OBJ_FILES) $(MAIN_FILE)
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $@ $(LIBS)

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

start: 
	QUEUE_URL=$(QUEUE_URL) CLIENT_ID=$(CLIENT_ID) TOPIC=$(TOPIC) ./$(TARGET)

# Clean command
clean:
	rm -f $(OBJ_FILES) $(TARGET)

neat:
	rm -f $(OBJ_FILES)