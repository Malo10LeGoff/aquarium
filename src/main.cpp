#include "Aquarium.h"
#include "Milieu.h"
#include "Creature.h"
#include "Sensors.h"
#include "Accessories.h"
#include <iostream>

using namespace std;


int main()
{
/*    Aquarium  ecosysteme( 640, 480, 30 );
   Creature c = Creature(& ecosysteme.getMilieu());
   for (int i=0;i<8;++i){
      cout << "HB1 x: "<<c.getHitbox()[i][0] <<endl;
      cout << "HB1 y: "<<c.getHitbox()[i][1] <<endl;
   }
   c.setOrient(M_PI);
   for (int i=0;i<8;++i){
      cout << "HB2 x: "<<c.getHitbox()[i][0] <<endl;
      cout << "HB2 y: "<<c.getHitbox()[i][1] <<endl;
   }*/

   Aquarium  ecosysteme( 640, 480, 30 );
   for ( int i = 1; i <= 20; ++i )
      ecosysteme.getMilieu().addRandomMember();
   ecosysteme.run();


   return 0;

}
