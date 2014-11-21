# Declaration of variables
CC = g++
CC_FLAGS = -Wall -g -std=c++11 -march=i686

# File names
EXEC = run
SOURCES := $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o ./bin/$(EXEC)

# To obtain object files
# NOTE: currently outputs the *.obj file into the src folder
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f ./bin/$(EXEC) $(OBJECTS)
