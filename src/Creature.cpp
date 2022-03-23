#include "Creature.h"
#include "Milieu.h"
#include <array>
#include <cstdlib>
#include <cmath>
#include <memory>
#include "constants.h"
#include <random>

const double Creature::AFF_SIZE = minSize;
const double Creature::dt = time_delta;

int Creature::next = 0;

Creature::Creature(Milieu *milieu) : m_milieu(*milieu) {
    setSize(AFF_SIZE);
    accessories = std::unique_ptr<Accessories>(new Accessories());
    sensors = std::unique_ptr<Sensors>(new Sensors());
    behaviour = std::unique_ptr<InterfaceBehaviour>(new GregariousBehaviour());
    couleur = new T[3];
    couleur[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    couleur[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    couleur[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);

}

Creature &Creature::operator=(const Creature &c) {

    id = c.id;
    setSpeed(Vector(c.speed));
    hitbox = CircleHitbox(c.hitbox);
    age = c.age;
    m_dyingAge = c.m_dyingAge;
    baseDeathProbOnCollision = c.baseDeathProbOnCollision;
    setSize(c.getSize());

    couleur = new T[3];
    memcpy(couleur, c.couleur, 3 * sizeof(T));
    accessories = std::unique_ptr<Accessories>(new Accessories(*c.accessories));
    sensors = std::unique_ptr<Sensors>(new Sensors(*c.sensors));
    behaviour = (*c.behaviour).clone();
    return *this;
}

Creature::Creature(const Creature &b) : m_milieu(b.m_milieu) {
    id = b.id;
    setPos(Vector(b.position));
    setSize(b.getSize());
    setSpeed(b.speed);
    age = 1;
    baseDeathProbOnCollision = b.baseDeathProbOnCollision;
    m_dyingAge = b.m_dyingAge;
    accessories = std::unique_ptr<Accessories>(new Accessories(*b.accessories));
    sensors = std::unique_ptr<Sensors>(new Sensors(*b.sensors));
    behaviour = (*b.behaviour).clone();
    couleur = new T[3];
    memcpy(couleur, b.couleur, 3 * sizeof(T));
}

Creature::~Creature(void) {

    delete[] couleur;
}

double Creature::getCollisionDeathProb() const {
    return baseDeathProbOnCollision * accessories->deathCoef();
}

void Creature::onMove(Milieu &monMilieu) {
    // Get the speed that the behaviour gives
    previous_speed = speed;
    Vector moveD = behaviour->moveDirection(position, getVisibleCreatures());
    setSpeed(getBaseSpeed() * moveD);
    if (moveD == Vector(0, 0)) {
        setSpeed(previous_speed);
    }
    // Once all that is done actually update the position of the creature
    move();
    handleWallCollision(m_milieu.getWidth(), m_milieu.getHeight());
}

void Creature::move() {
    // calculate new position
    Vector dV = speed * dt;
    Vector new_position = position + dV;
    // align to grid
    new_position.alignToGrid();

    setPos(new_position);
}

void Creature::handleWallCollision(int xLim, int yLim) {
// handle Wall collisions
    if ((position.x < 0) || (position.x > xLim)) {
        speed.reflectY();
    }
    if ((position.y < 0) || (position.y > yLim)) {
        speed.reflectX();
    }
    position.clip(0, xLim, 0, yLim);
};


double Creature::getSize() const {
    return hitbox.radius;
};

void Creature::draw(UImg &support) {
    double xt = position.x + cos(speed.orientation()) * getSize() / 2.1;
    double yt = position.y - sin(speed.orientation()) * getSize() / 2.1;
    unsigned char white[] = {255, 255, 255};
    support.draw_ellipse(position.x, position.y, getSize(), getSize() / 5., -speed.orientation() / M_PI * 180.,
                         couleur);
    support.draw_circle(xt, yt, getSize() / 2., couleur);
    support.draw_circle(xt, yt, getSize() / 6., white);
    unsigned char black[] = {0, 0, 0};
    unsigned char red[] = {255, 0, 0};
    unsigned char green[] = {0, 255, 0};
    int opacity = 1;
    for (auto const &it: accessories->accessories_) {
        if (it->AccessoryType() == 1) {
            support.draw_ellipse(position.x, position.y, getSize() * 2, getSize(), getOrient() / M_PI * 180., red, 0.6);
        }
        if (it->AccessoryType() == 2) {
            support.draw_ellipse(position.x, position.y, getSize() * 1.4, getSize() / 3, getOrient() / M_PI * 180.,
                                 green);
        }
        if (it->AccessoryType() == 3) {
            support.draw_ellipse(position.x, position.y, getSize(), getSize() / 5.,
                                 (getOrient() + M_PI / 2) / M_PI * 180., behaviour->getColor());
        }
    }

    support.draw_ellipse(position.x, position.y, getSize(), getSize() / 5., -getOrient() / M_PI * 180.,
                         behaviour->getColor(), opacity);
    support.draw_circle(position.x, position.y, getSize() / 2., behaviour->getColor(), opacity);
}


bool operator==(const Creature &b1, const Creature &b2) {
    return (b1.id == b2.id);
}

Vector Creature::getPos() const {
    return {position};
};

Vector Creature::getSpeed() const {
    return {speed};
};

double Creature::getOrient() const {
    return speed.orientation();
};

int Creature::getAge() const {
    return age;
};


int Creature::getId() const {
    return id;
};

CircleHitbox Creature::getHitbox(void) const {
    return {hitbox};
};

void Creature::setOrient(double ori) {
    speed.rotate(ori - speed.orientation());
}

void Creature::setPos(Vector v) {
    position = v;
    updateHitboxPosition();
}

void Creature::setSpeed(Vector v) {
    speed = v;
}

void Creature::detectSurroundings() {
    setVisibleCreatures(m_milieu.surrounding(*this));
}

bool operator!=(const Creature &b1, const Creature &b2) {
    return !(b1 == b2);
}

void Creature::onAge() {
    ++age;
    if (age > m_dyingAge) {
        m_milieu.addCreatureToKill(id);
    }
}

void Creature::onCreatureCollision() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::bernoulli_distribution shouldDie(getCollisionDeathProb());
    if (shouldDie(mt)) {
        m_milieu.addCreatureToKill(id);
    } else {
        speed *= -1;
    }
}

void Creature::setVisibleCreatures(std::vector<std::array<Vector, 2>> t_visibleCreatures) {
    visibleCreatures = t_visibleCreatures;
}

std::vector<std::array<Vector, 2>> Creature::getVisibleCreatures() const {
    return visibleCreatures;
}

float Creature::getCamoCoef() const {
    const double accessoriesCamoCoef = accessories->camoCoef();
    if (accessoriesCamoCoef != 1) {
        return accessoriesCamoCoef;
    } else { // No camo in the accessories
        return baseCamoCoef;
    }
}

void Creature::updateHitboxPosition() {
    hitbox.center = position;
}

void Creature::setSize(double s) {
    hitbox.radius = s;
}

ostream &operator<<(ostream &os, const Creature &cr) {
    os << "Creature with id <" << cr.getId() << ">";
    return os;
}

void Creature::setDyingAge(int i) {
    m_dyingAge = i;
}

int Creature::getDyingAge() const {
    return m_dyingAge;
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