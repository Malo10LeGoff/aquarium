#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <math.h> 
#include <array>

const T Milieu::white[] = {(T)255, (T)255, (T)255};

Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3),
                                          width(_width), height(_height)
{

   cout << "const Milieu" << endl;
   std::srand(time(NULL));
}

Milieu::~Milieu(void)
{

   cout << "dest Milieu" << endl;
}

void Milieu::step(void)
{
   cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

   for (std::vector<Creature>::iterator it = listeCreatures.begin(); it != listeCreatures.end(); ++it)
   {

      it->action(*this);
      it->draw(*this);

   } // for
   collision();
}

int Milieu::nbVoisins(const Creature &b)
{
   int nb = 0;

   for (std::vector<Creature>::iterator it = listeCreatures.begin(); it != listeCreatures.end(); ++it)
      if (!(b == *it) && detect(b,*it))
         ++nb;

   return nb;
};


//marche pas
std::vector<std::array<int,2>> Milieu::Surrounding(const Creature &a)
{
   
   std::vector<std::array<int,2>> res;

   for (std::vector<Creature>::iterator it = listeCreatures.begin(); it != listeCreatures.end(); ++it)
      if (!(a == *it) && detect(a,*it)) 
      {
         int * pos_tmp = (it)->getPos(); 
         std::array<int,2> pos;
         pos[0] = pos_tmp[0];
         pos[1] = pos_tmp[1];
         res.push_back(pos);
      }
   return res;
};




bool Milieu::detect(const Creature &a, const Creature &b)
{
   std::list<InterfaceSensors *>::const_iterator it;
   for (it=a.sensors.sensors_.begin();it!= a.sensors.sensors_.end();it++) {
         double dist;
         int * pos_a = a.getPos();
         int * pos_b = b.getPos();
         double orientation = a.getOrient();

         dist = std::sqrt((pos_a[0] - pos_b[0]) * (pos_a[0] - pos_b[0]) + (pos_a[1] - pos_b[1]) * (pos_b[1] - pos_b[1]));
        
         if (dist <= (*it)->getDetectionRadius()) {
            if ((*it)->getType()=="Ears") {
               return 1;
            } else {
               int new_x_b = static_cast<int>(pos_b[0]*std::cos(orientation) + pos_b[1]*std::sin(orientation) - pos_a[0]);
               int new_y_b = static_cast<int>(-pos_b[0]*std::sin(orientation) + pos_b[1]*std::cos(orientation)- pos_a[1]);

               double alpha = std::atan (new_y_b/new_x_b);

               if (std::abs(alpha)<(*it)->getDetectionAngle()) {
                  return 1;
               };
            }
         }
      }
   return 0;
}


void Milieu::collision(void)
{
   for (std::vector<Creature>::iterator it_i = listeCreatures.begin(); it_i != listeCreatures.end(); ++it_i) {
      for (std::vector<Creature>::iterator it_j = listeCreatures.begin(); it_j != listeCreatures.end(); ++it_j) {
      if (it_j!=it_i) {
         double x_i = (it_i)->getXt();
         double y_i = (it_i)->getYt();
         double x_j = (it_j)->getXt();
         double y_j = (it_j)->getYt();
         double size_i = (it_i)->getSize();
         double size_j = (it_j)->getSize();
         double dist = std::sqrt((x_i - x_j)*(x_i - x_j) + (y_i - y_j)*(y_i - y_j));
         if (dist<(size_i+size_j)){
            cout << "Collision" << endl;
            (it_j)->collision();
            (it_i)->collision();
         }
      }
   }}
}