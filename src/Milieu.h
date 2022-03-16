#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "../lib/UImg.h"
#include "Creature.h"

#include <iostream>
#include <vector>
#include <array>

using namespace std;


class Milieu : public UImg
{

private :
   static const T          white[];

   int                     width, height;
   std::vector<Creature>   listeCreatures;

public :
   Milieu( int _width, int _height );
   ~Milieu( void );

   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );

   void addMember( const Creature & b ) { listeCreatures.push_back(b); listeCreatures.back().initCoords(width, height); }
   int nbVoisins( const Creature & b );
   bool detect(const Creature &a, const Creature &b);
   std::vector<std::array<int,2>> Surrounding(const Creature &a);
   
};


#endif
