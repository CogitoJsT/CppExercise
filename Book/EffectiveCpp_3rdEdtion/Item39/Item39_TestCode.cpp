#include <iostream>

class BaseClass
{
public:
    void publicMethod() const
    {
        std::cout << "Call publicMethod\n";
    }
    int publicMember = 0;
protected:
    void protectedMethod() const
    {
        std::cout << "Call protectedMethod\n";
    }
    int protectedMember = 1;
private:
    void privateMethod() const
    {
        std::cout << "Private method\n";
    }
    int privateMember = 2;
};

class DerivedClassWithPublic: public BaseClass
{
public:
    void displayData() const
    {
        std::cout << publicMember << std::endl;
        std::cout << protectedMember << std::endl;
        //std::cout << privateMember << std::endl;  // Error, not accessible
    }
};

class DerivedClassWithPrivate: private BaseClass
{
public:
    void displayData() const
    {
        std::cout << publicMember << std::endl;
        std::cout << protectedMember << std::endl;
        //std::cout << privateMember << std::endl;  // Error, not accessible
    }

};

int main()
{
    DerivedClassWithPublic derivedPublic;
    DerivedClassWithPrivate derivedPrivate;

    derivedPublic.displayData();
    derivedPublic.publicMethod();
    derivedPublic.publicMember = 10;

    derivedPrivate.displayData();
    //derivedPrivate.publicMethod();      // Error, not accessible
    //derivedPrivate.publicMember = 20;   // Error, not accessible

    return 0;
}