# Item 38. "has-a" 혹은 "is-implemented-in-terms-of"를 모형화할 때는 객체 합성을 사용하자

## 합성 (composition)
- 어떤 타입의 객체들이 그와 다른 타입의 객체들을 포함하고 있을 경우에 성립하는 그 타입들 사이의 관계
- 포함된 객체들을 모아서 이들을 포함한 다른 객체를 합성한다는 의미
- layering, containment, aggregation(통합) 또는 embedding 으로도 불림
<br>

## Example source code
```c++
class Address                   // where someone lives
{
    ...
};

class PhoneNumber
{
    ...
};

class Person
{
public:
    ...
private:
    std::string name;           // composed object
    Address address;            // ditto
    PhoneNumber voiceNumber;    // ditto
    phoneNumber faxNumber;      // ditto
};
```
- Person class 가 나타내는 관게는 has-a 관계이다.

<br>

# Software domain
## Appplication domain
- 사람, 이동수단, 비디오 프레임 등 처럼 우리 일상생활에서 볼 수 있는 사물을 본 떠 객체화 한 것들이 속한 영역
- ```객체 합성이 application domain 에서 일어나면 has-a 관계이다.```

## Implementation domain
- 버퍼, 뮤텍스, 탐색 트리 등 순수하게 시스템 구현만을 위해 인공적으로 만들어진 객체들이 속한 영역
- ``` 객체 합성이 implementation domain 영역에서 일어나면 is-implemented-in-terms-of 관계이다.```
<br>
<br>

# Design Set class
set class 를 하나 설계한다고 가정
- 코드 재사용을 고려  
  => 라이브러리를 사용하자
- speed 보다는 memroy 사용을 더 고려  
  => 표준 라이브러리의 set template 는 pointer 3개를 사용하므로 제외
- list template을 사용하기로 결정

우선 아래와 같이 list 를 상속받아 설계한다.
<br>

```c++
template<typename T>
class Set: public std::list<T>
{
    ...
};
```

## Problem
1. 상속의 경우, base class 와 derived class 에 is-a 관계가 성립되어야 하는데 그렇지 않다.
2. 즉 base class 에서 true 인 것들이 derived class 에서도 true 이어야 하는데 그렇지 않다.  
=> list 객체는 중복 원소를 허용하지만 set 은 그렇지 않다. 만약 어떤 값이 list<int>에 두 번 insert 되면 리스트는 두 개의 중복 원소를 가지게 되는데 set에서는 허용되지 않는다.
<br>

## Solution
두 class 의 관계는 is-a 가 될 수 없다.  
아래처럼 is-implemented-in-terms-of 관계로 풀어야 한다. 

``` c++
template<class T>
class set
{
public:
    boo member(const T& item) const;
    void insert(const T& item);
    void remove(const T& item);

    std::size_t size() const;
private:
    std::list<T> rep;
};

template<typename T>
bool Set<T>::member(const T& item) const
{
    return std::find(rep.begin(), rep.end(), item) != rep.end();
}

template<typename T>
void Set<T>::insert(const T& item)
{
    if (!member(item))
    {
        rep.push_back(item);
    }
}

template<typename T>
void Set<T>::remove(const T& item)
{
    typename std::list<T>::iterator it = std::find(rep.begin(), rep.end(), item);

    if (it != rep.end())
    {
        rep.erase(it);
    }
}

template<typename T>
std::size_t Set<T>::size() const
{
    return rep.size();
}
```