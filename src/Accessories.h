#ifndef _ACCESSORIES_H_
#define _ACCESSORIES_H_

#include <iostream>
#include <vector>
#include "../lib/UImg.h"
#include <memory>

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
    virtual std::unique_ptr<InterfaceAccessory> clone() = 0 ;
    virtual int AccessoryType() const {
        return 0;
    }
};


class Accessories: public InterfaceAccessory {
public:
    Accessories() = default;
    Accessories(const Accessories & a);
    ~Accessories() = default ;
    Accessories& operator=(const Accessories& a);
    float speedCoef() const override;
    float camoCoef() const override;
    float deathCoef() const override ;
    std::vector<std::unique_ptr<InterfaceAccessory>> accessories_;
    void add(std::unique_ptr<InterfaceAccessory>& accessory);
    void remove(int idx);
    std::unique_ptr<InterfaceAccessory> clone() override;
};

class Shell:public InterfaceAccessory {
public:
    Shell(float speedReductionCoef, float deathCoef);
    Shell(const Shell & s);
    ~Shell() = default;
    Shell& operator=(const Shell& s);
    float speedCoef() const override;
    float deathCoef() const override;
    std::unique_ptr<InterfaceAccessory> clone() override;
    int AccessoryType() const;
private:
    float speedReductionCoef_;
    float deathCoef_;
};

class Camo:public InterfaceAccessory {
public:
    explicit Camo(float camoCoef);
    Camo(const Camo& c);
    ~Camo()=default;
    Camo& operator=(const Camo& c);
    float camoCoef() const override;
    std::unique_ptr<InterfaceAccessory> clone() override;
    int AccessoryType() const;
private:
    float camoCoef_;

};

class Fins:public InterfaceAccessory {
public:
    explicit Fins(float speedCoef);
    Fins(const Fins& f);
    ~Fins() =default;
    Fins& operator=(const Fins& f);
    float speedCoef() const override;
    std::unique_ptr<InterfaceAccessory> clone() override;
    int AccessoryType() const;
private:
    float speedCoef_;
};

#endif