#ifndef _CREATURES_H_
#define _CREATURES_H_


#include "../lib/UImg.h"
#include "Accessories.h"
#include "Sensors.h"
#include "Behaviour.h"
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
   static const double     LIMITE_VUE;

   static int              next;

private :
   int               identite;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   double            creature_size;
   T                 * couleur;
   Milieu & m_milieu;
   std::array<std::array<int,2>,8> hitbox;
   int               taille_a;
   int               taille_b;
public:
   std::unique_ptr<Accessories>       accessories;
   std::unique_ptr<Sensors>           sensors;
   std::unique_ptr<InterfaceBehaviour> behaviour;
   
private :
   void bouge( int xLim, int yLim );
  

public :                                           // Forme canonique :
   Creature( Milieu* t_milieu );                               // Constructeur par defaut
   Creature( const Creature & b );                 // Constructeur de copies
   ~Creature( void );                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );
   void collision(void);
   void update_hitbox(void);
   void initCoords( int xLim, int yLim );

   int * getPos() const;
   int getId() const;
   double getXt() ;
   double getYt() ;
   double getSize();
   double getOrient() const;
   void setOrient(double ori);
   std::array<std::array<int,2>,8> getHitbox(void);
   double parseEnvironement(std::list<Creature> clist);
   friend bool operator==( const Creature & b1, const Creature & b2 );

};


#endif
