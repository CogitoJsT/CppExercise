# Item32. Make sure public inheritance models "is-a"
public 상속 모형은 반드시 "is-a"를 따르도록 하자
<br>
<br>

# One sentence
public 상속은 "is-a(...는 ...의 일종이다)" 를 의미한다.
<br>
<br>

# Simple background
Base class 는 Derived class 보다 일반적이다. 
```c++
class Person {...};
class Student : public Person {...};
```
예를 들어 모든 학생들은 사람이지만 모든 사람이 학생은 아니다. 
```c++
void eat(const Person& p);      // Good

void study(const Student& s);   // Good

Person p;       // Good
Student s;      // Good

eat(p);         // Good
eat(s);         // Good

study(s);       // Good
study(p);       // Error!!! p is not student

```
<br>

# Bird and Penguin class problem
새와 펭귄에 대해 아래와 같이 디자인 할 수 있다. 
```c++
class Bird
{
public:
    virtual void fly();         // 새는 날 수 있습니다. 
    ...
};
class Penguin : public Bird     // 펭귄은 새입니다.
{
    ...
};
```

문제가 없어 보이지만, 사실 문제가 있다. 펭귄은 날지 못한다.  
새는 날 수 있다고 할 때, 모든 종류의 새를 뜻하는 것은 아니다.  

## Solution 1
아래처럼 다시 디자인 할 수 있다.  

- fly method 를 Bird 에서 제거
- 날 수 있는 새들을 위한 hlass 를 새로 정의하고 fly method 정의
- 펭귄은 다른 클래스로 정의하고, fly method 없음


```c++
class Bird
{
    ...
};

class FlyingBird: public Bird
{
public:
    virtual void fly();
    ...
};

class Penguin: public Bird
{
    ...
};
```
1. 어떤 SW 에서는 비행 능력이 있는 새와 없는 새를 구분하지 않아도 문제가 없을 수 있다.
2. 이럴 경우, 오히려 위의 첫 번째 디자인이 더 좋다.
3. 즉, 모든 SW에 이상적인 설계 같은 것은 없다라는 반증.
4. 이런 것들을 잘 구분해서 설계하는 것이 바람직하다.

## Solution 2
아래처럼 fly 함수를 재정의하여 런타임 에러를 내도록 한다.
```c++
void error(const std::string& message);
...
class Penguin: public Bird
{
public:
    virtual void fly()
    {
        error("Attempt to make a Penguin fly!");
    }
    ...
}
```
위의 code의 의미는  
_펭귄이 날 수는 있지만 실제로 날려고 하면 에러가 난다._  
<br>
위의 첫 번째 solutoin은 compile time 에 펭귄의 fly 여부가 결정이 되는 것이고(compile time error),  
두 번째 solution의 경우, run time 때 fly 할 수 없다는 것이 결정된다.(run time error)  
<br>
compile time에 결정이 되도록 하려면 아래처럼 fly 함수를 빼면 된다. 

```c++
class Bird
{
    ...
};

class Penguin: public Bird
{
    ...
};
...

Penguin p;
p.fly();        // Error in compile time!!!!!!
```
<br>

# Rectangle and Square class problem
정사각형 클래스는 직사각형 클래스로부터 상속을 받아야 할까?  
<br>
아래와 같은 코드가 있다.

```c++
class Rectangle
{
public:
    virtual void setHeight(int newHeight);
    virtual void setWidth(int newWidth);

    virtual int height() const;
    virtual int width() const;
    ...
};

void makeBigger(Rectangle& r)       // r의 넓이를 늘리는 함수
{
    int oldHeight = r.height();
    r.setWidth(r.width() + 10);
    assert(r.height() == oldHeight);
}
...

class Square: public Rectangle {...};

Square s;
...
assert(s.width() == s.height());    // 참이어야 한다.

makeBigger(s);                      // s의 넓이를 늘린다.

assert(s.width() == s.height());    // 참이어야 한다.
```
1. makeBigger는 Rectangle 타입의 변수를 레퍼런스로 받고, r의 넓이를 늘린다. 
2. Square 로 선언된 s가 makeBigger 에 입력된다. (Rectangle를 상속받았으므로..)
3. makeBigger는 s의 넓이를 늘린다. => ```s 는 더이상 정사각형이 아니다.```

직사각형의 성질 중 어떤 것은 정사각형에 적용할 수가 없다.  
그러나 public 상속은 기본 클래스 객체가 가진 ```모든 것```들이 파생 클래스 객체에서도 그대로 적용된다고 단정하는 속성이다.  
그렇기에 Square는 Rectangle 를 상속받으면 안된다. 

























