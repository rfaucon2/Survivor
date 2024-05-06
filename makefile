EXE = target/Survivor

SRC = $(wildcard src/*.cpp)
OBJ = $(subst src, build, $(patsubst %.cpp, %.o, $(SRC)))

DBG = -g

INCLUDE = -Iinclude
LIB = -L lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lsfml-audio 

all:  link
remake: clean all

build/%.o: src/%.cpp
	g++ $(INCLUDE) -c src/$*.cpp -o build/$*.o $(DBG)


link: $(OBJ)
	g++ $(OBJ) -o $(EXE) $(LIB) $(DBG)

run:
	$(EXE)

clean:
	erase $(subst build/, build\, $(OBJ))