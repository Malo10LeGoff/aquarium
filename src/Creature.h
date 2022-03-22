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
#include "constants.h"

using namespace std;


class Milieu;


class Creature
{

private :
   static const double     AFF_SIZE;
   static int              next;
   static const double            dt;

private :
   Vector position {0,0};
   Vector            speed;
   double   baseSpeed = 1;
   CircleHitbox hitbox {position, 1};
   double            creature_size;
   T                 * couleur;
   Milieu & m_milieu;
   double            baseDeathProbOnCollision = 0.05;
   double baseCamoCoef = baseCreatureCamoCoef;
   std::vector<std::array<Vector,2>> visibleCreatures {};
   int               taille_a = Creature::AFF_SIZE;
   int               taille_b = Creature::AFF_SIZE;
   int               lifetime_duration= rand()%300 + 500;
   int               age = 0;
public:
   int               id = -1;
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
   void handleWallCollision(int xLim, int yLim);
   void onCreatureCollision();
   void onCollide(int xlim, int ylim);
   void onAge();
   void draw( UImg & support );



   Vector getPos() const;
    void setPos(Vector v);
    Vector getSpeed() const;
    void setSpeed(Vector vector);
    double getBaseSpeed() const {return baseSpeed;};
    void setBaseSpeed(double t_baseSpeed) {baseSpeed = t_baseSpeed;}
    void setVisibleCreatures(std::vector<std::array<Vector,2>> t_visibleCreatures);
    std::vector<std::array<Vector,2>> getVisibleCreatures() const ;
    int getId() const;
    bool dieFromeAging(void) const;
    double getCollisionDeathProb() const;
    int getLifetime() const;
    int getAge() const;
    double getOrient() const;
    void setOrient(double ori);
    CircleHitbox getHitbox() const ;
    void updateHitboxPosition();
    double getSize() const ;
    void setSize(double s);

    friend bool operator==( const Creature & b1, const Creature & b2 );
    friend bool operator!=( const Creature & b1, const Creature & b2 );


    float getCamoCoef() const;
};


#endif
