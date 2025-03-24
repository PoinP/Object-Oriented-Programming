# Класове - жизнен цикъл

> Всичко описано за класовете тук, важи и за структурите

Класовете(както и структурите) разполагат с два основни метода, които се извикват по време на създаването и на унищожаването на един обект. Тези методи се наричат конструктори и деструктор.

## Конструктури и деструктури

Конструктурите се извикват тогава, когато един обект бъде създаден, а деструктора - когато обектът излезе извън обхвата в който е дефиниран или не се изтрие ръчно(когато е динамично заделен)

Конструктурите и деструктурите са специфични методи, чиито имена предстваляват името на класа(или структурата).

```cpp
class User
{
public:
    User();
    User(const char* name, unsigned age, const char* email);
    ~User();

private:
    char* name;
    unsigned age;
    char* email;
};
```

Можем да имаме колкото си искаме конструктора и точно един деструктор.  
Като конструкторите се делят на два вида:
- Конструктор по подразбиране (конструктор без параметри)
- Конструктор с парамтери

`User()` и `User(const char* name, unsigned age, const char* email)` са конструктори на класа `User`. `User()` е конструктор по подразбиране, а `User(const char* name, unsigned age, const char* email)` е конструктор с параметри.  
`~User()` играе роля на деструктор в класа `User`

```cpp
class ConstructorsExample
{
    public:
        ConstructorsExample() { std::cout << "Object created with default ctor\n"; }
        ConstructorsExample(int x, int y) { std::cout << "Object created with secondary ctor\n"; }
        ~ConstructorsExample() { std::cout << "Object destroyed"; }
};

int main()
{
    ConstructorsExample objWithDefaultCtor;
    ConstructorsExample objWithSecondaryCtor(2, 3);

    std::cout << "The two objects have been created\n";
}
```

Изходът от тази програма е:
```
Object created with default ctor
Object created with secondary ctor
The two objects have been created
Object destroyed
Object destroyed
```

Забележете как при конструктора по подразбиране не пишем `()`. Докато при конструктора с параметри, описваме неговите аргументи с `()`. Причината за това е, че когато използваме празни скоби при конструктора по подразбиране, езикът приема, че това е функция която не приема параметри и връща типа на обекта ни.

Цялата идея на конструкторите е да направят състоянието на обекта валидно и готово за първоначално използване. Това означава, че в конструкторите се заделя някаква нужна динамична памет или пък се зануляват полетата с цел обекта да бъде готов за използване.

Деструкторите от друга страна имат за цел да освобдят заделените ресурси за обекта. В общия случай в деструктора се освобождава всичката заделена динамична памет за полетата на обекта.

Конструкторите се викат при първоначалното създаване на обекта, а деструкторите - при унищожаване на обекта.

## Конструктори

Конструкторът има допълнителен синтаксис, които се използва при задаване на стойности на полетата на класа.

```cpp
class Triangle
{
public:
    Triangle(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

private:
    int x;
    int y;
    int z;
};
```

Този конструктор би ни свършил работа, но не е напълно оптимален. Това е така, защото преди да започне да се изпълнява тялото на конструктора, се създават всички полета на класа. Тоест в началото на тялото вече са създадени променливите `x`, `y` и `z` и са с някакви случайни стойности. След това ние ръчно променяме стойностите на `x`, `y` и `z`.

Конструкторите ни позволяват да зададем стойности на полетата още при тяхното създаване:
```cpp
class Triangle
{
public:
    Triangle(int x, int y, int z)
        : x(x), y(y), z(z)
    {
    }

private:
    int x;
    int y;
    int z;
};
```

Алтернативен запис с променени имена на полеатата за повече яснота
```cpp
class Triangle
{
public:
    Triangle(int x, int y, int z)
        : _x(x), _y(y), _z(z)
    {
    }

private:
    int _x;
    int _y;
    int _z;
};
```

Сега вече задаваме стойнсоти на полетата още при тяхното създаване. Това е ключово ако нямаме конструктор по подразбиране. Защо? Както казахме, точно преди да се изпълни тялото на конструктора, се създават всички полета. Но няма как да се създаде поле, което не притежава конструктор по подразбиране по този начин. Затова такова поле е задължително да се създаде в `member initializer list`-а.

Можем да си мислим, че следната имплементация:
```cpp
class Triangle
{
public:
    Triangle(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

private:
    int x;
    int y;
    int z;
};
```

