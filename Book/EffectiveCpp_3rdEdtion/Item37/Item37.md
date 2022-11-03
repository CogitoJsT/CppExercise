# Item 37. 어떤 함수에 대해서도 상속받은 기본 매개변수 값은 절대로 재정의하지 말자

상속받을 수 있는 함수의 종류는
- Virtual function
- Non virtual function

뿐인데, Non virtual function 인 경우 절대 재정의 하지 말아야 하므로   
이 챕터에서는 ```기본 매개변수 값을 가진 virtual function``` 에 대해서만 논의함
<br><br>

# Object's type

## Static type
코드 상에서 객체 선언 시 지정한 타입

## Dynamic type
현재 reference 하고 있는 객체의 타입에 따라 결정되는데, 보통 어떻게 동작할 것이냐를 가리키는 타입
<br>
<br>

# Background

```c++
class Shape
{
public:
    enum ShapeColor { Red, Green, Blue };

    // 모든 도형은 자기 자신을 그리는 함수를 제공해야 한다.
    virtual void draw(ShapeColor color = Red) const = 0;
    ...
};

class Rectangle: public Shape
{
public:
    // 기본 매개변수 값이 달라짐 - bad!!
    virtual void draw(ShapeColor color = Green) const;
    ...
};

class Circle: public Shape
{
public:
    virtual void draw(ShpaeColor color) const;
    ...
};

...

Shape *ps;                  // Static type = Shape*, Dynamic type = None

Shape *pc = new Circle;     // Static type = Shape*, Dynmaic type = Circle*

Shape *pr = new Rectangle;  // Static type = Shape*, Dynamic type = Rectangle*

ps = pc;                    // ps's dynamic type = Circle*

ps = pr;                    // ps's dynamic type = Rectangle*


pc->draw(Shape::Red);       // Call Circle::draw(Shape::Red)

pr->draw(Shape::Red);       // Call Rectangle::draw(Shape::Red)
```
<br>

명시적으로 draw function 에 argument 값을 넣어주는 경우에는 별 문제가 없다.  
하지만 '기본 매개변수 값이 설정된' virtual function 으로 오게 되면 꼬이기 시작한다.  
```virtual function 은 동적으로 바인딩되어 있지만 기본 매개변수는 정적으로 바인딩되어 있기 때문```
<br>
<br>

```c++
pr->draw();                // Call Rectangle::draw(Shape::Red)!!!!!
```
<br>

pr 의 dynamic type 이 Rectangle* 이므로 호출되는 virtual function 은 Rectangle 의 것이고,  
기본 매개변수 값은 Shape::Green 으로 설정되어 있다.  
하지만 pr의 static type 은 Shape* 이기 때문에  
```지금 호출되는 virtual function 에 쓰이는 기본 매개변수 값을 Shape 클래스에서 가져온다.```  
```
NOTE
포인터가 아닌 참조에서도 동일한 문제가 발생한다.  
draw 함수가 virtual function 이고 기본 매개변수 값들 중 하나가 derived class 에서 재정의 되면 여지없이 문제가 발생한다.
```
<br>

## Why Compiler operates like that? 
원서의 내용을 인용하면,,
```
The answer has to do with runtime efficiency. If default parameter values were dynamically bound, compilers would have to come up with a way to determine the appropriate default value(s) for parameters of virtual functions at runtime, which would be slower and more complicated than the current mechanism of determining them during compilation.
The decision was made to err on the side of speed and simplicity of implementation, and the result is that you now enjoy execution behavior that is efficient, but, if you fail to heed the advice of this
Item, confusing.
```
컴파일러가 위와 같이 동작하는 이유는 ```run time efficiency``` 때문이다.


<br>

# Solution
아래와 같이 base class 및 derived class 의 사용자에게 기본 매개변수 값을 동일하게 제공
```c++
class Shape
{
public:
    enum ShapeColor { Red, Green, Blue};
    virtual void draw(ShapeColor color = Red) const = 0;
    ...
};

class Rectangle: public Shape
{
public:
    virtual void draw(ShapeColor color = Red) const;
    ...
};
```
하지만 문제가 있다.  
1. 코드 중복
2. Shape 클래스의 기본 매개변수 값에 대한 의존성 (Shape class 에서 draw의 기본 매개변수 값이 달라지면 derived class에서도 모두 변경해야 함)
<br><br>

## NVI(Non Virtual Interface) 사용하여 문제 해결
-> 자세한 사항은 Item35 참조
```c++
class Shape
{
public:
    enum ShapeColor { Red, Green, Blue };
    void draw(ShapeColor color = Red) const
    {
        doDraw(color);
    }
    ...
private:
    virtual void doDraw(ShapeColor color) const = 0;
};

class Rectangle: public Shape
{
public:
    ...
private:
    virtual void doDraw(ShapeColor color) const;
};
```
Non virtual function 는 derived class 에서 오버라이드되면 안 되기 때문에 draw 함수의 color 매개변수에 대한 기본 값을 깔끔하게 Red로 고정 가능하다.