# Item 34. 인터페이스 상속과 구현 상속의 차이를 제대로 파악하고 구별하자

상속의 2가지 타입
- 함수 인터페이스 상속
- 함수 구현의 상속
<br>

아래의 코드를 보면,
```c++
class Shape
{
public:
    virtual void draw() const = 0;      // pure virtual function
    virtual void error(const std::string& msg);     // virtul function
    int objectID() const;       // non-virtual function
    ...
};
class Retangle: public Shape {};
class Elipse : public Shape {};
```

```Shape``` 는 draw 라는 순수 가상 함수가 있기 때문에 추상클래스이고, 인스턴스화가 불가능하다.
<br><br>

# Pure virtual function, draw
순수 가상 함수를 선언하는 목적은 파생 클래스에게 함수의 인터페이스만을 물려주려는 것  
=> *"draw 함수는 여러분이 직접 제공하도록 하세요. 하지만 당신이 어떻게 구현할지에 대해 난 아무 생각 없소"*
<br><br>
## 순수 가상 함수 정의
<br>
Shape::draw 함수에 대해 구현을 붙일 수 있다.<br>
단, 구현이 붙은 순수 가상 함수를 호출하려면 반드시 클래스 이름을 한정자로 붙여 주어야만 한다.

```c++
Shape *ps = new Shape;      // Error! Shape is abstract class

Shape *ps1 = new Retangle;  // Good
ps1->draw();                // OK, call Retangle::draw()

Shape *ps2 = new Ellipse;   // Good
ps2->draw();                // OK, call Ellipse::draw()

ps1->Shape::draw();         // OK, call Shape::draw()
```

이 부분은 일반(비순수) 가상 함수에 대한 기본 구현을 종전보다 안전하게 제공하는 메커니즘으로도 활용 가능
<br><br>

# Simple virtual function, error

```c++
class Shape
{
public:
    virtual void error(const std::string& msg);
}
```

단순 가상 함수를 선언하는 목적은 파생 클래스로 하여금 함수의 인터페이스뿐만 아니라 그 함수의 기본 구현도 물려받게 하자는 것  
=> *"error 함수는 여러분이 지원해야 해요. 그러나 굳이 새로 만들 생각이 없다면 Shape 클래스에 있는 기본 버전을 그냥 쓰세요."*
<br><br>
알고 보면 단순 가상 함수에서 함수 인터페이스와 기본 구현을 한꺼번에 지정하도록 내버려 두는 것은 위험할 수도 있다.
<br>

## Airpot example
```c++
class Airport {};

class Airplane
{
public:
    virtual void fly(const Airport& destination);
    ...
};

void Airplane::fly(const Airport& destination)
{
    // Go to the destination airport (Default fly)
}

class ModelA: public Airplane {};
class ModelB: public Airplane {};
```

fly 함수는 가상 함수로 선언되어 있다. 이것의 의미는,,
1. 모든 비행기는 fly 함수를 지원해야 한다.
2. 모델이 다른 비행기는 원칙상 fly 함수에 대한 구현을 저마다 다르게 요구할 수 있다는 사실을 알고 있다.
3. 하지만 ModelA, ModelB 클래스에 똑같은 코드를 작성하지는 말아야 하므로 기존적인 비행 원리를 기본 함수로 제공한다.
<br>

이는 결국 아래와 같은 특징을 갖게 된다.
1. 클래스 사이의 공콩 사항으로 둘 수 있는 특징이 명확해 지고,
2. 코드가 중복되지 않으며
3. 기능 개선의 통로도 열려 있게 되고
4. 장기적인 유지 보수도 쉬어진다.
<br>

라는 고전적인 객체 지향 설계의 장점을 가진다.
<br><br><br>

이 때, XYZ 항공사에 비행방식이 완전히 다른 C 모델이 추가되었는데,<br>
개발자들이 그만 fly 함수를 재정의하는 것을 잊고 말았다.<br>
<br><br>

