#ifndef _CREATURES_H_
#define _CREATURES_H_


#include "UImg.h"

#include <iostream>

using namespace std;


class Milieu;


class Creature
{

private :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;

   static int              next;

private :
   int               identite;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;

   T               * couleur;

private :
   void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
   Creature( void );                               // Constructeur par defaut
   Creature( const Creature & b );                 // Constructeur de copies
   ~Creature( void );                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );
   tuple<float,float> coordinates() const;
   bool jeTeVois( const Creature & b ) const;

   void initCoords( int xLim, int yLim );

   friend bool operator==( const Creature & b1, const Creature & b2 );

};


#endif
