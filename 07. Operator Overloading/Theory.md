# Предефиниране на оператори (Operator overloading)

Предефинирането на опратори позволява на потребителски дефинираните типове да използват вече познатите за езика оператори като `+`, `-`, `*`, `/`, `->`, `==`, `!=`, `<<`, `>>` и т.н. Така ако имаме клас към който може да се прибавят и премахват елементи, ние бихме могли да използваме операторите `+` и `-`, вместо да създаваме методите `add()` и `remove()`

Пример с клас, който представя комплексно число:

```cpp
Complex complexNum1(5, 3);
Complex complexNum2(9, 12);

// We can do this
Complex complexNum3 = complexNum1.add(complexNum2);

// Or this (static add method)
Complex complexNum4 = Complex::add(complexNum1, complexNum2);

// Or this (operator + is overloaded)
Complex complexNum5 = complexNum1 + complexNum2;
```

> Един оператор, който вече предефинирахме е `operator=`


## Как се предефинира оператор?

Предефинирането на даден оператор се случва много подобно на създаването на функция или метод в езика. Като следва следния синтаксис:  
`<return_type> operator<op>([params])`

- `return_type` - Типът, който връща операторът
- `op` - Операторът, който бихме искали да предефинираме
- `params` - Параметрите, които приема операторът

```cpp
class Point
{
public:
    Point() : x(0.f), y(0.f) {}
    Point(float x, float y) : x(x), y(y) {}

    Point& operator+=(const Point& rhs) // rhs is short for right hand side
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

private:
    float x;
    float y;
};

Point operator+(Point lhs, const Point& rhs)
{
    lhs += rhs;
    return lhs;

    // OR: 
    // return lhs += rhs
}

int main()
{
    Point p1(3.f, 4.f);
    Point p2(2.4f, 4.23f);

    Point p3 = p1 + p2; // (1)
    // OR
    Point p4 = operator+(p1, p2); // (2)

    p3 += p2; // (3)
    // OR
    p4.operator+=(p2); // (4)
}
```

Предефинирането на оператори може да става както под формата на методи в класовете, така и под формата на обикновени функции. Следователно те могат да се викат директно през оператора `(1), (3)`, което се пада **синтактична захар** на извикването им като нормални фунции/методи `(2), (4)`.

## Бинарни и унарни оператори

Броят на параметрите, които очаква един предефиниран оператор зависи от това дали той е под формата на метод или функция.

Под формата на фунцкия обикновено:
- Унрарен оператор: Приема само един параметър
- Бинарен оператор: Приема само два параметъра

Под формата на метод обикновено:
- Унрарен оператор: Не приема параметри. Елемента на който се прилага операторът е `*this`
- Бинарен оператор: Приема само един параметър. Левият елемент на операторът е `*this`, а десният - подаденият параметър

> Най-отдолу на този файл има връзка към страница която описва всеки оператор в езика колко параметъра приема, когато е метод и когато е функция

## Оператори, които могат да се предефинират

Всички оператори в езика могат да се предефинират освен:
- `.` - Class member selector operator
- `.*` - Pointer class member selector
- `::` - Scope resolution operator
- `?:` - Ternary operator
- `sizeof` - Size of operator
- `alignof` - Align of operator
- `typeid` - Type Id oprator

## Особености

Операторът `[]` може да приема аргументи от всякакъв тип. **НЕ Е ЗАДЪЛЖИТЕЛНО ДА Е ЦЯЛО ЧИСЛО**

### Оператор `()`

Всички оператори освен операторът `()` приемат точно определен брой параметри. Операторът `()` може да приеме колкото параметри ние си искаме(дори 0). Ако предефинираме този оператор, вече обектът ни може да се изпозлва като функция. Класове, които предефинират този оператор се наричат **функтори**

### Специфични осеобени оператори
Има оператори, които могат да се предефинират само и единствено под формата на функция или на метод.

Други особени оператори са:
- Предефиниране на литерали `R operator "" _b(T a)` (може да бъде само функция)
- Начин на преобразуване към друг тип `operator C();` (може да бъде само метод и няма тип на връщане)
- `new` и `delete` (могат да бъдат както функции, така и методи)

---

- `R` - Типа, който връща операторът
- `_b` - Името на литерала
- `T` - Типа на параметъра за литерала
- `C` - Типа към който може да се преобразува обекта чиито метод е операторът

### Операторите ++ и --
Специален случай са постинкрементален и преинкрементален `operator++`. Тъй като в езика всички оператори започват с думата `operator`, няма такова нещо като `++operato`r. За да се направи разлика между двете се поставя параметър `int`, който не се използва.  
Когато този помощен параметър присъства, говорим за постинкрементална операция.  
Когато го няма - за преинкрементална операция.

