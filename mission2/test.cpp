#include "gmock/gmock.h"
#include "product.cpp"

TEST(ProductTest, type) {
	TypeFactory typefac;
	
	Product *p1 = typefac.create(SEDAN);
	Product *p2 = typefac.create(SUV);
	Product *p3 = typefac.create(TRUCK);

	EXPECT_EQ("Sedan", p1->getName());
	EXPECT_EQ("SUV", p2->getName());
	EXPECT_EQ("Truck", p3->getName());
	EXPECT_EQ(SEDAN, p1->getID());
	EXPECT_EQ(SUV, p2->getID());
	EXPECT_EQ(TRUCK, p3->getID());
}

TEST(ProductTest, engine) {
	EngineFactory enginefac;

	Product* p1 = enginefac.create(GM);
	Product* p2 = enginefac.create(TOYOTA);
	Product* p3 = enginefac.create(WIA);
    Product* p4 = enginefac.create(BROKEN);

	EXPECT_EQ("GM 엔진", p1->getName());
	EXPECT_EQ("TOYOTA 엔진", p2->getName());
	EXPECT_EQ("WIA 엔진", p3->getName());
    EXPECT_EQ("고장난 엔진", p4->getName());
	EXPECT_EQ(GM, p1->getID());
	EXPECT_EQ(TOYOTA, p2->getID());
	EXPECT_EQ(WIA, p3->getID());
	EXPECT_EQ(BROKEN, p4->getID());
}

TEST(ProductTest, breakfac) {
	BreakFactory breakfac;

	Product* p1 = breakfac.create(MANDO);
	Product* p2 = breakfac.create(CONTINENTAL);
	Product* p3 = breakfac.create(BOSCH_B);

	EXPECT_EQ("MANDO 제동장치", p1->getName());
	EXPECT_EQ("CONTINENTAL 제동장치", p2->getName());
	EXPECT_EQ("BOSCH 제동장치", p3->getName());
	EXPECT_EQ(MANDO, p1->getID());
	EXPECT_EQ(CONTINENTAL, p2->getID());
	EXPECT_EQ(BOSCH_B, p3->getID());
}

TEST(ProductTest, steering) {
	SteeringFactory steeringfac;

	Product* p1 = steeringfac.create(BOSCH_S);
	Product* p2 = steeringfac.create(MOBIS);

	EXPECT_EQ("BOSCH 조향장치", p1->getName());
	EXPECT_EQ("Mobis 조향장치", p2->getName());
	EXPECT_EQ(BOSCH_S, p1->getID());
	EXPECT_EQ(MOBIS, p2->getID());
}
