#include <iostream>
using std::string;
#pragma once
enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

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

class ProductFactory {
public:
    virtual Product* create(int item) = 0;
    virtual ~ProductFactory() {}
};