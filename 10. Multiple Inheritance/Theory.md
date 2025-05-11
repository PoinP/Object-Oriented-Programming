# Множествено наследяване. Виртуално наследяване.

Множественото наследяване е механизъм в `C++`, който позволява на един клас да наследява повече от един базов клас.

```cpp
class A 
{
public:
    void show() { std::cout << "A\n"; }
};

class B 
{
public:
    void display() { std::cout << "B\n"; }
};

class C : public A, public B 
{
    // Наследява членовете и от A, и от B
};
```

Плюсове:
- Позволява ни по-гъвкаво моделиране – клас може да комбинира функционалност от няколко източника и улесянва повторната употреба на код.

Недостатъци:
- Може да доведе до конфликти на имена, ако два базови класа имат членове със същото име.
- Диамантения проблем

## Диамантения проблем

Той възниква, когато два класа наследяват един и същ базов клас, а след това трети клас ги наследява и двата.

```cpp
class A 
{
public:
    int value;
};

class B : public A {};
class C : public A {};

class D : public B, public C {};
```

При тази ситуация, класът `D` ще съдържа две копия на `A::value` - едното, което идва от `B`, а другото - идващо от `C`. Това води до еднозначност.

```cpp
// main.cpp

D obj;
// obj.value = 5; // Грешка: нееднозначност, кой value?
obj.B::value = 5;
obj.C::value = 10;
```

Димантения проблем се среща и в стандартната библиотека на езика и по-точно в `std::iostream` и `std::ofstream`.

![](assets/ios-inheritance.png)

## Виртуално наследяване

`C++` предоставя решениена този проблем, като се използва виртуално наследяване. То гарантира, че само едно копие от членовете на базовия клас ще бъде налично, независимо колко пъти той е наследен по пътя.

```cpp
class A 
{
public:
    int value;
};

class B : virtual public A {};
class C : virtual public A {};

class D : public B, public C {};
```

Забележете, че наследяваме виртуално само и едниствено най-базовия клас. Тоест ние трябва да наследим виртуално този клас, който е проблемния. Сега вече `B` вика конструктора на `A`, `C` вика конструктора на `A` и `D` вика конструктора на `A`.

И сега ще си кажете ама как така? Нали всеки клас си вика конструкторите на прекия за него базов клас. Как така `D` ще вика на `A`?

Ами това е така, защото наследим ли виртуално даден клас, то неговото състояние се създава в класа, от който се създава обект. Тоест ако имахме буквите `E`, `F` и т.н. всяка от тях трябваше да извика конструктора на `A` експлицитно.

Причината за това е, че по този начин имаме само една инстанция(състояние) на `A` и то се създава при появата на който и да е дъщерен клас.

```cpp
#include <iostream>

class A 
{
public:
    A(int val) : value(val) {}
    int value;
};

class B : virtual public A 
{
public:
    B() : A(2) {}
};

class C : virtual public A
{
public:
    C() : A(3) {}
};

class D : public B, public C {
public:
    D(int num) : A(4) { }
};

class F : public D 
{
public:
    F() : F(0.0) {}
    F(double balance) : A(5), D(6) {}
};

class E : public D
{
public:
    E() : A(7), D(0) {};
};
```

Тук отново имаме виртуална таблица. Виртуалното наследяване инструктира компилатора да споделя едно общо копие на базовия клас, което се управлява чрез вътрешна виртуална таблица (`vtable`). 

## Пример

> Приемаме, че сме си направили `BasicString`, който има предефиниран `operator<<` за принтиране в поток

```cpp
#include <iostream>

#include "BasicString"

class Device 
{
public:
    BasicString id;

    Device(const BasicString& id) : id(id) 
    {
        std::cout << "Device constructed: " << id << "\n";
    }

    void status() const 
    {
        std::cout << "Device [" << id << "] is operational.\n";
    }
};

class InputDevice : virtual public Device 
{
public:
    InputDevice(const BasicString& id) : Device(id) 
    {
        std::cout << "InputDevice constructed\n";
    }

    void read() const 
    {
        std::cout << "Reading data from device [" << id << "]\n";
    }
};

class OutputDevice : virtual public Device 
{
public:
    OutputDevice(const BasicString& id) : Device(id) 
    {
        std::cout << "OutputDevice constructed\n";
    }

    void write(const BasicString& data) const 
    {
        std::cout << "Writing '" << data << "' to device [" << id << "]\n";
    }
};

class IODevice : public InputDevice, public OutputDevice 
{
public:
    IODevice(const BasicString& id)
        : IODevice(id), InputDevice(id), OutputDevice(id) 
    {
        std::cout << "IODevice constructed\n";
    }
};
```

```cpp
int main() {
    IODevice device("USB123");

    device.status();
    device.read();
    device.write("Hello, world!");

    return 0;
}
```

```
Device constructed: USB123
InputDevice constructed
OutputDevice constructed
IODevice constructed
Device [USB123] is operational.
Reading data from device [USB123]
Writing 'Hello, world!' to device [USB123]
```

Ако `Devic` не бъде виртуално наследен, тогава `IODevice` би имал две копия на `Device` – едно от `InputDevice`, едно от `OutputDevice`, което би довело до:
- двусмисленост при достъп до id и status().
- грешка от компилатора при извикване на device.status().

Виртуалното наследяване гарантира, че ще съществува само едно общо копие на `Device`.