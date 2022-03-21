#include "Creature.h"

#include "Milieu.h"
#include "Accessories.h"
#include "Behaviour.h"
#include <array>
#include <cstdlib>
#include <cmath>
#include <memory>

const double Creature::AFF_SIZE = 8.;
const double Creature::MAX_VITESSE = 10.;
const double Creature::LIMITE_VUE = 30.;

int Creature::next = 0;

Creature::Creature(Milieu* milieu):m_milieu(*milieu)
{

   identite = ++next;
   creature_size = AFF_SIZE;
   cout << "const Creature (" << identite << ") par defaut" << endl;
   x = y = 0;
   cumulX = cumulY = 0.;
   age = 1;
   lifetime_duration = rand() % 300 + 500;
   orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
   accessories = std::unique_ptr<Accessories>(new Accessories());
   sensors = std::unique_ptr<Sensors>(new Sensors());
   behaviour = std::unique_ptr<InterfaceBehaviour>(new GregariousBehaviour());

   cout <<"Speed Coef " << accessories->speedCoef() <<endl;
   vitesse = std::min(static_cast<double>(rand()) / RAND_MAX * MAX_VITESSE + accessories->speedCoef(), MAX_VITESSE);
   collision_resistance = std::min(static_cast<double>(rand()/RAND_MAX + accessories->deathCoef()),1.0);
   cout << vitesse <<endl;
   couleur = new T[3];
   couleur[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
   couleur[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
   couleur[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);

   //hitbox-taille

   taille_a = 3;
   taille_b = 3;
}
Creature &Creature::operator=(const Creature &c) {
    identite = c.identite;
    x = c.x;
    y = c.y;
    age = c.age;
    lifetime_duration = c.lifetime_duration;
    cumulX = c.cumulX;
    cumulY = c.cumulY;
    orientation = c.orientation;
    collision_resistance = c.collision_resistance;
    vitesse = c.vitesse;
    hitbox = std::vector<std::array<double,2>> (c.hitbox);
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

   identite = ++next;

   cout << "const Creature (" << identite << ") par copie" << endl;

   x = b.x;
   y = b.y;
   m_milieu  = b.m_milieu;
   creature_size = AFF_SIZE * (0.5+static_cast<double>(rand())/RAND_MAX);
   cumulX = cumulY = 0.;
   age = 1;
   collision_resistance = b.collision_resistance;
   lifetime_duration = b.lifetime_duration;
   orientation = b.orientation;
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

   x = rand() % xLim;
   y = rand() % yLim;
}


double Creature::getResistanceCollision() const
{
   return collision_resistance;
}


void Creature::bouge(int xLim, int yLim)
{
   age +=1;
   double nx, ny;
   double dx = cos(orientation) * vitesse;
   double dy = -sin(orientation) * vitesse;
   int cx, cy;

   cx = static_cast<int>(cumulX);
   cumulX -= cx;
   cy = static_cast<int>(cumulY);
   cumulY -= cy;

   nx = x + dx + cx;
   ny = y + dy + cy;

   if ((nx < 0) || (nx > xLim - 1))
   {
      orientation = M_PI - orientation;
      cumulX = 0.;
   }
   else
   {
      x = static_cast<int>(nx);
      cumulX += nx - x;
   }

   if ((ny < 0) || (ny > yLim - 1))
   {
      orientation = -orientation;
      cumulY = 0.;
   }
   else
   {
      y = static_cast<int>(ny);
      cumulY += ny - y;
   }
}

void Creature::action(Milieu &monMilieu)
{
   bouge(monMilieu.getWidth(), monMilieu.getHeight());
};

bool Creature::DieFromeAging()
{
   return age >= lifetime_duration;
};

double Creature::getSize() 
{
   return creature_size;
};

void Creature::draw(UImg &support)
{
   double xt = x + cos(orientation) * creature_size / 2.1;
   double yt = y - sin(orientation) * creature_size / 2.1;
   unsigned char white[] = {255,255,255};
   unsigned char black[] = {0,0,0};
   unsigned char red[] = {255,0,0};
   unsigned char green[] = {0,255,0};
   int opacity = 1;


   std::list<InterfaceAccessory *> access = accessories->accessories_;
   std::list<InterfaceAccessory *>::const_iterator it;
   for (it=access.begin();it!= access.end();it++) {
      if ((*it)->AccessoryType()==1)
      {
         support.draw_circle(xt, yt, creature_size*1.3, red);
      }
      if ((*it)->AccessoryType()==2)
      {
         support.draw_ellipse(x, y, creature_size*1.3, creature_size / 3.5, -orientation / M_PI * 180., green);
      }
      if ((*it)->AccessoryType()==3)
      {
         support.draw_ellipse(x, y, creature_size, creature_size / 5., (-orientation+M_PI/2) / M_PI * 180., behaviour->getColor());
      }
   }

   support.draw_ellipse(x, y, creature_size, creature_size / 5., -orientation / M_PI * 180., behaviour->getColor(),opacity);
   support.draw_circle(xt, yt, creature_size / 2., behaviour->getColor(),opacity);
}

bool operator==(const Creature &b1, const Creature &b2)
{
   return (b1.identite == b2.identite);
}


int * Creature::getPos() const
{
   int  pos[2];
   pos[0] = x;
   pos[1] = y;
   return pos;
};

double Creature::getOrient() const
{
   return orientation;
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
   return identite;
};

std::vector<std::array<double,2>> Creature::getHitbox(void)
{
   return hitbox;
};

void Creature::collision(void) 
{
   orientation = orientation+M_PI;
};

void Creature::setOrient(double ori) 
{
   orientation = ori;
};

double Creature::getXt(void){
   double xt = x + cos(orientation) * creature_size / 2.1;
   return xt;
};

double Creature::getYt(void){
   double yt = y - sin(orientation) * creature_size / 2.1;
   return yt;
}







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