compile: main.o shader.o
	g++ main.o shader.o -lm -lGL -L/usr/X11R6/lib -lGLU -lglut -lGLEW -lXi -lXmu

main.o:
	g++ -c main.cpp

shader.o: shader.h
	g++ -c shader.cpp

run: a.out
	./a.out

clean:
	rm a.out
	rm shader.o
	rm main.o
