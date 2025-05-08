# Полиморфизъм, Абстрактни класове, Интерфейси

В езика C++ имаме два основни вида свързвания:

- Статично - изборът на функция, която да се изпълни се случва по време на компилация
- Динамично - изборът на функция, която да се изпълни се случва по време на изпълнение

До сега ние сме се срещали единствено и само със статичен начин на изпълнение на функциите. С помощта на виртуалните методи, вече ще можем да извикваме функции динамично, като избираме коя функция да се изпълни по време на изпълнение на програмата.

## Полиморфизъм

Полиморфизмът а последната основа на обектно-ориентираното програмиране. Така всички основи биват:

- Енкапсулация
- Наследяване
- Полиморфизъм
- Абстрация

Полимофризъм означава, че един обект може да се държи по няколко различни начина зависимост от типа, който съдържа. За да се получи това, трябва да поговрим за основни идеи, свързани с него:

- Реализира се с помощта на виртуални методи
- Класовете на които се прилага трябва да имат общ родител/базов клас
- Конструкторите НЕ могат да бъдат виртуални
- Имаме ли виртуален метод в даден клас, то той трябва задължително да има и виртуален деструктор
- Всеки клас може да дефинира или да дефинира даден виртуален метод на базов клас
- Реализирането на полиформизъм за осъществява чрез указател или референция към базов клас
- Искаме ли да копираме полиформни обекти, то трябва да съществува клониращ виртуален метод

Обикновено, когато говорим за полиморфни обекти, те трябва да са заделени в динамичната памет, но това не винаги е така!

Виртуалните методи се описват като им се постави думата `virtual` пред тях.

```cpp
class Animal
{
public:
    virtual void makeNoise() const
    {
        std::cout << "Default Noise\n";
    }

    // Задължително деструктора трябва да е виртуален
    virtual ~Animal() = default;
};

// Ако деструктора на базовия клас е виртуален, то
// виртуалността на деструктора се наследява.
// Тоест не е нужно да пишем деструктор в класовете
// наследници, освен ако те не се занимават с динамична памет
// (ресурси за освобождаване при унищожаване на обекта)

class Cat : public Animal
{
public:
    // Думичката override не е задължителна,
    // но е много силно препоръчителна.
    // Тя ще даде компилационна грешка, ако
    // не правим override на виртуален метод.
    // Тук можем също да сложим virtual пред
    // метода, но не е добра практика.
    // override е достатъчно.
    void makeNoise() const override
    {
        std::cout << "Meow\n";
    }
};

class Dog : public Animal
{
public:
    void makeNoise() const override
    {
        std::cout << "Woof\n";
    }

    // Можем да имаме допълнителни виртуални методи
    virtual void fetchStick() const
    {
        std::cout << "Fetching...\n";
    }
};

int main() 
{
    Animal a;
    a.makeNoise(); // Default Noise

    Animal* aPtr = new Animal();
    aPtr->makeNoise(); // Default Noise

    delete aPtr;
    aPtr = new Dog();
    aPtr->makeNoise(); // Woof

    delete aPtr;
    aPtr = new Cat();
    aPtr->makeNoise(); // Meow

    delete aPtr;

    Cat c;
    Dog d;

    // Не е нужно да са заделени динамично
    aPtr = &c;
    aPtr->makeNoise(); // Meow

    // Не е нужно да са заделени динамично
    Animal& aRef = d;
    aRef.makeNoise(); // Woof

    a = c; // OK Animal = Cat
    a.makeNoise(); // Deafult Noise, the same as in inheritance

    a = d; // OK Animal = Dog
    a.makeNoise(); // Default Noise, the same as in inheritance
}
```

Но защо последните две извиквания на `makeNoise()` не извикват правиланите функции? Специфично на `Cat` и след това на `Dog`?

## Виртуална таблица (`vtable`)

Това е така заради т.нар. виртуална таблица, която се създава автоматично след като опишем някой метод като виртуален. Тя пази масив от указатели към виртуалните методи на всеки обект. При извикване на виртуален метод чрез указател или референция, се прави индиректен достъп до реалната функция чрез `vtable` масива.

Няма да навлизам в детайли за нея, само е нужно да знаете, че съществува за да разберете защо последните два метода извикват функционалността на базовия клас, а не на наследниците, както по-горе. И че тя е отговорна за динамичното извикване(`dynamic dispatch`) на методите.

Същата е идеята с деструктора. Ако нямахме указател към деструктора ни чрез `vtable`, то при изтриване на обекта щеше да се извика само деструктора на базовия клас. Тоест при извикването на `delete aPtr;` щеше да се извика само деструктора на `Animal`. Но благодарение на `dynamic dispatching` се вика деструктора на реалния тип отодлу, който започва процеса по унищожаване на обекта.

> Имплементацията на тази таблица зависи от използвания компилатор

## Абстрактен клас

Чисто виртуалните(`pure virtual`) методи са такива виртуални методи, които нямат имплементация. Такива виртуални методи трябва да се `override`-нат задължително от наследяващия ги клас, за да могат да се създават иснтанции от него.

`! Ако даден клас има чисто виртуален метод, то не може да се прави инстанция от него !`

