CXX = g++
CXXFLAGS = -Wall -g -std=c++11  # Add the C++11 standard and other common flags

# Name of the executable
TARGET = MEGATRON

# All object files that will be generated
OBJS = main.o DataBase.o SchemaManager.o Pesos.o DataManager.o

# Default rule
all: $(TARGET)

# How to link the program
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# How to compile each source file
main.o: main.cpp DataBase.h SchemaManager.h Pesos.h DataManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

DataBase.o: database.cpp SchemaManager.h DataBase.h DataManager.h Pesos.h
	$(CXX) $(CXXFLAGS) -c DataBase.cpp -o DataBase.o

SchemaManager.o: SchemaManager.cpp schemaManager.h Pesos.h DataManager.h
	$(CXX) $(CXXFLAGS) -c SchemaManager.cpp -o SchemaManager.o

Pesos.o: Pesos.cpp Pesos.h DataManager.h
	$(CXX) $(CXXFLAGS) -c Pesos.cpp -o Pesos.o

DataManager.o: DataManager.cpp DataManager.h
	$(CXX) $(CXXFLAGS) -c DataManager.cpp -o DataManager.o

# Command to clean compiled files (optional)
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
