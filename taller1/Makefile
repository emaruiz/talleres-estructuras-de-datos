CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

SOURCES = Pila.cpp tests.cpp
OBJS = $(SOURCES:.cpp=.o)

LIBS =

TARGET =	tests

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: run valgrind

run: all
	./$(TARGET)

valgrind: all
	valgrind --leak-check=full ./$(TARGET)
