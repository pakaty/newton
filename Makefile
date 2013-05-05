CC=g++
CFLAGS=-std=c++11 -c -Wall
LDFLAGS=
SOURCES=main.cpp gppp/gnuplot.cpp
OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=program

all: $(SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS) 
	    $(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	    $(CC) $(CFLAGS) $< -o $@
