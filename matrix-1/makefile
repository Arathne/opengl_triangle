compile: main.o shader.o texture.o
	g++ main.o shader.o texture.o -lm -lGL -L/usr/X11R6/lib -lGLU -lglut -lGLEW -lXi -lXmu

main.o: main.cpp
	g++ -c main.cpp

shader.o: shader.h shader.cpp
	g++ -c shader.cpp

texture.o: texture.h texture.cpp
	g++ -c texture.cpp

run: a.out
	./a.out

clean:
	rm *.o
	rm *.out
