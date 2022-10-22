#include <iostream>
#include <memory>
#include <functional>

class GameCharacter;

int defaultHealthCalc(const GameCharacter& gc);

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

