# Изклюения, ключовата дума `static`, `const` полета

## Изключения и тяхната обряботка
Изключенията(`Exceptions`) представляват механизъм по който да се обработват грешки по време на изпълнението на кода. Те се използват тогава, когато се случи нещо "изклчително" по време на изпълнението на кода.

Не всяка грешка възникнала по време на изпълнението на кода трябва да създаде изключение. Кога е по-правилно да обработим грешката и кога да създадем изключение зависи от контекста в който се изпълнява кода.

В C++ имаме три основни ключови думи:
- `throw` - Използва се за да създадем(или хвърлим) изключение
- `try` - Използва се за обграждане на блок от код, който е възможно да хвърли изключение
- `catch` - Използва се заедно с `try` и се използва за улавянето и обработването на изключения

> Важно е да се спомене, че при C++ всичко може да бъде `exception`

```cpp
#include <iostream>

int main()
{
    try
    {
        throw 12;
    }
    catch(int exceptionCode)
    {
        std::cout << "An exception with code " << exceptionCode << " was thrown!";
    }
    catch(...)
    {
        std::cout << "An unknown exception was thrown!";
    }
}
```

Ако някъде в `try` блока се хвърли грешка, то кодът по-надолу не се обработва. Когато се хвръли грешка в `try` блока, типа на грешката се прихваща от `catch`. В зависимост от това какъв тип е бил хвърлен, се изпълнява този `catch` блок, чиито параметър е същия тип. `catch(...)` прихваща всички възможни изключения. Тоест, ако хвърлим изключение с тип `int`, `catch(int exeptionCode)` ще прихване изключението и ще се изпълни неговото тяло. В противен случай ще се изпълни тялото на `catch(...)`. Можем да имаме колкото си `catch`-а искаме. Обработката се случва отгоре-надолу. Това означва, че първо се проверява дали типа принадлежи на първия `catch`, после на втория и така до последно дефинирания `catch` блок.

### Stack Unwinding
Това е процес при който езика автоматично "развива" стековата рамка, когато се хвърли някое изключение. По време на този процес, всички обекти започват да биват разрушавани в обратен ред на тяхното създаване, докато процеса не приключи. "Развиването" на стековата рамка продължава докато:
- Не стигне до `catch` блок, който може да прихване изхвърленото изключение
- Не съществува `catch` блок, който да прихване изхвърленото изключение

При първия случай ще бъдат разрушавани обекти, докато не се достигне до `catch` блок, който да успее да обработи изключението.  
При втория - всички обекти ще бъдат разрушени и накрая на `main` функцията ще се извика `std::terminate` което ще накара програмата да приключи нейното изпълнение.

Когато се хвърли едно изключение **НЕ** трябва да могат да се хвърлят други изключения по време на `Stack Unwinding` процеса. При изхвърляне на второ изключение, автоматично се извиква `std::terminate`.

> Това означава, че деструкторите **НЕ** трябва да могат да хвърлят изключения!

```cpp
class A {
public:
    A() { std::cout << "Created A\n"; }
    ~A() { std::cout << "Destroyed A\n"; }
};

class B {
public:
    B() { std::cout << "Created B\n"; }
    ~B() { std::cout << "Destroyed B\n"; }
};

int f() {
    A a;
    B b;
    throw 42; // Exception throw
    std::cout << "This won't be executed\n";
    return 681;
}

int main() {
    try {
        int value = f();
    }
    catch (int e) {
        std::cout << "An exception has been caught: " << e << "\n";
    }
    return 0;
}
```

Изход:
```
Created A
Created B
Destroyed B
Destroyed A
An exception has been caught: 42
```

Забележете, че функцията не връща нищо. Тя директно се прикратява заради хвърлянето на изключението и всички променливи в нея се унищожават.

Този пример показва една от най-големите сили на ООП-то и `RAII` идеологията. Деструкторите ще се погрижат за освобождаването на заделената памет, дори и при появата на изключение. Разбира се стига обектът да е бил създаден успешно. (*Изключения и конструктори ще се обсъдят по-надолу в документа*)

### Видове грешки
Въпреки, че езика ни позволява да хвърляме всичко под формата на изключение, това не е коректно. Правилния подход е всяко изключение да се върже към определен тип и чрез него да се предостави допълнителна информация за изключението.

В библиотеката `<stdexcept>` се съдържат основните типове изключения в езика. Ако искаме да хвърлим някое изключение, то тогава е хубаво да си изберем едно от тях или да си направим собствен клас, който да играе роля на изключение. (*В бъдеще ще си поговорим как е най-правилно да си направим `custom` изключение*)

