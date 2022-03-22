#include "Creature.h"
#include "Milieu.h"
#include <array>
#include <cstdlib>
#include <cmath>
#include <memory>
#include "constants.h"

const double Creature::AFF_SIZE = baseSize;
const double Creature::MAX_VITESSE = baseSpeed;
const double Creature::dt = time_delta;

int Creature::next = 0;

Creature::Creature(Milieu* milieu):m_milieu(*milieu)
{
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
    speed = Vector(c.speed);
    hitbox = CircleHitbox(c.hitbox);
    age = c.age;
    lifetime_duration = c.lifetime_duration;
    collision_resistance = c.collision_resistance;
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

   cout << "const Creature (" << id << ") par copie" << endl;
   position = Vector(b.position);
   creature_size = b.creature_size;
   speed = b.speed;
   creature_size = AFF_SIZE * (0.5+static_cast<double>(rand())/RAND_MAX);
   age = 1;
   collision_resistance = b.collision_resistance;
   lifetime_duration = b.lifetime_duration;
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

double Creature::getResistanceCollision() const
{
    return collision_resistance;
}

void Creature::move() {
   // calculate new position
   Vector dV = speed * dt ;
   Vector new_position = position + dV;
    // align to grid
   new_position.alignToGrid();


   position = new_position;
}

void Creature::onMove(Milieu &monMilieu)
{
    // Get the speed that the behaviour gives
    speed = behaviour->moveDirection(position, visibleCreatures);
    // Once all that is done actually update the position of the creature
    move( );
}

bool Creature::dieFromeAging() const
{
   return age >= lifetime_duration;
};

double Creature::getSize() const
{
   return creature_size;
};

void Creature::draw(UImg &support)
{
    // TODO :
   double xt = position.x + cos(speed.orientation()) * creature_size / 2.1;
   double yt = position.y - sin(speed.orientation()) * creature_size / 2.1;
   unsigned char white[] = {255,255,255};
   support.draw_ellipse(position.x, position.y, creature_size, creature_size / 5., -speed.orientation() / M_PI * 180., couleur);
   support.draw_circle(xt, yt, creature_size / 2., couleur);
   support.draw_circle(xt, yt, creature_size / 6., white);
   unsigned char black[] = {0,0,0};
   unsigned char red[] = {255,0,0};
   unsigned char green[] = {0,255,0};
   int opacity = 1;
   for (auto const &it :accessories->accessories_) {
      if (it->AccessoryType()==1)
      {
         support.draw_ellipse(position.x, position.y, creature_size*2, creature_size, (-getOrient()) / M_PI * 180., red, 0.6);
      }
      if (it->AccessoryType()==2)
      {
         support.draw_ellipse(position.x, position.y, creature_size*1.4, creature_size / 3, -getOrient() / M_PI * 180., green);
      }
      if (it->AccessoryType()==3)
      {
         support.draw_ellipse(position.x, position.y, creature_size, creature_size / 5., (-getOrient()+M_PI/2) / M_PI * 180., behaviour->getColor());
      }
   }

   support.draw_ellipse(position.x, position.y, creature_size, creature_size / 5., -getOrient() / M_PI * 180., behaviour->getColor(),opacity);
   support.draw_circle(position.x, position.y, creature_size / 2., behaviour->getColor(),opacity);
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
   return speed.orientation();
};

int Creature::getAge() const
{
   return age;
};

int Creature::getLifetime() const
{
   return lifetime_duration;
};

int Creature::getId() const
{
   return id;
};

CircleHitbox Creature::getHitbox(void) const
{
   return {hitbox};
};

void Creature::onCollision(int xLim, int yLim){
// handle box collisions
    if ((new_position.x < 0) || (new_position.x > xLim )){
    speed.reflectY();
    }
    if ((new_position.y < 0) || (new_position.y > yLim))
    {
    speed.reflectX();
    }
    //todo : calculate whether the creature should die
   speed.rotate(M_PI);
};

void Creature::setOrient(double ori) 
{
   speed.rotate(ori - speed.orientation());
}

void Creature::setPos(Vector v) {
    position = v;
}

void Creature::setSpeed(Vector v) {
    speed = v;
}

void Creature::clip(int xlim, int ylim) {
    position.clip(0, xlim, 0, ylim);
}

void Creature::detectSurroundings() {
    visibleCreatures = m_milieu.surroundings(*this);
}

bool operator!=(const Creature &b1, const Creature &b2) {
    return !(b1 == b2);
}

void Creature::onAge() {
    ++age;
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