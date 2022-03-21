#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "../lib/UImg.h"
#include "Creature.h"

#include <iostream>
#include <vector>
#include <array>
#include <memory>
using namespace std;


class Milieu : public UImg
{

private :
   static const T          white[];

   int                     width, height;
   std::vector<std::unique_ptr<Creature>>   listeCreatures;

public :
   Milieu( int _width, int _height );
   ~Milieu( void );

   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );
   void collision(void);
   void addMember( std::unique_ptr<Creature> b ) ;
   
};


#endif
