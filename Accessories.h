#ifndef _ACCESSORIES_H_
#define _ACCESSORIES_H_

#include <iostream>
#include <vector>
#include "UImg.h"

class InterfaceAccessory {
public: 
    virtual float speedCoef() const {
        return 1;
    }
    virtual float camoCoef() const {
        return 1;
    }
    virtual float deathCoef() const {
        return 1;
    }
};


class Accessories: public InterfaceAccessory {
public:
    InterfaceAccessory first() const;
    InterfaceAccessory last() const;
    int getSize() const;

    
private:
    InterfaceAccessory* first_;
    InterfaceAccessory* last_;
};

class Shell:public InterfaceAccessory {
public:
    virtual float speedCoef() const override;
    virtual float deathCoef() const override;
    InterfaceAccessory* next() const;
    bool hasNext() const;
private:
    InterfaceAccessory* next_;
    float speedReductionCoef_;
    float deathCoef_;
};

class Camo:public InterfaceAccessory {
public:
    virtual float camoCoef() const override;
    InterfaceAccessory* next() const;
    bool hasNext() const;
private:
    InterfaceAccessory* next_;
    float camoCoef_;

};

class Fins:public InterfaceAccessory {
public:
    virtual float speedCoef() const override;
    InterfaceAccessory* next() const;
    bool hasNext() const;
private:
    InterfaceAccessory* next_;
    float speedCoef_;
};

#endif