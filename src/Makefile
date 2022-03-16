
main : main.cpp Aquarium.o Creature.o Milieu.o Behaviour.o Accessories.o Sensors.o random_selection.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Creature.o Milieu.o random_selection.o Accessories.o Sensors.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Creature.o : Creature.h Creature.cpp
	g++ -Wall -std=c++11  -c Creature.cpp -I .


Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

Behaviour.o : Behaviour.h Behaviour.cpp
	g++ -Wall -std=c++11 -c Behaviour.cpp -I .


Accessories.o : Accessories.h Accessories.cpp
	g++ -Wall -std=c++11 -c Accessories.cpp -I .

Sensors.o : Sensors.h Sensors.cpp
	g++ -Wall -std=c++11 -c Sensors.cpp -I .

random_selection.o : random_selection.cpp
	g++ -Wall -std=c++11 -c random_selection.cpp -I .


clean:
	rm *.o