```c++
class ModelC: public Airplane
{
    // fly method is not declared
}
...

Airport PDX(...);

Airplane *pa = new ModelC;
...
pa->fly(PDX);   // Airplane::fly() is called
```

ModelC 는 결국 ModelA 또는 ModelB 처럼 날아가게 된다.<br>
=> Airplane::fly 함수가 기본 동작을 구현해서 갖고 있는 문제가 아닌, ModelC 클래스가 이 기본 동작을 원한다고 명시적으로 밝히지 않았는데도 이 동작을 물려받는 데 아무런 걸림돌이 없다는 것
<br>
<br>

## Solution 1
가상 함수의 인터페이스와 그 가상 함수의 기본 구현을 잇는 연결 관계를 끊어 버린다.
1. Airplane::fly 를 순수 가상 함수로 변경
2. defaultFly 함수를 선언
<br>

derived class 에서는 필요시 fly 함수를 재정의 하여 사용할 수도 있고,  
기본 함수가 필요할 때에는 Airplane::defaultFly 를 함수를 wrapping 하여 사용한다.
<br>

```c++
class Airplane
{
public:
    virtual void fly(const Airport& destination) = 0;
    ...
protected:
    void defaultfly(const Airport& destination);
};

void Airplane::defaultFly(const Airport& destination
{
    // 주어진 목적지로 비행기를 날려 보내는 기본 동작 원리를 가진 코드
}

...

class ModelA: public Airplane
{
public:
    virtual void fly(const Airport& destination)
    {
        defaultfly(destination);
    }
};

class ModelB: public Airplane
{
public:
    virtual void fly(const Airport& destination)
    {
        defaultfly(destination);
    }
}
```
<br>

### Airplane::defaultFly()
1. protected member : 사용자는 "비행기가 날 수 있다"만 알면된다, "어떻게 구현되는가"는 알 필요가 없다.
2. Non virtual function : derived class 에서 이 함수를 재정의하게 되면 결국 위와 똑같은 문제에 직면할 수 있다.
<br><br><br>

## Solution 2
순수 가상 함수가 구체 파생 클래스에서 재선언되어야 하는 사실을 활용하되, 자체적으로 순수 가상 함수의 구현을 구비해 둔다.
1. Airplane::fly 를 순수 가상 함수로 선언한다.
2. Airplane::fly 함수의 기본 구현을 정의한다.
3. derived class 에서 필요시 명시적으로 Airplane::fly 를 호출한다.
<br>

```c++
class Airplane
{
public:
    virtual void fly(const Airport& destination) = 0;
    ...
};

void
Airplane::fly(const Airport& destination)
{
    // 주어진 목적지로 비행기를 날려 보내는 기본 코드
}

class ModelA: public Airplane
{
public:
    virtual void fly(const Airport& destination)
    {
        Airplane::fly(destination);
    }
};

class ModelB: public Airplane
{
public:
    virtual void fly(const Airport& destination)
    {
        Airplane::fly(destination);
    }
};

class ModelC: public Airplane
{
public:
    virtual vodi fly(const Airport& destination);
    ...
};

void
ModelC::fly(const Airport& destination)
{
    // 주어진 목적지로 ModelC 비행기를 날려 보내는 코드
};
```
이전 solution 과 다른 점은,,,  
기본 비행 원리를 담고 있는 fly 함수가 public 으로 선언되어 노출되었다는 것이다.  
이전 solution 에서는 defaultFly 함수를 protected 로 선언하여 외부에 노출되지 않도록 캡슐화 되어 있었다.
<br><br>

# Non virtual function, objectID()
member 함수가 비가상 함수로 되어 있다는 것은, 파생 클래스에서 다른 행동이 일어날 것으로 가정하지 않았다는 뜻.  
비가상 함수는 클래스 파생에 상관없는 불변동작과 같다.
<br>
<br>
**비가상 함수를 선언하는 목적은 파생 클래스가 함수 인터페이스와 더불어 그 함수의 필수적인 구현을 물려받게 하는 것**



