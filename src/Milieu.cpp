#include "Milieu.h"
#include "Sensors.h"
#include "../lib/Vector.h"
#include <cstdlib>
#include <ctime>
#include <memory>

const T Milieu::white[] = {(T)255, (T)255, (T)255};

Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3),
                                          width(_width), height(_height), builder(CreatureBuilder(*this))
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
    //move creatures
    // // calculate creature collisions
   cimg_forXY(*this, x, y) fillC(x, y, 0, 50, 100, 255);
   auto it = listeCreatures.begin();
   while (it != listeCreatures.end())
   {
      cout << (*it)->getAge() << " " <<(*it)->getLifetime() << endl;
      cout << (*it)->dieFromeAging() << endl;
      if ((*it)->dieFromeAging())
      {
         cout <<"Creature "<<(*it)->getId() << " died from aging"<<endl;
         listeCreatures.erase(it);
      }
      else 
      {
       
         cout<<"moving"<<endl;
          (*it)->onMove(*this);
         (*it)->draw(*this);
         it++; 
                           
      }
   } // for
   collision();
}


int Milieu::nbVoisins(const Creature &b)
{
   int nb = 0;

   for (auto const & creature : listeCreatures )
      if (!(b == *creature) && detect(b,*creature))
         ++nb;

   return nb;
};

int Milieu::getNbCreatures()
{
   return listeCreatures.size();
}

//marche pas
std::vector<Vector> Milieu::Surrounding(const Creature &a)
{

   std::vector<Vector> res;

   for (auto const& creature: listeCreatures)
      if (!(a == *creature) && detect(a,*creature))
      {
         Vector pos_tmp = creature->getPos();
         res.push_back(pos_tmp);
      }
   return res;
};


bool Milieu::detect(const Creature &a, const Creature &b)
{
   for (auto const& sensor : a.sensors->sensors_) {
         double dist;
         Vector pos_a = a.getPos();
         Vector pos_b = b.getPos();

      }
   return true;
}



void Milieu::collision(void) {
    std::vector<int> tmp_vector{};
    for (auto &creature_i: listeCreatures) {
        for (auto &creature_j: listeCreatures) {
            if (creature_i->getId() != creature_j->getId()) {
                if (creature_j->getHitbox().isColliding(creature_i->getHitbox())) {
                    cout << "Collision" << endl;
                    creature_i->onCollision();
                    creature_j->onCollision();
                    //does creatures survive onCollision
                    cout << (double) std::rand() / RAND_MAX << endl;
                    if ((double) std::rand() / RAND_MAX > creature_i->getResistanceCollision()) {
                        tmp_vector.push_back((creature_i->getId()));
                    }
                }
            }
        }
    }
    auto it = listeCreatures.begin();
    while (it != listeCreatures.end())
    {
        if (std::find(tmp_vector.begin(), tmp_vector.end(), (*it)->getId()) != tmp_vector.end())
        {
            cout << "Creature " << (*it)->getId() << " died from onCollision" << endl;
            listeCreatures.erase(it);
        }
        else
        {
            ++it;
        }
    }

}
void Milieu::addMember(std::unique_ptr<Creature>& b) {
    listeCreatures.push_back(std::move(b));
}

void Milieu::addRandomMember() {
    std::shared_ptr<RandomBuilder> b = std::make_shared<RandomBuilder> (builder);
    builder.setBuilder(b);
    std::unique_ptr<Creature> randomCreature = builder.make();
    addMember(randomCreature);
}

void Milieu::moveCreatures() {
    for (auto & creature : listeCreatures) {
        creature->onMove(*this);
    }
}

void Milieu::detectSurroundings() {
    for (auto & creature : listeCreatures){
        creature->detectSurroundings();
    }
}

std::vector<array<Vector, 2>> Milieu::getSurroundings(Creature& creature) {
    std::vector<array<Vector,2>> ret {} ;
    for (auto & creature_i: listeCreatures) {
        if (creature != *creature_i && detect(creature, *creature_i)) {
            ret.push_back(std::array<Vector,2>{creature_i->previous_speed, creature_i->getPos()});
        }
    }
    return ret;
}


