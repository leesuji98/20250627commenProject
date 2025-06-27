#include <iostream>
using std::string;
#pragma once
enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    BROKEN
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

class Product {
public:
    virtual string getName() const = 0;
    virtual int getID() = 0;
    virtual ~Product() {};
};