Когато езикът хвърли изключение по време на използването на някои от вградените му функционалности, той хвърля изключения от `<std::except>`

Основни видове грешки в `<stdexcept>`:
- `std::bad_alloc` - Грешка, при заделянето на памет (може да се хвърли от `new`)
- `std::bad_cast` - Грешка, при преобразуването от един тип към друг
- `std::runtime_error` - Грешка, по време на изпълнението на програмата
- `std::logic_error` - Грешка, която описва грешки в логиката на програмата, които могат да бъдат предотвратени

Когато се опитваме да хванем обект от дадено изключение, ние винаги трябва да го прихващаме по константна референция и **НЕ** по копие.

Йерархия на изкюченията в `<stdexcept>`:

СНИМКА

```cpp
#include <cstring>
#include <iostream>
#include <stdexcept>

#pragma warning(disable:4996)

char* getGreeting(const char* name)
{
    if (!name)
        throw std::logic_error("nullptr is not a valid name");

    // Hello, <name>
    const unsigned prefixLength = 7;
    char* greeting = new char[prefixLength + strlen(name) + 1]; // 'new' may throw
    strcpy(greeting, "Hello, ");
    strcat(greeting, name);
    return greeting;
}

int main()
{
    try
    {
        std::cout << getGreeting("John") << "\n";       // May throw std::bad_alloc
        std::cout << getGreeting(nullptr) << std::endl; // Throws std::logic_error
    }
    catch(const std::logic_error& ex)
    {
        std::cout << "Invalid input!" << std::endl;
    }
    catch(const std::bad_alloc& ex)
    {
        std::cout << "Uh oh, there is not enough memory available!" << std::endl;
    }
    catch(const std::exception& ex) // Catches std::runtime_error as well!
    {
        std::cout << "A generic error has occured";
    }
    // No need to catch(...) every time. This time it's okay to not catch everything!
}
```

### Изключения и конструктори
Ако едно изкючение бъде хвърлено в конструктор, то тогава обекта няма да бъде създаден успешно. Това означава, че неговия деструктор няма да се извика. Един деструктор може да бъде извикван тогава и само тогава, когато неговия обект е създаден. В противен случай **деструкторът НЕ се извиква**.

```cpp
#include <cstring>

class Person
{
public:
    Person(char* firstName, char* lastName)
    {
        // We are taking at face value that firstName and lastName will be valid values
        this->firstName = new char[strlen(firstName) + 1]; // May throw std::bad_alloc
        // If the code above throws, everything is okay. No memory leak occurs
        strcpy(this->firstName, firstName); // Will not throw

        this->lastName = new char[strlen(lastName) + 1]; // May throw
        // If the code above throw, we have a memory leak! The constructor has not been
        // executed fully and gets short circuted by the exception. This means that the
        // destructor will NOT be called. The pointer to this->firstName will cease to exist
        // and we will have a memory leak!
        strcpy(this->lastName, lastName); // Will not throw
    }
private:
    char* firstName;
    char* lastName;
}
```

Горното парче код е проблемно в случай, че `new` хвърли изключение. Има два начина по които да се справим с проблема:

Начин 1:
```cpp
#include <cstring>

class Person
{
public:
    Person(char* firstName, char* lastName)
    {
        // We are taking at face value that firstName and lastName will be valid values
        this->firstName = new char[strlen(firstName) + 1]; // May throw std::bad_alloc
        // If the code above throws, everything is okay. No memory leak occurs
        strcpy(this->firstName, firstName); // Will not throw

        try 
        {
            this->lastName = new char[strlen(lastName) + 1]; // May throw
            strcpy(this->lastName, lastName); // Will not throw
        } catch (...) // We do not care what exception is throw. We just want to delete the allocated memory
        {
            delete[] firstName;
            // If the second new throws, we can catch it and delete the allocated memory
            // for this->firstName.
            throw;
            // This is important! After we handle the exception, we want to throw it back.
            // This way we can show the person using the code that some error has occured.
            // They(the person using the code) can catch the expcetion or just let it terminate the program.
        }
    }
private:
    char* firstName;
    char* lastName;
}
```

Начин 2:
```cpp
#include <new>
#include <cstring>

class Person
{
public:
    Person(char* firstName, char* lastName)
    {
        // We are taking at face value that firstName and lastName will be valid values
        this->firstName = new char[strlen(firstName) + 1]; // May throw std::bad_alloc
        // If the code above throws, everything is okay. No memory leak occurs
        strcpy(this->firstName, firstName); // Will not throw

        this->lastName = new(std::nothrow) char[strlen(lastName) + 1]; // May throw
        // If 'new' throws, it will catch it's exception and just set this-lastName to nullptr.
        // (std::nothrow) makes it return nullptr if it tries to throw an exception
        // In order to use std::nothrow, we need to include <new>
        if (!this->lastName)
        {
            delete[] firstName;
            throw std::bad_alloc();
            // Just like the last example, we would like to let the person using our code
            // that an error has occured.
        }

        strcpy(this->lastName, lastName); // Will not throw
    }
private:
    char* firstName;
    char* lastName;
}
```