Реално прави следното нещо:
```cpp
class Triangle
{
public:
    Triangle(int x, int y, int z)
        : x(), y(), z()
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

private:
    int x;
    int y;
    int z;
};
```

Така де, извиква се конструктора по подразбиране на всяко поле.

```cpp
class Triangle
{
public:
    Triangle(int x, int y, int z)
        : _x(x), _y(y), _z(z)
    {
    }

private:
    int _x;
    int _y;
    int _z;
};

class IndexedTriangle
{
public:
    IndexedTriangle(int x, int y, int z, short index) // ERROR
    {
        this->triangle = Triangle(x, y, z);
        this->index = index;
    }   
    
private:
    Triangle triangle;
    short index
};
```

По-горния код няма да се компилира, защото `Triangle` няма конструктор по подразбиране. Следователно ние трябва да опишем кода по-горе по следния начин:
```cpp
class Triangle
{
public:
    Triangle(int x, int y, int z)
        : _x(x), _y(y), _z(z)
    {
    }

private:
    int _x;
    int _y;
    int _z;
};

class IndexedTriangle
{
public:
    IndexedTriangle(int x, int y, int z, short index)
        : triangle(x, y, z),
          index(index)
    {
    }   
    
private:
    Triangle triangle;
    short index
};
```

> На `index` може да му се зададе стойността и в тялото на конструктора, но е по-правилно чрез `member initializer list`

> **Понякога не е възможно да се създаде поле чрез `member initializer list`**

Чрез `member initializer list` можем да извикваме и други конструктори.

```cpp
class Triangle
{
public:
    Traingle()
        : Triangle(0, 0, 0)
    {}

    Triangle(int side)
        : Triangle(side, side, side)
    {}

    Triangle(int sameSide, int otherSide)
        : Triangle(sameSide, sameSide, otherSide)
    {}

    Triangle(int x, int y, int z)
        : x(x), y(y), z(z)
    {}

private:
    int x;
    int y;
    int z;
}
```

### Ред на инициализиране на полетата

Реда в който се инициализират полетата зависи от реда в който са декларирани в класа.

```cpp
class EqualiteralTriangle
{
public:
    EqualiteralTriangle(int side)
        : z(x), y(x), x(side)
    {
    }

private:
    int x;
    int y;
    int z;
}
```

Тук всичко е окей! Първо се инциализира `x` със стойнсотта `side`, защото `x` е декларирано преди `y` и `z`. След това се инициализира `y` и след това `z`.

**ВАЖНО: Реда в който се описват полетата в конструкотра няма значение. Има значение реда в който са декларирани в класа**

```cpp
class EqualiteralTriangle
{
public:
    EqualiteralTriangle(int side)
        : z(x), y(x), x(side)
    {
    }

private:
    int y;
    int x;
    int z;
}
```

След изпълнението на този код `y` ще има някаква случайна стойност.

### Копиращ конструкотр

Същестува специфичен конструктор, който се нарича копиращ конструктор. Той има следната сигнатура

```cpp
class Triangle
{
public:
    Triangle();
    Traingle(const Triangle&); // Copy constructor

private:
    int x;
    int y;
    int z;
};
```

Неговата цел е да опише начин по който да се копират полетата от един обект в `this` обекта. Такъва конструктор създаваме експлицитно тогава когато някое от полетата ни съдържа някакъв вид динамична памет. В противен случай не е нужно и автоматично генерирания копиращ конструктор е достаъчен.

### Копиращ оператор за присвояване

Ако си създадем собствен копиращ конструктор е задължително да си дефинираме и собствен оператор за копиране.

```cpp
class Person
{
public:
    Person(const char* name) // Secondary ctor
    {
        if (name != nullptr)
        {
            unsigned nameLength = strlen(name);
            this->name = new char[nameLength + 1];
            strcpy(this->name, name);

            // this->name = strcpy(new char[strlen(name) + 1], name);
        }
        else
        {
            const char* unknownName = "";
            unsigned nameLength = strlen(unknownName);
            this->name = new char[unknownName + 1];
            strcpy(this->name, unknownName);

            // this->name = strcpy(new char[strlen("") + 1], "");
        }
    }

    Person(const Person& other)  // Copy ctor
        : Person(other.name)
    {
    }

    Person& operator=(const Person& other) // Copy assignment operator
    {
        if (this != &other)
        {
            delete[] this->name;
            unsigned nameLength = strlen(other.name);
            this->name = new char[nameLength + 1];
            strcpy(this->name, other.name);
        }

        return *this
    }

    ~Person()
    {
        delete[] name;
    }

private:
    char* name
}
```

