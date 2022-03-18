#include "Creature.h"

#include "Milieu.h"
#include "Accessories.h"
#include <array>
#include <cstdlib>
#include <cmath>

const double Creature::AFF_SIZE = 8.;
const double Creature::MAX_VITESSE = 10.;
const double Creature::LIMITE_VUE = 30.;

int Creature::next = 0;

Creature::Creature(void)
{

   identite = ++next;
   creature_size = AFF_SIZE;
   cout << "const Creature (" << identite << ") par defaut" << endl;
   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;

   accessories = Accessories();
   sensors = Sensors();

   cout <<"Speed Coef " << accessories.speedCoef() <<endl;
   vitesse = std::min(static_cast<double>(rand()) / RAND_MAX * MAX_VITESSE + accessories.speedCoef(), MAX_VITESSE);
   cout << vitesse <<endl;
   couleur = new T[3];
   couleur[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
   couleur[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
   couleur[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);

   //hitbox-taille

   taille_a = 3;
   taille_b = 3;

}

Creature::Creature(const Creature &b)
{

   identite = ++next;

   cout << "const Creature (" << identite << ") par copie" << endl;

   x = b.x;
   y = b.y;
   creature_size = AFF_SIZE * (0.5+static_cast<double>(rand())/RAND_MAX);
   cumulX = cumulY = 0.;
   orientation = b.orientation;
   vitesse = b.vitesse;
   accessories = b.accessories;
   sensors = b.sensors;
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

void Creature::bouge(int xLim, int yLim)
{

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
}
double Creature::getSize() 
{
   return creature_size;
};

void Creature::draw(UImg &support)
{
   double xt = x + cos(orientation) * creature_size / 2.1;
   double yt = y - sin(orientation) * creature_size / 2.1;
   unsigned char white[] = {255,255,255};
   support.draw_ellipse(x, y, creature_size, creature_size / 5., -orientation / M_PI * 180., couleur);
   support.draw_circle(xt, yt, creature_size / 2., couleur);
   support.draw_circle(xt, yt, creature_size / 6., white);
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

int Creature::getId() const
{
   return identite;
};

std::array<std::array<int,2>,8> Creature::getHitbox(void) 
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