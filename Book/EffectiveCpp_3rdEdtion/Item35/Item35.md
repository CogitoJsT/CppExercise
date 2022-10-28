# Item35 : 가상 함수 대신 쓸 것들도 생각해 두는 자세를 시시때때로 길러 두자
가상 함수를 대신할 수 있는 여러 전략에 대해 소개한다.
- 비가상 인터페이스 관용구를 통한 템플릿 메서드 패턴
- 함수 포인터로 구현한 전략 패턴
- std::function 으로 구현한 전략 패턴
- 고전적인 전략 패턴
<br><br>

## Background
각종 캐릭터를 설계하는 작업을 하는데, 캐릭터의 체력이 얼마나 남았는지 나타내는 healthValue 라는 멤버 함수를 제공한다.  
<br>

```c++
class GameCharacter
{
public:
    virtual int healthValue() const;
}
```
순수 가상 함수가 아닌 것으로 보아 체력치를 계산하는 기본 알고리즘이 제공된다는 사실을 알 수 있음
<br><br>

# 비가상 인터페이스 관용구를 통한 템플릿 메서드 패턴

## 가상 함수 은폐론
가상 함수는 반드시 private 멤버로 두어야 한다.

1. healthValue 를 public 멤버 함수로 그대로 두되, 비가상 함수로 선언
2. 내부적인 실제 동작은 private 가상 함수를 호출
<br><br>

```c++
class GameCharacter
{
public:
    int healthValue() const // 가상 함수의 wrapper
    {
        ... // preprocessing 을 수행합니다.
        
        int retVal = doHealthValue();   // 실제 동작을 수행합니다.

        ... // postprocessing 을 수행합니다.

        return retVal;
    }
    ...
private:
    virtual int doHealthValue() const   // 파생 클래스는 이 함수를 재정의할 수 있습니다.
    {
        ... // 캐릭터의 체력치 계산을 위한 기본 알고리즘 구현
    }
}
```
사용자로 하여금 public 비가상 멤버 함수를 통해 private 가상 함수를 간접적으로 호출하게 만드는 방법<br>
=> ```비가상 함수 인터페이스 (Non-Virtual Interface)``` or ```Template method pattern```
<br><br>
  
  - 가상 함수가 호출되기 전에 어떤 상태를 구성하고 가상 함수가 호출된 후에 그 상태를 없애는 작업이 wrapper를 통해 공간적으로 보장된다.
  - 예로 뮤텍스 잠금, 로그 정보, 클래스이 불변속성, 함수의 사전조건이 만족되었는지를 검증 등의 사전 작업
  - 뮤텍스 해체, 함수의 사후조건을 점검, 클래스의 불변속성을 재검증 하는 등의 사후 작업
  - 만약 사용작 쪽에서 가상 함수를 직접 호출하도록 했다면, 사전/사후 동작을 끼워 넣을 좋은 방법이 없음
<br><br>

## private 가상 함수 재정의
- 가상 함수를 재정의하는 일은 어떤 동작을 ```어떻게``` 구현할 것인가를 지정하는 것
- 가상 함수를 호출하는 일은 그 동작이 ```수행될 시점```을 지정하는 것  
```
NVI 관점에서는 파생 클래스의 가상 함수 재정의를 허용하기 때문에 어떤 기능을 어떻게 구현할지를 조정하는 권한은 파생 클래스가 갖게 되지만, 함수를 언제 호출할지를 결정하는 것은 기본 클래스만의 고유 권한이다.
```
<br>

## 가상 함수가 엄격히 private 일 필요는 없다
- 파생 클래스에서 재정의되는 가상 함수가 기본 클래스의 대응 함수(같은 이름의 가상 함수)를 호출할 것을 예상하고 설게된 것도 있음  
  => ```Window::onResize()```
- 이런 경우 적법한 함수 호출이 되려면 가상 함수가 protected 로 선언되어야 함
<br><br><br>

# 함수 포인터로 구현한 전략 패턴
가상 함수를 전혀 사용하지 않은 설계
- 체력치 계산이 구태여 어떤 캐릭터의 일부일 필요가 없다.
- 각 캐릭터의 생성자에 체력치 계산용 함수의 포인터를 넘기고, 이 함수를 호출해서 계산한다.
<br><br>

```c++
class GameCharacter; // Foward declaration

// 체력치 계산에 대한 기본 알고리즘 구현한 함수
int defaultHealthCalc(const GameCharacter &gc);

class GameCharacter
{
public:
    typedef int (*HealthCalcFunc)(const GameCharacter&);

    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
        : healthFunc(hcf);
    {}

    int healthValue() const
    {
        return healthFunc(*this);
    }
    ...
private:
    HealthCalcFunc healthFunc;
}
```

## Strategy Pattern
위의 코드는 전략 패턴(Strategy Pattern)의 한 예이다.  
<br>

### Good point
- 같은 캐릭터 타입으로부터 만들어진 객체(인스턴스)들도 체력치 계산 함수를 각각 다르게 가질 수 있음
<br>

