#include <iostream>

class Shape
{
public:
    enum class ShapeColor { Red = 0, Green, Blue };

    virtual void draw(ShapeColor color = ShapeColor::Red) const = 0;
};

class Rectangle: public Shape
{
public:
    virtual void draw(Shape::ShapeColor color = Shape::ShapeColor::Green) const override;
};

void
Rectangle::draw(Shape::ShapeColor color) const
{
    std::cout << "Rectangle::draw(" << static_cast<int>(color) << ")" << std::endl;
}

int main()
{
    Shape *shape = new Rectangle();

    shape->draw(); // Call Rectangle::draw(Shape::Red)

    return 0;
}