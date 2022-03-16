main : main.cpp Aquarium.o Creature.o Milieu.o Accessories.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Creature.o Milieu.o Accessories.o Sensors.cpp -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Creature.o : Creature.h Creature.cpp
	g++ -Wall -std=c++11  -c Creature.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

Accessories.o : Accessories.h Accessories.cpp
	g++ -Wall -std=c++11 -c Accessories.cpp -I .

Sensors.o : Sensors.h Sensors.cpp
	g++ -Wall -std=c++11 -c Sensors.cpp -I .
clean:
	rm *.o



