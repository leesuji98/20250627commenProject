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

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

int TypeMaxRange[5] = { 3, 4, 3, 2, 2 };
const char* QuestionTypeName[] = {
    "���� Ÿ��",
    "����",
    "������ġ",
    "���ýý���",
    "Runt Test"
};

const char* CarTypeName[] = {
    "Sedan",
    "SUV",
    "Truck",
};

const char* EngineTypeName[] = {
    "GM",
    "TOYOTA",
    "WIA",
    "���峭",
};

const char* BreakTypeName[] = {
    "MANDO",
    "CONTINENTAL",
    "BOSCH",
};

const char* SteeringTypeName[] = {
    "BOSCH",
    "MOBIS",
};

enum InputValue
{
    Reset_I = 0,
    Exit_I = -1,
    NotNumber_I = -2,
};

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
    WIA
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

    // ���ڷ� �� ������� Ȯ��
    char* checkNumber;
    ret = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ
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

int runStep(int step, int answer)
{
    if (step == CarType_Q)
    {
        selectCarType(answer);
        delay(800);
        step = Engine_Q;
    }
    else if (step == Engine_Q)
    {
        selectEngine(answer);
        delay(800);
        step = brakeSystem_Q;
    }
    else if (step == brakeSystem_Q)
    {
        selectbrakeSystem(answer);
        delay(800);
        step = SteeringSystem_Q;
    }
    else if (step == SteeringSystem_Q)
    {
        selectSteeringSystem(answer);
        delay(800);
        step = Run_Test;
    }
    else if (step == Run_Test && answer == 1)
    {
        runProducedCar();
        delay(2000);
    }
    else if (step == Run_Test && answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
        delay(2000);
    }

    return step;
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
            printf("� ���� Ÿ���� �����ұ��?\n");
            printf("1. Sedan\n");
            printf("2. SUV\n");
            printf("3. Truck\n");
        }
        else if (step == Engine_Q)
        {
            printf(CLEAR_SCREEN);
            printf("� ������ ž���ұ��?\n");
            printf("0. �ڷΰ���\n");
            printf("1. GM\n");
            printf("2. TOYOTA\n");
            printf("3. WIA\n");
            printf("4. ���峭 ����\n");
        }
        else if (step == brakeSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("� ������ġ�� �����ұ��?\n");
            printf("0. �ڷΰ���\n");
            printf("1. MANDO\n");
            printf("2. CONTINENTAL\n");
            printf("3. BOSCH\n");
        }
        else if (step == SteeringSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("� ������ġ�� �����ұ��?\n");
            printf("0. �ڷΰ���\n");
            printf("1. BOSCH\n");
            printf("2. MOBIS\n");
        }
        else if (step == Run_Test)
        {
            printf(CLEAR_SCREEN);
            printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
            printf("� ������ �ұ��?\n");
            printf("0. ó�� ȭ������ ���ư���\n");
            printf("1. RUN\n");
            printf("2. Test\n");
        }
        printf("===============================\n");

        printf("INPUT > ");
        fgets(buf, sizeof(buf), stdin);
        int answer = validCheckInputValue(buf);

        if (answer == Exit_I)
        {
            printf("���̹���\n");
            break;
        }

        if (answer == NotNumber_I)
        {
            printf("ERROR :: ���ڸ� �Է� ����\n");
            delay(2000);
            continue;
        }

        if (answer == Reset_I)
        {
            if ((step == CarType_Q)) {
                printf("ERROR:: %s��(��) 1 ~ %d ������ ���� ����\n", QuestionTypeName[step], TypeMaxRange[step]);
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
                printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
            else
                printf("ERROR:: %s��(��) 1 ~ %d ������ ���� ����\n", QuestionTypeName[wrongStep], TypeMaxRange[wrongStep]);
            delay(800);
            continue;
        }

        step = runStep(step, answer);
    }
}

void selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    printf("���� Ÿ������ %s�� �����ϼ̽��ϴ�.\n", CarTypeName[answer-1]);
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    printf("%s ������ �����ϼ̽��ϴ�.\n", EngineTypeName[answer - 1]);
}

void selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", BreakTypeName[answer - 1]);
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", SteeringTypeName[answer - 1]);
}

int isValidCheck()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        return false;
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        return;
    }

    if (stack[Engine_Q] == 4)
    {
        printf("������ ���峪�ֽ��ϴ�.\n");
        printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        return;
    }

    printf("Car Type : %s\n", CarTypeName[stack[CarType_Q]-1]);
    printf("Engine : %s\n", EngineTypeName[stack[Engine_Q]-1]);
    printf("Brake System : %s\n", BreakTypeName[stack[brakeSystem_Q]-1]);
    printf("SteeringSystem : %s\n", SteeringTypeName[stack[SteeringSystem_Q]-1]);

    printf("�ڵ����� ���۵˴ϴ�.\n");
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}

#endif