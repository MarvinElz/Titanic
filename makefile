Solver.o: Solver.cpp Solver.h
	g++ -c Solver.cpp

Step.o: Step.cpp Step.h
	g++ -c Step.cpp

Field.o: Field.cpp Field.h
	g++ -c Field.cpp -leigen

Titanic: Titanic.cpp Field.o Field.h Step.o Step.h Solver.o Solver.h
	g++ -o Titanic Titanic.cpp Field.o Step.o Solver.o -lpthread
