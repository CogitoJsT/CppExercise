# Item 34. 인터페이스 상속과 구현 상속의 차이를 제대로 파악하고 구별하자

상속의 2가지 타입
- 함수 인터페이스 상속
- 함수 구현의 상속
<br>

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