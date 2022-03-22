#include "Milieu.h"

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
   cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

   for (auto &creature : listeCreatures)
   {

      creature->action(*this);
      creature->draw(*this);

   } // for
   collision();
}



void Milieu::collision(void)
{
   for (auto &creature_i : listeCreatures) {
      for (auto &creature_j : listeCreatures) {
      if (creature_i->getId() != creature_j->getId()) {
         if (creature_j->getHitbox().isColliding( creature_i->getHitbox())){
            cout << "Collision" << endl;
            creature_i->collision();
            creature_j->collision();
         }
      }
   }}
}

void Milieu::addMember(std::unique_ptr<Creature>& b) {
    listeCreatures.push_back(std::move(b));
}

void Milieu::addRandomMember() {
    std::shared_ptr<BuilderInterface> b = std::make_shared<RandomBuilder> (builder);
    builder.setBuilder(b);
    std::unique_ptr<Creature> randomCreature = builder.make();
    addMember(randomCreature);
}
