EXE = target/Tweaker

SRC = $(wildcard src/*.cpp)
OBJ = $(subst src, build, $(patsubst %.cpp, %.o, $(SRC)))

INCLUDE = -Iinclude
LIB = -L lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lsfml-audio

all:  link

build/%.o: src/%.cpp
	g++ $(INCLUDE) -c src/$*.cpp -o build/$*.o


link: $(OBJ)
	g++ $(OBJ) -o $(EXE) $(LIB)

run:
	$(EXE)
	