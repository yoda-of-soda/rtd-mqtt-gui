CXX := g++
CXXFLAGS := -std=c++11 -Wall

LIBS := -lpaho-mqttpp3 -lpaho-mqtt3as
TEST_LIBS := -lgtest

QUEUE_URL := "tcp://127.0.0.1:1883"
CLIENT_ID := "publisher"

# Directories
SRC_DIR := src
INCLUDE_DIR := ./include
TEST_DIR := tests
BUILD_DIR := build
BIN_DIR := bin

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_FILES))
MAIN_FILE := main.cpp

# Include directories
INC := -I$(INCLUDE_DIR)

TARGET := $(BIN_DIR)/mqtt_publisher
TEST_TARGET := $(BIN_DIR)/test_mqtt_publisher

all: | $(BUILD_DIR) $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR) $(BIN_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: $(TARGET)

$(TARGET): $(OBJ_FILES) $(MAIN_FILE)
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

test: $(TEST_TARGET)
	@echo "Running tests..."
	$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ_FILES) $(filter-out $(BUILD_DIR)/$(patsubst %.cpp, %.o, $(MAIN_FILE)), $(OBJ_FILES))
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS) $(TEST_LIBS)

# $(TEST_TARGET): $(TEST_OBJ_FILES)
# 	$(CXX) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

start:
	QUEUE_URL=$(QUEUE_URL) CLIENT_ID=$(CLIENT_ID) TOPIC=$(TOPIC) $(TARGET)

# Clean command
clean:
	rm -f $(OBJ_FILES) $(TARGET)

neat:
	rm -f $(OBJ_FILES)

# g++ -std=c++11 build/topic_message_generator_test.o build/callback.o build/load_environment.o build/message_with_topic.o build/mqtt_client.o build/topic_message_generator.o -o bin/test_mqtt_publisher -lpaho-mqttpp3 -lpaho-mqtt3as
# g++ -std=c++11 build/topic_message_generator_test.o -o bin/test_mqtt_publisher -lgtest