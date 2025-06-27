#include <iostream>
#include "product.h"

using std::string;

class TypeSedan : public Product {
public:
    int getID() override {
        return SEDAN;
    }
    string getName() const override {
        return "Sedan";
    }
};

class TypeSUV :public Product {
public:
    string getName() const override {
        return "SUV";
    }
    int getID() override {
        return SUV;
    }
};

class TypeTruck : public Product {
public:
    string getName() const override {
        return "Truck";
    }
    int getID() override {
        return TRUCK;
    }
};

class EngineGM : public Product {
    string getName() const override {
        return "GM ����";
    }
    int getID() override {
        return GM;
    }
};

class EngineToyota : public Product {
    string getName() const override {
        return "TOYOTA ����";
    }
    int getID() override {
        return TOYOTA;
    }
};

class EngineWIA : public Product {
    string getName() const override {
        return "WIA ����";
    }
    int getID() override {
        return WIA;
    }
};

class EngineBroken : public Product {
    string getName() const override {
        return "���峭 ����";
    }
    int getID() override {
        return BROKEN;
    }
};

class BreakMando : public Product {
    string getName() const override {
        return "MANDO ������ġ";
    }
    int getID() override {
        return MANDO;
    }
};

class BreakContinental : public Product {
    string getName() const override {
        return "CONTINENTAL ������ġ";
    }
    int getID() override {
        return CONTINENTAL;
    }
};

class BreakBosch : public Product {
    string getName() const override {
        return "BOSCH ������ġ";
    }
    int getID() override {
        return BOSCH_B;
    }
};

class SteeringBosch : public Product {
    string getName() const override {
        return "BOSCH ������ġ";
    }
    int getID() override {
        return BOSCH_S;
    }
};

class SteeringMobis : public Product {
    string getName() const override {
        return "Mobis ������ġ";
    }
    int getID() override {
        return MOBIS;
    }
};


class TypeFactory {
public:
    static Product* create(int item) {
        if (item == SEDAN) return new TypeSedan();
        if (item == SUV) return new TypeSUV();
        return new TypeTruck();

    }
};

class EngineFactory {
public:
    static Product* create(int item) {
        if (item == GM) return new EngineGM();
        if (item == TOYOTA) return new EngineToyota();
        if (item == WIA) return new EngineWIA();
        return new EngineBroken();
    }
};

class BreakFactory {
public:
    static Product* create(int item) {
        if (item == MANDO) return new BreakMando();
        if (item == CONTINENTAL) return new BreakContinental();
        return new BreakBosch();
    }
};

class SteeringFactory {
public:
    static Product* create(int item) {
        if (item == BOSCH_S) return new SteeringBosch();
        return new SteeringMobis();
    }
};

class Car {
public:
    Product* carType;
    Product* engine;
    Product* breakSystem;
    Product* steering;
    string failItem1, failItem2;

    bool isValid() {
        failItem1 = "";
        failItem2 = "";

        if (carType->getID() == SEDAN && breakSystem->getID() == CONTINENTAL) 
        {
            failItem1 = carType->getName();
            failItem2 = breakSystem->getName();
            return false;
        }
        if (carType->getID() == SUV && engine->getID() == TOYOTA)
        {
            failItem1 = carType->getName();
            failItem2 = engine->getName();
            return false;
        }
        if (carType->getID() == TRUCK && engine->getID() == WIA)
        {
            failItem1 = carType->getName();
            failItem2 = engine->getName();
            return false;
        }
        if (carType->getID() == TRUCK && breakSystem->getID() == MANDO)
        {
            failItem1 = carType->getName();
            failItem2 = breakSystem->getName();
            return false;
        }
        if (breakSystem->getID() == BOSCH_B && steering->getID() != BOSCH_S)
        {
            const string additionalStr = " �̿ܿ� ";
            failItem1 = breakSystem->getName();
            failItem2 = steering->getName() + additionalStr;
            return false;
        }

        return true;
    }

};
