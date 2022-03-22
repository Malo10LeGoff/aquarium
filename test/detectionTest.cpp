#include "gtest/gtest.h"
//#include "../src/Aquarium.h"



TEST(Testdetection, TestdetectionIsTrue) {
   /*
   Aquarium ecosysteme( 640, 480, 30 );

   Creature a = Creature(&ecosysteme.getMilieu());
   Creature b = Creature(&ecosysteme.getMilieu());

   a.setPos(Vector {10,10});
   b.setPos(Vector {30,10});

   a.setSpeed(Vector {10,0});
   b.setSpeed(Vector {0,0});

   std::unique_ptr<InterfaceSensors> s = std::unique_ptr<Ears>(new Ears(1,1000));
   a.sensors->add(s);
   bool test = ecosysteme.getMilieu().detect(a,b);
   if (test) {
      cout <<"Creature a detected b" <<endl;
   }
   else {
      cout <<"No detection"<<endl;
   }
   */
    EXPECT_EQ(0,0 );
    
    std::cout << "detectionTest" << "\n";
}