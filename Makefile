COMPILER = g++
LIB = SFML/build/lib/
INCLUDE = SFML/include/
MODULES = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main
EXECUTABLE = main
SOURCES = Vector2d.cpp Line.cpp WorldParameters.cpp CollisionDetector.cpp World.cpp Body.cpp main.cpp

clean: main.exe
	./clean.sh ${EXECUTABLE}.exe

compile:
	g++ -g -L${LIB} -I${INCLUDE} -I./include ${SOURCES} ${MODULES} -o ${EXECUTABLE}

run: main.exe
	./${EXECUTABLE}