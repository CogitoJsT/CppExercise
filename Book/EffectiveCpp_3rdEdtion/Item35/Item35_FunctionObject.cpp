#include <iostream>
#include <memory>
#include <functional>

class GameCharacter;

int defaultHealthCalc(const GameCharacter& gc);
short calcHealth(const GameCharacter&)
{
    std::cout << "::calcHealth" << std::endl;
    return 100;
}

class GameCharacter
{
public:
    using HealthCalcFunc = std::function<int(const GameCharacter&)>;

    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
        : myHcf(hcf)
    {
    }

    int healthValue() const
    {
        return myHcf(*this);
    }

private:
    HealthCalcFunc myHcf;
};


struct HealthCalculator
{
    int operator()(const GameCharacter&) const
    {
        std::cout << "HealthCalculator::operator()" << std::endl;
        return 100;
    }
};



class GameLevel
{
public:
    float health(const GameCharacter&) const
    {
        std::cout << "GameLevel::health" << std::endl;
        return 100.0f;
    }
};

class EvilBadGuy: public GameCharacter
{
public:
    explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc)
        : GameCharacter(hcf)
    {
        std::cout << "EvilBadGuy constructor is called" << std::endl;
    }
};

class EyeCandyCharacter: public GameCharacter
{
public:
    explicit EyeCandyCharacter(HealthCalcFunc hcf = defaultHealthCalc)
        : GameCharacter(hcf)
    {
        std::cout << "EyeCandyCharacter constructor is called" << std::endl;
    }
};

int main()
{
    EvilBadGuy ebg1(calcHealth);
    EyeCandyCharacter ecc1(HealthCalculator());

    GameLevel currentLevel;

    EvilBadGuy ebg2(std::bind(&GameLevel::health, currentLevel, std::placeholders::_1));

    ebg2.healthValue();

    return 0;
}

