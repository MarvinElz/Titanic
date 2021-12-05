Solver.o: Solver.cpp Solver.h Step.o Step.h Field.o Field.h
	g++ -c Solver.cpp

Step.o: Step.cpp Step.h Field.h
	g++ -c Step.cpp

Field.o: Field.cpp Field.h Step.o Step.h
	g++ -c Field.cpp -leigen

Titanic: Titanic.cpp Field.o Field.h Step.o Step.h Solver.o Solver.h
	g++ -o Titanic -O2 Titanic.cpp Field.o Step.o Solver.o -lpthread

clean:
	rm -f Titanic Field.o Step.o Solver.o
