SOURCES=test.cpp simpleExplorer.cpp Explorer.cpp Matrix.cpp BTNode.h
EXECUTABLE=test
CC=g++
CFLAGS=-Wall
LDFLAGS=
OBJECTS=$(SOURCES:.cpp=.o)

all:$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o core
	rm -rf *~
