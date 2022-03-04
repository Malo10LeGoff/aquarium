main : main.cpp Aquarium.o Bestiole.o Milieu.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Creature.o Milieu.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Creature.o : Creature.h Creature.cpp
	g++ -Wall -std=c++11  -c Bestiole.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

Behaviour.o : Behaviour.h Behaviour.cpp
	g++ -Wall -std=c++11 -c Behaviour.cpp -I .

