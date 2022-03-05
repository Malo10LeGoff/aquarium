#include "Creature.h"

#include "Milieu.h"
#include "Accessories.h"

#include <cstdlib>
#include <cmath>

const double Creature::AFF_SIZE = 8.;
const double Creature::MAX_VITESSE = 10.;
const double Creature::LIMITE_VUE = 30.;

int Creature::next = 0;

Creature::Creature(void)
{

   identite = ++next;

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
   

}

Creature::Creature(const Creature &b)
{

   identite = ++next;

   cout << "const Creature (" << identite << ") par copie" << endl;

   x = b.x;
   y = b.y;
   cumulX = cumulY = 0.;
   orientation = b.orientation;
   vitesse = b.vitesse;
   accessories = b.accessories;
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

void Creature::draw(UImg &support)
{

   double xt = x + cos(orientation) * AFF_SIZE / 2.1;
   double yt = y - sin(orientation) * AFF_SIZE / 2.1;

   support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5., -orientation / M_PI * 180., couleur);
   support.draw_circle(xt, yt, AFF_SIZE / 2., couleur);
}

bool operator==(const Creature &b1, const Creature &b2)
{

   return (b1.identite == b2.identite);
}

bool Creature::jeTeVois(const Creature &b) const
{
   double dist;
   dist = std::sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
   return (dist <= LIMITE_VUE);
}
