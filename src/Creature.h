#ifndef _CREATURES_H_
#define _CREATURES_H_


#include "../lib/UImg.h"
#include "Accessories.h"
#include "Sensors.h"
#include "Behaviour.h"
#include "../lib/Hitbox.h"
#include <list>
#include <memory>
#include <array>
#include <iostream>

using namespace std;


class Milieu;


class Creature
{

private :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static int              next;
   static const double            dt;

private :
   Vector position {0,0};
   Vector            vitesse;
   CircleHitbox hitbox {position, 1};
   double            creature_size;
   T                 * couleur;
   Milieu & m_milieu;
   int               taille_a;
   int               taille_b;
public:
   int               id;
   std::unique_ptr<Accessories>       accessories;
   std::unique_ptr<Sensors>           sensors;
   std::unique_ptr<InterfaceBehaviour> behaviour;
   
private :
   void move(int xLim, int yLim );
  

public :                                           // Forme canonique :
   explicit Creature( Milieu* t_milieu );                               // Constructeur par defaut
   Creature( const Creature & b );                 // Constructeur de copies
   ~Creature( void );                              // Destructeur
   Creature& operator=(const Creature& c);                                                // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );
   void collision(void);
   void initCoords( int xLim, int yLim );

   Vector getPos() const;
   int getId() const;
   double getOrient() const;
   void setOrient(double ori);
   CircleHitbox getHitbox() const ;
   friend bool operator==( const Creature & b1, const Creature & b2 );
    double getSize() const ;
};


#endif
