#include <iostream>
#include <memory>

class Shape
{
public:
    virtual void draw() = 0;
};

void
Shape::draw()
{
    std::cout << "Shape::draw()" << std::endl;
}


class Rectangle : public Shape
{
public:
    virtual void draw() override;
};

void
Rectangle::draw()
{
    std::cout << "Rectangle::draw()" << std::endl;
}

int main()
{
    std::unique_ptr<Shape> shapeUP = std::make_unique<Rectangle>();
    shapeUP->draw();
    shapeUP->Shape::draw();
    return 0;
}