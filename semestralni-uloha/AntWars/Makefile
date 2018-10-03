CXX=gcc
CFLAGS= -std=c++11 -Wall -pedantic -Wno-long-long -O0
LDFLAGS=
EXECUTABLE=jencmart
SOURCES= main.cpp gameWrapper.cpp menu.cpp game.cpp inOut.cpp map.cpp mapElement.cpp antHill.cpp ant.cpp empty.cpp wall.cpp path.cpp humanPlayer.cpp botPlayer.cpp command.cpp

all: $(SOURCES:.cpp=.o)
	$(CXX) $(LDFLAGS) $(SOURCES:.cpp=.o) -o $(EXECUTABLE) -lstdc++ -lncurses
	doxygen Doxyfile

clean:
	$(RM)$(SOURCES:.cpp=.o) $(EXECUTABLE)
	$(RM) -R doc

run:
	./$(EXECUTABLE)

doc:
	doxygen Doxyfile