В дестурктора **НИКОГА** не се хвърлят изключения!

### Exception safety
Когато с нашата програма или обект се получи някаква грешка е хубаво да знаем какво е състоянието им след прихващането на грешката. Същестуват четири основни нива на безопасност (`Exception safety`):

- `Nothrow` - Извършваната операция никога няма да хвърли изключение
- `Strong` - Ако дадена операция хвърли грешка, то състоянието на програмата (или обекта) ще остане в същото състояние преди да бъде хвърлена грешката.
- `Basic` - Ако дадена операция хвърли изкючение, то обектът, хвърлил изключението може да продължи да се използва. Но няма гаранция, че състоянието му е същото както преди изхвърлянето на изключението.
- `No guarantee` - Не е грантирано нищо. Ако един обект хвърли изключение, то програмата може да е в невалидно състояние: да има теч на памет, да има memory corruption и т.н.

|Ниво        |Изключение?  |Състояние на обекта        |Примерен случай            |
|------------|-------------|---------------------------|---------------------------|
|Nothrow     |	Никога     |Напълно запазено           |Деструктори, прости функции|
|Strong      |	Може       |Напълно запазенo           |Присвояване с копие        |
|Basic       |	Може       |Валидно, частично променено|Повечето C++ операции      |
|No guarantee|	Можe       |Неопределено               |Лошо написан код           |

Присвояване с копие означава първо да се създаде обект, чиито създаване може да хвърли изключение и чак тогава да се присвои с копиране.

Да кажем, че имаме клас `Person` и имплементираме коприащ оператор за присвояване.
```cpp
Person& Person::operator=(const Person& other)
{
    if (this != &other)
    {
        char* newFirstName = new(std::nothrow) char[strlen(other.firstName) + 1];
        char* newSecondName = new(std::nothrow) char[strlen(other.secondName) + 1];

        if (!newFirstName || !newSecondName)
        {
            delete[] newFirstName;
            delete[] newSecondName;
            throw std::bad_alloc();
        }

        this->firstName = newFirstName;
        this->secondName = newSecondName;
    }

    return *this;
}
```

Кода, който пишем **НИКОГА** не трябва да бъде `No guarantee`.

## `static`
`static` се държи по различен начин в зависимост от контекста в който се използва.

### `static` в променлива на фунцкия/метод
```cpp
#include <iostream>

void globalCounter() {
    static int count = 0;
    count += 1;
    std::cout << "Counted: " << count << std::endl;
}

int main()
{
    globalCount(); // Counted: 1
    globalCount(); // Counted: 2
    globalCount(); // Counted: 3 
}
```

Тук `count` се държи в глобалната(или статичната памет). Тази променлива ще се създаде само веднъж - при първото извикване на функцията. Така нейната стойност се запазва между извикванията. Тази променлива живее през целия живот на програмата. Тоест вече тя не се унищожава на края на обхвата(`scope`-а), ами чак в края на програмата.

Често се използва за: броячи, кеширане на информация и т.н.

### `static` поле(член променлива) в клас

```cpp
class MyClass {
public:
    static int counter;
};

int MyClass::counter = 0;  // дефиниция извън класа
// Дефинирането на статично поле става задължително по-този начин
// Може тази дефиниция да се напиша и в .cpp файла
```

`counter` е общо поле за всички обекти от класа. Това означава, че ако създам примерно пет обекта, то всеки от тях ще има достъп до един и същ `counter`. Ако един обект вдигне стойността на `counter` с 4, то всички обекти на този клас, ще имат достъп до обновената стойност. Тоест съществува само едно копие, независимо от това колко обекта ще създадем. Не е част от конкретна "инстанция" ами е част от класа.


```cpp
#include <iostream>

class MyClass {
public:
    static int publicCounter;
};

int MyClass::publicCounter = 0;

int main()
{
    MyClass obj1, obj2, obj3;

    obj1.publicCounter = 23;
    std::cout << obj1.publicCounter << "\n"; // 23
    std::cout << obj2.publicCounter << "\n"; // 23
    obj2.publicCounter = 99;
    std::cout << obj3.publicCounter << "\n"; // 99

    MyClass::publicCounter = 120;
    std::cout << obj1.publicCounter << "\n"; // 120
    std::cout << obj2.publicCounter << "\n"; // 120
    std::cout << obj3.publicCounter << "\n"; // 120
}
```

