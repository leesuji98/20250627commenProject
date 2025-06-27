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

	EXPECT_EQ("GM ����", p1->getName());
	EXPECT_EQ("TOYOTA ����", p2->getName());
	EXPECT_EQ("WIA ����", p3->getName());
    EXPECT_EQ("���峭 ����", p4->getName());
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

	EXPECT_EQ("MANDO ������ġ", p1->getName());
	EXPECT_EQ("CONTINENTAL ������ġ", p2->getName());
	EXPECT_EQ("BOSCH ������ġ", p3->getName());
	EXPECT_EQ(MANDO, p1->getID());
	EXPECT_EQ(CONTINENTAL, p2->getID());
	EXPECT_EQ(BOSCH_B, p3->getID());
}

TEST(ProductTest, steering) {
	SteeringFactory steeringfac;

	Product* p1 = steeringfac.create(BOSCH_S);
	Product* p2 = steeringfac.create(MOBIS);

	EXPECT_EQ("BOSCH ������ġ", p1->getName());
	EXPECT_EQ("Mobis ������ġ", p2->getName());
	EXPECT_EQ(BOSCH_S, p1->getID());
	EXPECT_EQ(MOBIS, p2->getID());
}

TEST(ProductTest, factory) {
	ChoiceFactory choicefac;
	ProductFactory* fac1 = choicefac.getFactory(CarType_Q);
	ProductFactory* fac2 = choicefac.getFactory(Engine_Q);
	ProductFactory* fac3 = choicefac.getFactory(brakeSystem_Q);
	ProductFactory* fac4 = choicefac.getFactory(SteeringSystem_Q);

	Product* p1 = fac1->create(SUV);
	Product* p2 = fac2->create(BROKEN);
	Product* p3 = fac3->create(CONTINENTAL);
	Product* p4 = fac4->create(BOSCH_S);

	EXPECT_EQ(SUV, p1->getID());
	EXPECT_EQ(BROKEN, p2->getID());
	EXPECT_EQ(CONTINENTAL, p3->getID());
	EXPECT_EQ(BOSCH_S, p4->getID());
}
