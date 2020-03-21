compile: main.o shader.o texture.o
	g++ main.o shader.o texture.o -lm -lGL -L/usr/X11R6/lib -lGLU -lglut -lGLEW -lXi -lXmu

main.o:
	g++ -c main.cpp

shader.o: shader.h
	g++ -c shader.cpp

texture.o: texture.h
	g++ -c texture.cpp

run: a.out
	./a.out

clean:
	rm *.o
	rm *.out
