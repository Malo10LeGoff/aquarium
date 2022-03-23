#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "../lib/UImg.h"
#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include "CreatureBuilder.h"
using namespace std;


class Milieu : public UImg
{

private :
   static const T          white[];

   int                     width, height;
   std::vector<std::unique_ptr<Creature>>   listeCreatures;
   CreatureBuilder builder;
   std::vector<int> creaturesToKill {}; // vector of ids of the creatures to kill

public :
   Milieu( int _width, int _height );
   ~Milieu();

   int getWidth() const { return width; };
   int getHeight() const { return height; };

   void step();
   void creatureDetectSurroundings();
   void moveCreatures();
   void draw();
   void killCreatures();

   void handleCreatureCollision(void);
   void addMember( std::unique_ptr<Creature>& b ) ;
   void addRandomMember();
   int getNbCreatures(void);
   bool detect(const Creature &a, const Creature &b);
   std::vector<array<Vector,2>> surrounding(const Creature &a);

   void addCreatureToKill(int i);

    void ageCreature();
};


#endif
