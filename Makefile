
CFLAGS := -Wall -std=gnu99 -pthread -g -DDEBUG
CXXFLAGS := -std=c++11 -pthread -g -DDEBUG
CPPSOURCES = l_test.cpp l_list.cpp haz_ptr.cpp
OBJECTS += $(CPPSOURCES:%.cpp=%.o)

%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

all: $(OBJECTS)
	g++ $(CXXFLAGS) $(OBJECTS) -o l_list

clean:
	rm *.o l_list
	
