#include "Accessories.h"



float Accessories::speedCoef() const
{
    float coef =1 ;
    for (auto const& accessory : accessories_) {
        coef *= accessory->speedCoef();
    }
    return coef;
}

float Accessories::camoCoef() const
{
    float coef = 0.9;
    for (auto it=accessories_.begin();it!= accessories_.end();it++) {
        coef *= (*it)->camoCoef();
    }
    return coef;
}

float Accessories::deathCoef() const
{
    float coef = 1;
    for (auto it=accessories_.begin();it!= accessories_.end();it++) {
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
    for (auto const& accessory : a.accessories_) {
        accessories_.push_back(accessory->clone());
    }
}

Accessories &Accessories::operator=(const Accessories &a) {
    accessories_ = std::vector<std::unique_ptr<InterfaceAccessory>> {} ;
    for (auto const & accessory : a.accessories_) {
        accessories_.push_back(accessory->clone());
    }
    return *this;
}

std::unique_ptr<InterfaceAccessory> Accessories::clone() {
    return std::unique_ptr<InterfaceAccessory>(new Accessories(*this));
}


Shell::Shell(float speedReductionCoef, float deathCoef) 
{
    speedReductionCoef_ = speedReductionCoef;
    deathCoef_ = deathCoef;
}

int Shell::AccessoryType() const
{
    return 1;
}

float Shell::speedCoef() const
{
    return speedReductionCoef_;
}

float Shell::deathCoef() const
{
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

Camo::Camo(float camoCoef) 
{
    camoCoef_ = camoCoef;
}

int Camo::AccessoryType() const
{
    return 2;
}


float Camo::camoCoef() const
{
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

Fins::Fins(float speedCoef) 
{
    speedCoef_ = speedCoef;
}


float Fins::speedCoef() const
{
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

int Fins::AccessoryType() const
{
    return 3;
}