Такъв клас се нарича **абстрактен клас**

```cpp
// Abstract class
class Shape
{
public:
    virtual ~Shape() = default;

    // Pure virtual
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;

    virtual const char* getName() const = 0 
    {
        // Това е позволено!
        return "Unknown Name";
    }

    virtual bool isValid() const { return true; }

    void printData() const
    {
        std::cout << "P = " << getPerimeter() << "\n";
        std::cout << "S = " << getArea() << std::endl;
    }
};

// Concrete type
class Square5 : public Shape
{
public:
    double getArea() const override { return 5 * 5; }
    double getPerimeter() const override { return 4 * 5; }

    const char* getName() const override { return "Square"; }
  
    // isValid has a default implementation, so I do not need to
    // override it. I must override all of the pure virtual methods though
    // If I do not override one of the pure virutals, Square5 will be an abstract class.
    // This means I won't be able to create objects of type Square5
}

// Abstract class
class Square10 : public Shape
{
public:
    double getArea() const override { return 10 * 10; }
    double getPerimeter() const override { return 4 * 10; }

    // getName() const may have an implementation, howver it is still
    // a pure virtual and must be overriden in order for Square10 to not be
    // an abstract class!
}

int main()
{
    // Shape s; Error! Shape is abstract
    Square5 sq5; // OK
    // Square10 sq10; Error! Square10 is abstract. It does not implement getName() const

    Shape* shapePtr; // OK
    // Следователно...
    shapePtr = &sq5; // OK
    // Или...
    shapePtr = new Square5(); // OK
    delete shapePtr;

    // shapePtr = new Square10(); Error! Square10 is abstract. It does not implement getName() const
}
```

> Като задача за читателя ще оставя да се помисли защо бихме имали имплементация на `pure virtual` метод и по каквъ начин можем да извикаме неговата имплементация.

Абстрактен клас е такъв клас, който в себе си има поне един `pure virtual` метод,

## Интерфейс

Интерфейс е такъв клас, който има в себе си само `pure virtual` методи, и няма никакво състояние(полета).

```cpp
class CloudManipulator
{
public:
    virtual ~CloudManipulator() noexcept = default;

    virtual void conmect(const char* connectionUri) = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const;

    virtual void uploadFile(const char* filePathUri) const = 0;
    virtual void downloadFile(const char* fileUri, const char* savePath) const = 0;

    virtual void createBucket(const char* bucketName) const = 0;
    virtual void deleteBucket(const char* bucketName, int internalId) const = 0;
}
```

Интерфейсът описва "какво" трябва да се направи, а не "как" да се направи.

## `final`

`final` описва, че даден клас не може да се наследява повече или даден метод не може да се `override`-ва повече.

```cpp
class Base
{
public:
    virtual void print() const = 0;
};

class Child : public Base
{
public:
    void print() const final { std::cout << "Hey!"; }
};

class Last final : public Base
{
public:
    void print() const final { std::cout << "Hey!"; }
};

class ChildInherited : public Child
{
public:
    // void print() const override { std::cout << "Child inherited!"; } // Error
};

// class LastInherited : public Last // - Error
// {
// }
```

## Хетерогенен контейнер (*TODO*)

Накратко това е контейнер(най-често масив), който съдържа масив от указатели(или референции) към тип с виртуална функционалност. Така примерно може в контейнер от указатели към `Shape` да пазим `Square`, `Triangle`, `Circle` и т.н.

## `clone` метод (*TODO*)

Ако искаме да позволим на един хетерогенен контейнер или като цяло на базов полиморфен тип да се копира, то трябва да си направим за всеки наследник `clone` метод.

```cpp
class Shape
{
public:
    ...
    virtual Shape* clone() const = 0;
    ...
};

class Circle : public Shape
{
public:
    ...
    Circle* clone() const override
    {
        return new Circle(*this);
    }
    ...
};

class Triangle : public Shape
{
public:
    ...
    Triangle* clone() const override
    {
        return new Triangle(*this);
    }
    ...
};

// и така нататък

int main()
{
    // Сега ако имаме хетерогенен контейнер:
    Shape* shapes[5] {
        new Triangle(),
        new Circle(),
        new Circle(),
        new Triangle(),
        new Circle()
    };

    // Можем да го копираме по следния начин:
    Shape* shapesCopy[5];
    for (size_t i = 0; i < 5; i++)
    {
        shapesCopy[i] = shapes[i]->clone();
    }

    for (size_t i = 0; i < 5; i++)
    {
        delete shapes[i];
        delete shapesCopy[i];
    }
}
```

ВАЖНО: относно типа на връщане на `clone()`.
Правилно е да се връща указател от типа, който копираме, а не от базовия тип. Тоест ако имаме: `virtual Shape* clone() const = 0;` трябва да имплементираме този метод за `Triangle`: `Triangle* clone() const override`.

Компилаторът няма да ни се скара ако върнем `Shape*` при клонирането на `Triangle`, но НЕ е правилно!

## `dynamic_cast` (*TODO*)

Накратко - позволява преобразуване на указател от базов тип към производен тип. Връща указател към производния тип, ако е успешно преобразуването, `nullptr` в противен случай.