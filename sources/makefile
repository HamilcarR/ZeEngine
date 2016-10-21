CC = g++
CFLAGS = -std=c++17 -g  
LFLAGS = -lSDL2 -lGLEW -lGLU -lGL -lSOIL -lassimp
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)
EX = Se-hara

all: $(EX)
	mv $(EX) ../


$(EX): $(OBJ)
	@$(CC) -o $@ $^ $(LFLAGS)


%.o: %.cpp
	@$(CC) -c $< $(CFLAGS) -o $@


.PHONY: clean


clean: 
	rm -f *.o



