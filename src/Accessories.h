#ifndef _ACCESSORIES_H_
#define _ACCESSORIES_H_

#include <iostream>
#include <vector>
#include "../lib/UImg.h"
#include <list>


class InterfaceAccessory {
public: 
    virtual float speedCoef() const {
        return 0;
    }
    virtual float camoCoef() const {
        return 0;
    }
    virtual float deathCoef() const {
        return 0;
    }
};


class Accessories: public InterfaceAccessory {
public:
    Accessories();
    float speedCoef() const;
    float camoCoef() const;
    float deathCoef() const ;
    std::list<InterfaceAccessory *> accessories_;
};

class Shell:public InterfaceAccessory {
public:
    Shell(float speedReductionCoef, float deathCoef);
    float speedCoef() const override;
    float deathCoef() const override;
private:
    float speedReductionCoef_;
    float deathCoef_;
};

class Camo:public InterfaceAccessory {
public:
    Camo(float camoCoef);
    float camoCoef() const override;
private:
    float camoCoef_;

};

class Fins:public InterfaceAccessory {
public:
    Fins(float speedCoef);
    float speedCoef() const override;
private:
    float speedCoef_;
};

#endif