```c++
class EvilBadGuy: public GameCharacter
{
public:
    explicit EvilBadGuy(healthCalcFunc hcf = defaultHealthCalc)
        : GameCharacter(hcf)
    {
        ...
    }
    ...
};

int loseHealthQuickly(const GameCharacter &);   // 다른 동작원리로 구현된 체력치 계산 함수들
int loseHealthSlowly(const GameCharacter &);


EvilBadGuy ebg1(loseHealthQuickly); // 같은 타입인데도 체력치 변화가 다르게 나오는 캐릭터들
EvilBadGuy ebg2(loseHealthSlowly);
```
- 게임이 실행되는 도중에 특정 캐릭터에 대한 체력치 계산 함수 변경 가능하다.
<br><br>

### Bad point
- 체력치 계산 함수는 더이상 GameCharacter 클래스 계통의 멤버 함수가 아니다.  
  => ```체력치가 계산되는 대상 객체의 비공개 데이터는 이 함수로 접근이 불가능```
```
사실 이 부분은 클래스 내부의 기능을 그 클래스의 바깥에 있는 동등한 기능으로 대체하려고 하면 언제든 생기는 고민거리이다.  
public 영역에 없는 부분을 비멤버 함수도 접근할 수 있게 하려면 그 클래스이 캡슐화를 약화시키는 방법밖에는 없다.
(비멤버 함수를 프렌드로 선언한다던지, 숨겨 놓는 것이 더 나을지도 모르는 세부 구현 사항에 대한 접근자 함수를 public 멤버로 제공하는 등)
```
<br>

### Conclusion
함수 포인터를 통해 얻는 이점들이 과연 GameCharacter 클래스의 캡슐화를 떨어뜨리면서 얻는 불이익을 채워 줄지 아닐지는 스스로 판단
<br><br>

# std::function으로 구현한 전략 패턴
function pointer 를 이용한 구현에 대한 의문
- 체력치 계산을 왜 꼭 함수가 해야 해? function object 쓰면 안돼나?
- 반드시 함수여야 한다면, 멤버 함수는 왜 안돼?
- 반환 값을 int로 바꿀 수 있는 임의의 타입이면 충분할거 같은데, 왜 꼭 int 가 아니면 안돼?
<br><br>

## std::function 을 사용하여 의문점들 해결

```c++
class GameCharacter;                        // 이전과 동일
int defaultHealthCalc(const GameCharacter); // 이전과 동일

class GameCharacter
{
public:
    using HealthCalcFunc = std::function<int (const GameCharacter&)>;

    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
        : healthFunc(hcf)
    {
        ...
    }

    int healthValue() const
    {
        return healthFunc(*this);
    }
    ...
private:
    HealthCalcFunc healthFunc;
};
```

```HealthCalcFunc``` 은 std::function 템플릿을 인스턴스화한 것이다.  
=> 이 타입은 일반화된 함수 포인터 타입처럼 동작한다.
<br><br>
std::function<```int (const GameCharacter&)```>
<br>
이 시그니처를 그대로 읽으면
- ```const GameCharacter``` 에 대한 참조자를 받고 ```int```를 반환하는 함수
- 이렇게 정의된 std::function 타입으로 만들어진 객체는 대상 시그니처와 호환되는 함수호출성 개체를 어떤 것도 가질 수 있다.<br>
- 호환된다는 말은,,,  
  1. 함수호출성 개체의 매개변수 타입이 const GameCharacter& 이거나 const GameCharacter& 으로 암시적 변환이 가능한 타입이며,
  2. 반환 타입도 암시적으로 int 로 변환될 수 있다는 것을 의미
<br><br>

## std::function 의 융통성
함수 포인터를 이용한 구현과 비교했을 때 큰 차이는 없지만 std::function을 사용함으로써 좀 더 ```일반화된 함수 포인터```를 사용하게 됨

```c++
short calcHealth(const GameCharacter&); // 체력치 계산 함수. 
                                        // 반환 타입이 int가 아닌 부분에 주목

struct HealthCalculator
{
    int operator() (const GameCharacter&) const
    {
        ...
    }
};

class GameLevel
{
public:
    float health(const GameCharacter&) const;   // 체력치 계산에 쓰일 멤버 함수 
    ...                                         // 반환 타입이 int 가 아닌 부분에 주목
};


class GameCharacter             // 이전과 동일
{
public:
    using HealthCalcFunc = std::function<int (const GameCharacter&)>;

    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
        : healthFunc(hcf)
    {
        ...
    }

    int healthValue() const
    {
        return healthFunc(*this);
    }
    ...
private:
    HealthCalcFunc healthFunc;
};

class EvilBadGuy: public GameCharacter  // 이전과 동일
{
public:
    explicit EvilBadGuy(healthCalcFunc hcf = defaultHealthCalc)
        : GameCharacter(hcf)
    {
        ...
    }
    ...
터

class EyeCandyCharacter: public GameCharacter  // 새로운 캐릭터 타입. 
{
public:
    explicit EyeCandyCharacter(healthCalcFunc hcf = defaultHealthCalc)
        : GameCharacter(hcf)
    {
        ...
    }
    ...
}


EvilBadGuy ebg1(calcHealth);    // 체력치 계산을 위한 함수를 사용하는 캐릭터

EyeCandyCharacter ecc1(HealthCalculator()); // 체력치 계산을 위한 함수 객체를 사용한 캐릭터

GameLevel currentLevel;
...

EvilBadGuy ebg2(
        std::bind(&GameCharacter::health,  // 체력치 계산을 위한 멤버 함수를 사용하는 캐릭터
                  &currentLevel,
                  std::placeholder_1)
        );

```