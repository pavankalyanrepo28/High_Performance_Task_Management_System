CXX = g++
CXXFLAGS = -Wall -std=c++11
SRC_DIR = src
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/task.cpp $(SRC_DIR)/task_manager.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = task_manager

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) 