Забележете следната логика при копиращия оператор за присвояване:

```cpp
if (this != &other)
{
    // Copy logic
}
```

Това е така, защото `other` може да бъде реално същия обект като this. Затова ние сравняваме техните адреси и ако са различни, чак тогава извърваме копирането, защото в протвен случай може да се получи **теч на памет**

Имаме следния код:
```cpp
int main()
{
    Person p("Ivan Kolev");
    p = p;
}
```

Тук ако при оператора за присвояване нямахме проверката от по-горе, то тогава щеше да се получи работа с памет, която не е наша. Ето кода, който описва поведението на оператора (тук е без проверката):

```cpp
Person& operator=(const Person& other) // Copy assignment operator
{
    delete[] this->name;
    unsigned nameLength = strlen(other.name);
    this->name = new char[nameLength + 1];
    strcpy(this->name, other.name);

    return *this
}
```

В `p` първоначално има заделена памет за `Ivan Kolev`. След като извикваме оператора за присвояване, изтриваме вече заделената памет. Така като `this` и `other` са реално едно и също нещо, ние изтриваме `name` от `this` и `other`. Когато извикаме `strlen` с указател към изтрита памет, се получава недефинирано поведение и може да доведе до множество грешки.

Добре нека имаме следния код и да помислим кога какво се вика:
```cpp
int main()
{
    Person myPerson("Nikoleta Nikolova"); // Конструктор с параметър
    Person secondPerson = "Monika Dimitrova" // Конструктор с параметър
    Person thirdPerson = myPerson; // Копиращ конструктор
    myPerson = secondPerson; // Копиращ оператор за присвояване
}
```

При първите три примера се създават нови обекти от тип `Person` и за това се извиква някой от дефинираните конструктори. При последния пример обектът `myPerson` е вече създаден и заради това се извиква оператора за присвояване. Втори и трети ред са аналогични на `Person secondPerson("Monika Dimitrova")` и `Person thirdPerson(myPerson);`. Просто това са особености на езика. Ако искаме да предотвратим това държание можем да използваме ключовата дума `explicit`.

> Имаме ли дефиниран копиращ конструктор, то тогва трябва задължително да дефинираме и копиращ оператор за присвояване

**Когато говорим за голямата четворка, ние имаме предвид:**
- Конструктор
- Копиращ конструктор
- Копиращ оператор за присвояване
- Деструктор

> *ВАЖНО:* Винаги когато класа ни има някаква динамична памет(тоест ресурс за който отговрая) ние си имплементираме *голямата четворка*.

### Move конструктор и Move оператор за присвояване

Тях ще ги прескочим в този документ. Те са важни и от значение, но за тях ще си говорим на семинарните упражнения и не са жизнено важни за завършването на предмета. Идеята им е много подобна на копиращия конструктор и копиращия оператор за присвояване. Просто тук данните не се копират ами се променя кой е техния собственик.

Когато включим и Move семантиката към нашия клас, той вече се придържа към т. нар. голяма шестица:
- Конструктор
- Копиращ конструктор
- Копиращ оператор за присвояване
- Move конструктор
- Move оператор за присвояване
- Деструктор


### Автоматично генерирани елементи

Обикновено когато съдадем един клас се създават автоматично:
- Конструктор по подразбиране
- Копиращ конструктор
- Копиращ оператор за присвояване
- Move конструктор
- Move оператор за присвояване
- Деструктор

Ако някое от полетата на класа изтрие по някакъв начин някой от тези конструктори, то тогава такъв конструктор няма да се създаде автоматично.

Ако създадем конструктор с параметри, то тогава няма да се генерира конструктор по подразбиране.

Ако създадем копиращ конструктор, то тогава няма да се генерира копиращ оператор за присвояване, Move конструктор и Move оператор за присвояване.

Ако създадем копиращ оператор за присвояване, то тогава няма да се генерира копиращ конструктор, Move конструктор и Move оператор за присвояване.

Същото важи и за Move аналозите.

Можем да изтрием някой от описаните конструктори/оператори с ключовата дума `delete` или да накраме езика да използва поведението по подразбиране с `default`

```cpp
class Triangle
{
public:
    Triangle() = default;
    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = default;
    ~Traingle() = default;
};
```

### Деструктор

Основната цел на деструктора е да освободи заделените ресурси(динамичната памет) на класа.