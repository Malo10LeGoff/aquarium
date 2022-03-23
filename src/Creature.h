#ifndef _CREATURES_H_
#define _CREATURES_H_


#include "../lib/UImg.h"
#include "Accessories.h"
#include "Sensors.h"
#include "Behaviour.h"
#include "../lib/Hitbox.h"
#include <list>
#include <memory>
#include <array>
#include <iostream>
#include "constants.h"

using namespace std;


class Milieu;


class Creature {

private :
    static const double AFF_SIZE;
    static int next;
    static const double dt;

private :
    Vector position{0, 0};
    Vector speed;
    double baseSpeed = 1;
    CircleHitbox hitbox{position, 1};
    T *couleur;
    Milieu &m_milieu;
    double baseDeathProbOnCollision = 0.05;
    double baseCamoCoef = baseCreatureCamoCoef;
    std::vector<std::array<Vector, 2>> visibleCreatures{};
    int m_dyingAge = minDyingAge;
    int age = 0;
public:
    int id = -1;
    std::unique_ptr<Accessories> accessories;
    std::unique_ptr<Sensors> sensors;
    std::unique_ptr<InterfaceBehaviour> behaviour;
    Vector previous_speed;

private :
    void move();

public :                                           // Forme canonique :
    explicit Creature(Milieu *t_milieu);                               // Constructeur par defaut
    Creature(const Creature &b);                 // Constructeur de copies
    ~Creature(void);                              // Destructeur
    Creature &operator=(const Creature &c);                              // Operateur d'affectation binaire par defaut
    void detectSurroundings();

    void onMove(Milieu &monMilieu);

    void handleWallCollision(int xLim, int yLim);

    void onCreatureCollision();

    void onAge();

    void draw(UImg &support);


    Vector getPos() const;

    void setPos(Vector v);

    Vector getSpeed() const;

    void setSpeed(Vector vector);

    double getBaseSpeed() const { return baseSpeed; };

    void setBaseSpeed(double t_baseSpeed) { baseSpeed = t_baseSpeed; }

    int getDyingAge() const;

    void setDyingAge(int i);

    void setVisibleCreatures(std::vector<std::array<Vector, 2>> t_visibleCreatures);

    std::vector<std::array<Vector, 2>> getVisibleCreatures() const;

    int getId() const;

    void setId(int id);

    double getCollisionDeathProb() const;

    int getAge() const;

    double getOrient() const;

    void setOrient(double ori);

    CircleHitbox getHitbox() const;

    void updateHitboxPosition();

    double getSize() const;

    void setSize(double s);

    friend bool operator==(const Creature &b1, const Creature &b2);

    friend bool operator!=(const Creature &b1, const Creature &b2);

    friend ostream &operator<<(ostream &os, const Creature &cr);

    float getCamoCoef() const;
};


#endif
