#include <iostream>
#include <memory>

class GameCharacter
{
public:
    void healthValue() const
    {
        // Do something before doHealthValue()

        doHealthValue();

        // Do something after doHealthValue()
    }

private:
    virtual void doHealthValue() const      // Derived calss is able to override this virtual function
    {
        // Default algorithm for calculating health value

        std::cout << "doHealthValue() is called\n";
    }
};

class Soldier : public GameCharacter
{
private:
    virtual void doHealthValue() const override
    {
        std::cout << "Soldier::dohealthValue() is called\n";
    }
};

int main()
{
    std::unique_ptr<GameCharacter> characterUP = std::make_unique<Soldier>();

    characterUP->healthValue();

    return 0;
}