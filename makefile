CXX = g++
CXXFLAGS = -std=c++1y
LDFLAGS = -lboost_regex -lboost_serialization

OBJ = dataGrid.o biIndex.o main.o indexTree.o Module.o

all: marks

dataGrid.o: dataGrid.cpp
	$(CXX) -c $< $(CXXFLAGS)

biIndex.o: biIndex.cpp
	$(CXX) -c $< $(CXXFLAGS)

indexTree.o: indexTree.cpp
	$(CXX) -c $< $(CXXFLAGS)

Module.o: Module.cpp dataGrid.o biIndex.o indexTree.o
	$(CXX) -c $< $(CXXFLAGS)

main.o: main.cpp Module.o
	$(CXX) -c $< $(CXXFLAGS)

marks: $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS) 

clean: 
	rm -rf *.o marks
