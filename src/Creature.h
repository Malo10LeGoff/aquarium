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
   Vector            speed;
   CircleHitbox hitbox {position, 1};
   double            creature_size;
   T                 * couleur;
   Milieu & m_milieu;
   double            collision_resistance;
   std::vector<std::array<Vector,2>> visibleCreatures {};
   int               taille_a;
   int               taille_b;
   int               lifetime_duration= 1000;
   int               age = 0;
public:
   int               id;
   std::unique_ptr<Accessories>       accessories;
   std::unique_ptr<Sensors>           sensors;
   std::unique_ptr<InterfaceBehaviour> behaviour;
   Vector previous_speed;
   
private :
    void move();

public :                                           // Forme canonique :
   explicit Creature( Milieu* t_milieu );                               // Constructeur par defaut
   Creature( const Creature & b );                 // Constructeur de copies
   ~Creature( void );                              // Destructeur
   Creature& operator=(const Creature& c);                              // Operateur d'affectation binaire par defaut
   void detectSurroundings() ;
   void onMove(Milieu & monMilieu );
   void onCollide(int xlim, int ylim);
   void onCreatureCollision(void);
   void onAge();
   void draw( UImg & support );



   Vector getPos() const;
   void setPos(Vector v);
   int getId() const;
   bool dieFromeAging(void) const;
   double getResistanceCollision() const;
   int getLifetime() const;
   int getAge() const;
   double getOrient() const;
   void setOrient(double ori);
   CircleHitbox getHitbox() const ;
    double getSize() const ;
    void setSpeed(Vector vector);
    void clip(int xlim, int ylim) ;

    friend bool operator==( const Creature & b1, const Creature & b2 );
    friend bool operator!=( const Creature & b1, const Creature & b2 );

};


#endif
