#include "Creature.h"
#include "Milieu.h"
#include <array>
#include <cstdlib>
#include <cmath>
#include <memory>


const double Creature::AFF_SIZE = 8.;
const double Creature::MAX_VITESSE = 10.;
const double Creature::dt = 1;

int Creature::next = 0;

Creature::Creature(Milieu* milieu):m_milieu(*milieu)
{

    id = ++next;
   creature_size = AFF_SIZE;
   cout << "const Creature (" << id << ") par defaut" << endl;
   accessories = std::unique_ptr<Accessories>(new Accessories());
   sensors = std::unique_ptr<Sensors>(new Sensors());
   behaviour = std::unique_ptr<InterfaceBehaviour>(new GregariousBehaviour());

   cout <<"Speed Coef " << accessories->speedCoef() <<endl;
   couleur = new T[3];
   couleur[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
   couleur[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
   couleur[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);

   //hitbox-taille

   taille_a = 3;
   taille_b = 3;

}
Creature &Creature::operator=(const Creature &c) {
    id = c.id;
    vitesse = Vector(c.vitesse);
    hitbox = CircleHitbox(c.hitbox);
    creature_size = c.creature_size;
    taille_a = c.taille_a;
    taille_b = c.taille_b;

    couleur = new T[3];
    memcpy(couleur, c.couleur, 3 * sizeof(T));
    accessories = std::unique_ptr<Accessories>(new Accessories(*c.accessories));
    sensors = std::unique_ptr<Sensors>(new Sensors(*c.sensors));
    behaviour = (*c.behaviour).clone();
    return *this;
}

Creature::Creature(const Creature &b):m_milieu(b.m_milieu)
{

    id = ++next;

   cout << "const Creature (" << id << ") par copie" << endl;
   position = Vector(b.position);
   m_milieu  = b.m_milieu;
   creature_size = AFF_SIZE * (0.5+static_cast<double>(rand())/RAND_MAX);
   vitesse = b.vitesse;
   accessories = std::unique_ptr<Accessories>(new Accessories(*b.accessories));
   sensors = std::unique_ptr<Sensors>(new Sensors(*b.sensors));
   behaviour = (*b.behaviour).clone();
   couleur = new T[3];
   memcpy(couleur, b.couleur, 3 * sizeof(T));
}

Creature::~Creature(void)
{

   delete[] couleur;

   cout << "dest Creature" << endl;
}

void Creature::initCoords(int xLim, int yLim)
{
    position = Vector(rand() % xLim, rand() % yLim);
}

void Creature::move(int xLim, int yLim)
{

   // calculate new position
   Vector dV = vitesse * dt ;
   Vector new_position = position + dV;
   // handle box collisions
   if ((new_position.x < 0) || (new_position.x > xLim - 1))
   {
      vitesse.reflectY();
   }
   if ((new_position.y < 0) || (new_position.y > yLim - 1))
   {
      vitesse.reflectX();
   }
    // align to grid
   new_position.x = static_cast<int>(new_position.x);
   new_position.y = static_cast<int>(new_position.y);

   position = new_position;
}

void Creature::action(Milieu &monMilieu)
{

    move(monMilieu.getWidth(), monMilieu.getHeight());
}
double Creature::getSize() const
{
   return creature_size;
};

void Creature::draw(UImg &support)
{
   double xt = position.x + cos(vitesse.orientation()) * creature_size / 2.1;
   double yt = position.y - sin(vitesse.orientation()) * creature_size / 2.1;
   unsigned char white[] = {255,255,255};
   support.draw_ellipse(position.x, position.y, creature_size, creature_size / 5., -vitesse.orientation() / M_PI * 180., couleur);
   support.draw_circle(xt, yt, creature_size / 2., couleur);
   support.draw_circle(xt, yt, creature_size / 6., white);
}

bool operator==(const Creature &b1, const Creature &b2)
{
   return (b1.id == b2.id);
}


Vector Creature::getPos() const
{
   return {position};
};

double Creature::getOrient() const
{
   return vitesse.orientation();
};

int Creature::getId() const
{
   return id;
};

CircleHitbox Creature::getHitbox(void) const
{
   return {hitbox};
};

void Creature::collision(void) 
{
   vitesse.rotate(M_PI);
};

void Creature::setOrient(double ori) 
{
   vitesse.rotate(ori - vitesse.orientation());
};







// void Creature::update_hitbox(void)
// {
//    double angles[8];
//    for (int i = 0; i < 8; i++) {
//       angles[i] = i*2*M_PI/8;
//    }

//    double e = sqrt((pow(taille_a,2)-pow(taille_b,2))/taille_a);
//    for (int i = 0; i < 8; i++) {
//       double a = angles[i];
//       double r_0 = sqrt(taille_b/(1 - e*pow(cos(a),2)));

//       hitbox[i][0] = x + int(r_0*cos(orientation + a));
//       hitbox[i][1] = y + int(r_0*sin(orientation + a));
//    }

// }