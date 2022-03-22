#include "Aquarium.h"
#include "Milieu.h"
#include "Creature.h"
#include "Sensors.h"
#include "Accessories.h"
#include <iostream>

using namespace std;


int main()
{

   /*
   Aquarium  ecosysteme( 640, 480, 30 );
   for ( int i = 1; i <= 20; ++i )
      ecosysteme.getMilieu().addRandomMember();
   ecosysteme.run();
   */
   

  
   Aquarium ecosysteme( 640, 480, 30 );

   Creature a = Creature(&ecosysteme.getMilieu());
   Creature b = Creature(&ecosysteme.getMilieu());

   a.setPos(Vector {10,10});
   b.setPos(Vector {30,10});

   a.setSpeed(Vector {10,0});
   b.setSpeed(Vector {0,0});

   cout << a.getPos().x <<" "<< a.getPos().y << endl;
   cout << a.getSpeed().x <<" "<< a.getSpeed().y << endl;
   std::unique_ptr<InterfaceSensors> s = std::unique_ptr<Ears>(new Ears(1,1000));
   a.sensors->add(s);

   cout << a.sensors->sensors_.size() << endl;
   bool test = ecosysteme.getMilieu().detect(a,b);

   if (test) {
      cout <<"Creature a detected b" <<endl;
   }
   else {
      cout <<"No detection"<<endl;
   }
   
   return 0;

}