Често се използва за: пазене на глобално състояние на класа, броячи на обекти, конфигурации

### `static` метод на клас

```cpp
#include <iostream>

class MyClass {
public:
    static void show() {
        std::cout << "Static method!" << std::endl;
    }
};

int main()
{
    MyClass::show();
    MyClass object;
    object.show();
}
```

```cpp
#include <iostream>

class MyClass {
public:
    static void show() {
        std::cout << "Static method!" << std::endl;
        staticState = 12; // OK
        state = 10;  // Error
    }

private:
    int state;
    static int staticState;
};

int MyClass::staticState = 0;
```

Статичният метод може да се вика както без обект, така и с обект. Той няма достъп до `this`, следователно няма достъп до състоянието(полетата) на обекта. Но има достъп до всички статични полета на класа. Както статичните полета, така и статичните методи на са обвързани с даден обект, ами с даден клас.

Често се използва за: помощни функции, фабрични методи, операции със `static` членове.

### `static` свободна функция или променлива в `.cpp` файл (локална за файла)

```cpp
// Самостоятелна фунцкия във .cpp файл:
static void helperFunction() {
    // видима само в текущия файл (translation unit)
}
```

Тази функция(или променлива) е ограничена само за текущия `.cpp` файл. Тоест не е видима в който и да е друг файл. Прави върешна връзка (`internal linkage`).

Използва се за: капсулиране на логика, която не трябва да бъде достъпна извън файла (подобно на `private`).

> Вместо този методи вече се използват анонимни `namespace`-и, но за тях ще си говорим на по-късен етап.

> Не е нужно да разберете напълно четвъртия контекст. Важно е да сте напълно наясно с първите три конетекста!

|Контекст              |Какво прави static?                              |
|----------------------|-------------------------------------------------|
|Във функция           |Променлива със запазена стойност между извиквания|
|Член-променлива в клас|Обща стойност за всички обекти (едно копие)      |
|Член-функция (метод)  |Извиква се без обект, няма достъп до `this`      |
|Функция в .cpp файл   |Видима само в този файл (вътрешна връзка)        |

Общ пример:
```cpp
#include <iostream>

class Example {
public:
    static int count;

    Example() {
        count++;
    }

    static void printCount() {
        std::cout << "Created objects: " << count << std::endl;
    }

    void instanceMethod() {
        static int globalCounter = 0;
        globalCounter++;
        std::cout << "globalCounter: " << globalCounter << std::endl;
    }
};

// Static field definition
int Example::count = 0;

int main()
{
    Example ex1;
    Example ex2;

    ex1.printCount(); // Created objects: 2
    ex2.printCount(); // Created objects: 2

    ex1.instanceMethod(); // localCounter: 1
    ex1.instanceMethod(); // localCounter: 2

    ex2.instanceMethod(); // localCounter: 3
    ex2.instanceMethod(); // localCounter: 4
}
```

## `const` полета

`const` поле (член-променлива) в `C++` е такова, което не може да бъде променяно след инициализация. Това означава, че:
- трябва да бъде инициализирано при създаване на обекта
- не може да бъде присвоявана нова стойност по-късно

```cpp
class Identity {
private:
    const int id; // const поле

public:
    Identity(int value) : id(value) {} // инициализация в конструктора

    void printID() const {
        std::cout << "ID: " << id << std::endl;
    }
};
```

`id` е `const` следователно задължително трябва да се инциализира в `member initializer list`-a на конструктора. Ако се опитаме да го инзициализираме в тялото на конструктора, ще получим компилационна грешка.

```cpp
class Identity {
private:
    const int id; // const поле

public:
    Identity(int value) {
        id = value // Грешка! Не може да се инициализира в тялото
    }

    void printID() const {
        std::cout << "ID: " << id << std::endl;
    }
};
```

Когато имаме `const` поле:
- Задължително се инициализира в `member initializer list`-a
- Не може да се променя и да му се присвояват стойности => няма как да съществува `operator=`

В повечето случаи няма нужда да правим дадено поле константно, освен ако наистина не искаме да се променя по каквъто и да е начин(включително чрез копиращия оператор за присвояване).

Ако не искаме да можем да променяме дадено поле, но все пак искаме да можем да използваме копиращия оператор за присвояване, то тогава няма как да направим полето `const`. В този случай просто няма да съществуват публични методи, които да променят това поле.

Можем да имаме и `static const` полета.