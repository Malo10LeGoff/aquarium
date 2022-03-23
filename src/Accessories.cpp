#include "Accessories.h"


float Accessories::speedCoef() const {
    float coef = 1;
    for (auto const &accessory: accessories_) {
        coef *= accessory->speedCoef();
    }
    return coef;
}

float Accessories::camoCoef() const {
    float coef = 1;
    for (auto it = accessories_.begin(); it != accessories_.end(); it++) {
        coef *= (*it)->camoCoef();
    }
    return coef;
}

float Accessories::deathCoef() const {
    float coef = 1;
    for (auto it = accessories_.begin(); it != accessories_.end(); it++) {
        coef *= (*it)->deathCoef();
    }
    return coef;
}

void Accessories::add(std::unique_ptr<InterfaceAccessory> &accessory) {
    accessories_.push_back(std::move(accessory));
}

void Accessories::remove(int idx) {
    accessories_.erase(accessories_.begin() + idx);
}

Accessories::Accessories(const Accessories &a) {
    for (auto const &accessory: a.accessories_) {
        accessories_.push_back(accessory->clone());
    }
}

Accessories &Accessories::operator=(const Accessories &a) {
    accessories_ = std::vector<std::unique_ptr<InterfaceAccessory>>{};
    for (auto const &accessory: a.accessories_) {
        accessories_.push_back(accessory->clone());
    }
    return *this;
}

std::unique_ptr<InterfaceAccessory> Accessories::clone() {
    return std::unique_ptr<InterfaceAccessory>(new Accessories(*this));
}

void Accessories::draw(UImg &support, Vector position, Vector speed, double size, T color) {

    for (auto & accessory: accessories_) {
        accessory->draw(support, position,  speed,  size,color);
        }
    };




Shell::Shell(float speedReductionCoef, float deathCoef) {
    speedReductionCoef_ = speedReductionCoef;
    deathCoef_ = deathCoef;
}

float Shell::speedCoef() const {
    return speedReductionCoef_;
}

float Shell::deathCoef() const {
    return deathCoef_;
}

Shell::Shell(const Shell &s) {
    speedReductionCoef_ = s.speedReductionCoef_;
    deathCoef_ = s.deathCoef_;
}

Shell &Shell::operator=(const Shell &s) {
    speedReductionCoef_ = s.speedReductionCoef_;
    deathCoef_ = s.deathCoef_;
    return *this;
}

std::unique_ptr<InterfaceAccessory> Shell::clone() {
    return std::unique_ptr<InterfaceAccessory>(new Shell(*this));
}

void Shell::draw(UImg &support, Vector position, Vector speed, double size , T color) {
    support.draw_ellipse(position.x, position.y, size * 2, size, speed.orientation() / M_PI * 180.,&color, 0.6);
};



Camo::Camo(float camoCoef) {
    camoCoef_ = camoCoef;
}


float Camo::camoCoef() const {
    return camoCoef_;
}

Camo::Camo(const Camo &c) {
    camoCoef_ = c.camoCoef_;
}

Camo &Camo::operator=(const Camo &c) {
    camoCoef_ = c.camoCoef_;
    return *this;
}

std::unique_ptr<InterfaceAccessory> Camo::clone() {
    return std::unique_ptr<InterfaceAccessory>(new Camo(*this));
}

void Camo::draw(UImg &support, Vector position, Vector speed, double size, T color) {
    support.draw_ellipse(position.x, position.y, size * 1.4, size / 3, speed.orientation() / M_PI * 180.,&color);
    };


Fins::Fins(float speedCoef) {
    speedCoef_ = speedCoef;
}


float Fins::speedCoef() const {
    return speedCoef_;
}


Fins::Fins(const Fins &f) {
    speedCoef_ = f.speedCoef_;
}

Fins &Fins::operator=(const Fins &f) {
    speedCoef_ = f.speedCoef_;
    return *this;
}

std::unique_ptr<InterfaceAccessory> Fins::clone() {
    return std::unique_ptr<InterfaceAccessory>(new Fins(*this));
}

void Fins::draw(UImg &support, Vector position, Vector speed, double size,T color) {
    support.draw_ellipse(position.x, position.y, size, size / 5.,( speed.orientation() + M_PI / 2) / M_PI * 180. , &color);
};