***Продължаваме класа `Point`***
```cpp
class Point
{
public:
    ...

    Point& operator++() // (1)
    {
        x++;
        y++;
        return *this;
    }

    Point operator++(int) // (2)
    {
        Point oldPoint(*this); // Save the current state
        operator++(); // Call the prefix operator++

        // OR
        // ++*this; 
        // OR
        // x++;
        // y++;

        return oldPoint;
    }

    ...
private:
    ...
};

int main()
{
    Point p;
    ++p; // Calls (1)
    p++; // Calls (2)
}
```

## Външно и вътрешно предефиниране на оператори

Външно предефиниране на оператор наричаме функция, която предефинира определен оператор.  
Вътрешно - метод в даден клас, който предефинира определен оператор.

Оператор, който е предефиниран вътрешно има достъп до всички данни на даден клас (`public`, `private`, `protected`). Докато външните оператори имат достъп само до публичните методи на параметрите, които приемат.  
Тоест можем да си дефинираме `operator+` по два начина:

```cpp
class Point
{
public:
    Point() : x(0.f), y(0.f) {}
    Point(float x, float y) : x(x), y(y) {}

    Point& operator+=(const Point& rhs) // rhs is short for right hand side
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

private:
    float x;
    float y;
};

Point operator+(Point& lhs, const Point& rhs)
{
    lhs += rhs;
    return lhs;

    // OR: 
    // return lhs += rhs
}
```

и

```cpp
class Point
{
public:
    Point() : x(0.f), y(0.f) {}
    Point(float x, float y) : x(x), y(y) {}

    Point& operator+=(const Point& rhs) // rhs is short for right hand side
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Point operator+(const Point& rhs)
    {
        return Point(x + rhs.x, y + rhs.y);
    }

private:
    float x;
    float y;
};
```

> В първия случай `operator+` няма достъп до `*this`, защото е външен за класа

Понякога обаче, даден оператор не можем да го направим вътрешен, но трябва да достъпи елементи на обекта, които не са публични...

## Операторите за извеждане и въвеждане в поток >> и <<

Операторите за извеждане и въвеждане в поток винаги приемат порока като първи параметър и връщат потока обратно. Понякога искаме да изведем на екрана състоянието на даден обект, но да не съществуват `get`-ъри за неговите полета. Тогава можем да използваме `friend`.

`friend` позволява на дадена функция да има достъп до вътрешното(`private` и `protected`) състояние на обекти от даден клас.

```cpp
#include <iostream>

class Point
{
public:
    Point() : x(0.f), y(0.f) {}
    Point(float x, float y) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& outStream, const Point& point);
    friend std::istream& operator>>(std::istream& inStream, Point& point);

private:
    float x;
    float y;
};

std::ostream& operator<<(std::ostream& outStream, const Point& point)
{
    outStream << "Point(" << point.x << ", " << point.y << ")";
    return outStream;
}

std::istream& operator>>(std::istream& inStream, Point& point)
{
    inStream >> point.x >> point.y;
    return inStream;
}
```

> `friend` функциите не са част от класа ни, а само позволение на функция с такава сигнатура да достъпва private член данните.

> Ако е възможно, е хубаво да се избягва `friend`. Най-често ако класът ни има подходящите `get`-ъри и `set`-ъри, не се налага да създаваме такова позволение.

```cpp
#include <iostream>

class Point
{
public:
    Point() : x(0.f), y(0.f) {}
    Point(float x, float y) : x(x), y(y) {}

    float getX() const;
    float getY() const;

    void setX(float x);
    void setY(float y);

private:
    float x;
    float y;
};

std::ostream& operator<<(std::ostream& outStream, const Point& point)
{
    outStream << "Point(" << point.getX() << ", " << point.getY() << ")";
    return outStream;
}

std::istream& operator>>(std::istream& inStream, Point& point)
{
    float x, y;
    inStream >> x >> y;

    point.setX(x);
    point.setY(y);

    return inStream;
}
```

## Добри практики

- Предефиниявайте операторите така, че тяхното поведение да е очаквано. Тоест `+` събира или прилепя елементи, а не премахва елементи.
- Предефинирайте оператори с `const` методи, ако не модифицират обекта.
- За бинарни оператори като `+`, `-`, `*` и т.н. използвайте `copy-and-modify` подхода (използвайки `+=`, `*=` и т.н.). Пример за това е най-първия пример в този документ.
- За симетрични оператори (като `==`, `!=`) може да дефинирате единия и да изградите другия чрез него.
- Използвайте `friend`, когато лявата страна не е обект от същия клас или когато трябва да имате достъп до `private`/`protected` членове. Често може да се избегне!
- Ако съществува `operator+`, то тогава трябва да се осигури и `operator+=`.
- За `operator[]` — хубаво е да имате и константна версия (`const BigObject& operator[](int idx) const`), ако работите с константен обект. И следователно - `BigObject& operator[](int idx)`


Полезен линк с всички оператори и техните сигнатури:
[Operators in C and C++](https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B)