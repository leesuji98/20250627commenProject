#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "product.cpp"

#define CLEAR_SCREEN "\033[H\033[2J"

Car car;

int runStep(int step, int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

int TypeMaxRange[5] = { 3, 4, 3, 2, 2 };
const char* QuestionTypeName[] = {
    "차량 타입",
    "엔진",
    "제동장치",
    "스팅시스템",
    "Runt Test"
};

enum InputValue
{
    Reset_I = 0,
    Exit_I = -1,
    NotNumber_I = -2,
};


void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

int validCheckInputValue(char* buf)
{
    int ret;

    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
        return Exit_I;

    // 숫자로 된 대답인지 확인
    char* checkNumber;
    ret = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환
    if (*checkNumber != '\0')
        return NotNumber_I;

    return ret;
}

int checkAnswerWrongRange(int step, int answer)
{
    int ret = -1;
    int maxInput = TypeMaxRange[step];
    int minInput = 1;
    if ((answer < minInput) || (answer > maxInput))
        return step;

    return ret;
}

void setCar(int step, int answer, Product* p)
{
    if (step == CarType_Q) {
        car.carType = p;
        return;
    }
    if (step == Engine_Q) {
        car.engine = p;
        return;
    }
    if (step == brakeSystem_Q) {
        car.breakSystem = p;
        return;
    }
    if (step == SteeringSystem_Q) {
        car.steering = p;
        return;
    }
}


int main()
{
    char buf[100];
    int step = CarType_Q;

    while (1)
    {

        if (step == CarType_Q)
        {
            printf(CLEAR_SCREEN);

            printf("        ______________\n");
            printf("       /|            | \n");
            printf("  ____/_|_____________|____\n");
            printf(" |                      O  |\n");
            printf(" '-(@)----------------(@)--'\n");
            printf("===============================\n");
            printf("어떤 차량 타입을 선택할까요?\n");
            printf("1. Sedan\n");
            printf("2. SUV\n");
            printf("3. Truck\n");
        }
        else if (step == Engine_Q)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 엔진을 탑재할까요?\n");
            printf("0. 뒤로가기\n");
            printf("1. GM\n");
            printf("2. TOYOTA\n");
            printf("3. WIA\n");
            printf("4. 고장난 엔진\n");
        }
        else if (step == brakeSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 제동장치를 선택할까요?\n");
            printf("0. 뒤로가기\n");
            printf("1. MANDO\n");
            printf("2. CONTINENTAL\n");
            printf("3. BOSCH\n");
        }
        else if (step == SteeringSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 조향장치를 선택할까요?\n");
            printf("0. 뒤로가기\n");
            printf("1. BOSCH\n");
            printf("2. MOBIS\n");
        }
        else if (step == Run_Test)
        {
            printf(CLEAR_SCREEN);
            printf("멋진 차량이 완성되었습니다.\n");
            printf("어떤 동작을 할까요?\n");
            printf("0. 처음 화면으로 돌아가기\n");
            printf("1. RUN\n");
            printf("2. Test\n");
        }
        printf("===============================\n");

        printf("INPUT > ");
        fgets(buf, sizeof(buf), stdin);
        int answer = validCheckInputValue(buf);

        if (answer == Exit_I)
        {
            printf("바이바이\n");
            break;
        }
        if (answer == NotNumber_I)
        {
            printf("ERROR :: 숫자만 입력 가능\n");
            delay(2000);
            continue;
        }
        if (answer == Reset_I)
        {
            if ((step == CarType_Q)) {
                printf("ERROR:: %s은(는) 1 ~ %d 범위만 선택 가능\n", QuestionTypeName[step], TypeMaxRange[step]);
                delay(800);
                continue;
            }
            if (step == Run_Test)
                step = CarType_Q;
            else
                step -= 1;
            continue;
        }

        int wrongStep = checkAnswerWrongRange(step, answer);
        if (wrongStep >= 0)
        {
            if (wrongStep == Run_Test)
                printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
            else
                printf("ERROR:: %s은(는) 1 ~ %d 범위만 선택 가능\n", QuestionTypeName[wrongStep], TypeMaxRange[wrongStep]);
            delay(800);
            continue;
        }

        step = runStep(step, answer);
    }
}

int runStep(int step, int answer)
{
    ChoiceFactory choicefac;
    ProductFactory* fac = choicefac.getFactory(step);

    const string preStr = "차량 타입으로 ";
    const string endStr = "을 선택하셨습니다.\n";

    if (step == Run_Test && answer == 1)
    {
        runProducedCar();
        delay(200);
        return step;
    }
    else if (step == Run_Test && answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
        delay(2000);
        return step;
    }
    Product* prod = fac->create(answer);
    setCar(step, answer, prod);

    string printStr = prod->getName();

    if (step == CarType_Q)
        printStr = preStr + printStr + endStr;
    else
        printStr = printStr + endStr;

    printf("%s", printStr.c_str());

    delay(1500);
    step += 1;
    return step;
}

void runProducedCar()
{
    if (car.isValid() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }

    if (car.engine->getID() == BROKEN)
    {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    printf("Car Type : %s\n", car.carType->getName().c_str());
    printf("Engine : %s\n", car.engine->getName().c_str());
    printf("Brake System : %s\n", car.breakSystem->getName().c_str());
    printf("SteeringSystem : %s\n", car.steering->getName().c_str());

    printf("자동차가 동작됩니다.\n");
}

void testProducedCar()
{
    if (car.isValid()) {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
        return;
    }

    printf("자동차 부품 조합 테스트 결과 : FAIL\n");
    printf("%s에는  %s 사용 불가\n", car.failItem1.c_str(), car.failItem2.c_str());
}

#endif