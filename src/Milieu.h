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

public :
   Milieu( int _width, int _height );
   ~Milieu( void );

   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );
   void collision(void);
   void addMember( std::unique_ptr<Creature>& b ) ;
   void addRandomMember();
   int getNbCreatures(void);
   int nbVoisins( const Creature & b );
   bool detect(const Creature &a, const Creature &b);
   bool detection(const Creature &a, const Creature &b);
   std::vector<Vector> Surrounding(const Creature &a);

};


#endif
