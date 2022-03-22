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
    // Detect surroundings
    creatureDetectSurroundings();
    // move creatures
    moveCreatures();
    // handle creature collisions
    handleCreatureCollision();
    //draw
    draw();
}


int Milieu::getNbCreatures()
{
   return listeCreatures.size();
}

std::vector<array<Vector,2>> Milieu::surrounding(const Creature &a)
{

   std::vector<array<Vector,2>> res {};

   for (auto const& creature: listeCreatures)
      if ((a != *creature) && detect(a,*creature))
      {
         
         Vector pos_tmp = creature->getPos();
         Vector speed  = creature->getSpeed();
         array<Vector,2> tmp_ar  {speed,pos_tmp};
         res.push_back(tmp_ar);
      }
   return res;
};


bool Milieu::detect(const Creature &a, const Creature &b)
{

      Vector pos_a = a.getPos();
      Vector pos_b = b.getPos();
      
      double alpha_2 = (pos_b-pos_a).orientation();
      if (alpha_2 > M_PI)
         {
            alpha_2 = std::abs(alpha_2 - 2*M_PI);
         }
      double alpha_1 = a.getSpeed().orientation();
      double dist_a_b = distanceVectors(pos_a,pos_b);
      std::vector<detection_caract> detectionZones = a.sensors->getDetectionZone(); // [ [detectionCoef, detectionRadius, DetectionAngle], ...]
      for (auto const & detectionZone :detectionZones) {
         if ((detectionZone[1]>dist_a_b) && (detectionZone[3]/2 > std::abs(alpha_2 - alpha_1)) && (detectionZone[0]>b.getCamoCoef()))
            {
               return true;
            }
      }
         
      
   return false;
}



void Milieu::handleCreatureCollision(void) {
    std::vector<int> tmp_vector{};
    for (auto &creature_i: listeCreatures) {
        for (auto &creature_j: listeCreatures) {
            if (creature_i->getId() != creature_j->getId()) {
                if (creature_j->getHitbox().isColliding(creature_i->getHitbox())) {
                    cout << "Coli" << endl;
                    creature_i->onCreatureCollision();
                    //creature_j->onCreatureCollision();
                }
            }
        }
    }

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

void Milieu::moveCreatures() {
    for (auto & creature : listeCreatures) {
        creature->onMove(*this);
    }
}

void Milieu::creatureDetectSurroundings() {
    for (auto & creature : listeCreatures){
        creature->detectSurroundings();
    }
}


void Milieu::addCreatureToKill(int i) {
    creaturesToKill.push_back(i);
}

void Milieu::draw() {
    cimg_forXY(*this, x, y) fillC(x, y, 0, 50, 100, 255);
    for (auto& creature: listeCreatures) {
        creature->draw(*this);
    }
}


