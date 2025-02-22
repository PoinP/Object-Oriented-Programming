# Указатели към функции
Функциите не са по-различни от променливите в това, че те също трябва да се намират някъде в паметта. 

Ако някога сте се опитвали да принтирате функция, по погрешка или от интерес, може да сте се срещнали с подобен резултат:


```cpp
int sum(int a, int b)
{
    return a + b;
}
```
```cpp
cout << sum; 
```
Примерен изход:
```
00007FF7A0E91000
```

С други думи, когато подадем идентификаторът на функция на `cout`, ще видим адреса на тази функция.  

Разликата между променливи и функции е че променливите съдържат специфични **стойности**, а функциите - **инструкции**. Можем да направим *указател* към функция по следния начин:

```
<return type> (*<identifier>)([<type> <identifier>]);

<return type> (*<identifier>)([<type>]);
```

Това може да изглежда малко стряскащо, но ето как изглежда с по-практични примери:

```cpp
int (*foo)(int number1, int number2);

bool (*bar)(bool, int);
```

Първият пример е указател към функция, която връща int, и приема като параметри 2 int-а. Идентификатора/името на този указател е `foo`.  
Вторият пример е указател към функция, която връща bool, и приема 1 bool и 1 int. Идентификатора на този указател е `bar`.


За да присвоим някаква стойност към този указател, просто го правим както с нормална променлива:

```cpp
bool isPositive(int number)
{
    return number >= 0;
}

int main()
{
    bool (*foo)(int) = isPositive;

    cout << foo(15) << endl; // true
    cout << foo(-2);         // false
}
```
---

На практика, тази техника често се използва, когато искаме да приложим някаква функция върху много елементи на някаква колекция (напр. масив). Един вид такава функция е `map`. Тя има за цел да обходи всеки елемент на масива, като му прилага дадена фунцкия и го замести с резултата от функцията.

```cpp
void map(int* arr, int size, int (*mappingFunction)(int))
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = mappingFunction(arr[i]);
    }
}
```

Тук `mappingFunction` е указател към функция, който приема един `int`, трансформира го по някакъв начин, и връща друг `int`. 

Идеята е, че вместо да пишем много различни функции, които да обхождат масива и да го променят, ще напишем само един (`map`), а за да променим стойностите на елементите, ще пишем по-прости функции. 

```cpp
void map(int* arr, int size, int (*mappingFunction)(int))
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = mappingFunction(arr[i]);
    }
}

int times2(int element)
{
    return element * 2;
}

int square(int element)
{
    return element * element;
}

int main()
{
    int arr[5] {1, 2, 3, 4, 5};
    
    map(arr, 5, times2); // 2  4  6  8  10
    map(arr, 5, square); // 4 16 36 64 100
}
```

# Ламбда изрази
Ламбда изразите са *анонимни функции*, тоест функции без име. Те са дълга и сложна тема, като на този етап ще разгледаме само по-базовите части. Ламбда функция се дефинира по следния начин

```cpp
[]() -> <return_type> {}
```

Задължителни елементи на една ламбда: <br>
Квадратните скоби `[]` се наричат *Capture Clause* или *Capture Closure*, но няма да се възползваме от него на този етап.  
Кръглите скоби `()` указват параметрите на функцията.  
Къдравите скоби `{}` са тялото на функцията. 

Опционални елементи: <br>
-> <return_type> е елемент, който не е задължителен. Той експлицитно оказва типа, който връща ламбдата. В общия случай, той не е нужен, защото `C++` сам разбира типа, който връща ламбдата от нейното тяло.

С други думи, по-горния код можем да го пренапишем по следния начин:

```cpp
void map(int* arr, int size, int (*mappingFunction)(int))
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = mappingFunction(arr[i]);
    }
}

int main()
{
    int arr[5] {1, 2, 3, 4, 5};
    
    map(arr, 5, [](int e){return e * 2}); // 2  4  6  8  10
    map(arr, 5, [](int e){return e * e}); // 4 16 36 64 100

    // или

    map(arr, 5, [](int e) -> int {return e * 2}); // 2  4  6  8  10
    map(arr, 5, [](int e) -> int {return e * e}); // 4 16 36 64 100
}
```

# Изброен тип (enum)

`enum` е начин да дефинираме множество от именувани стойности, които в основата си представляват цели числа. Използват се за по-ясен и четим код, особено когато работим със състояния, опции или флагове. Той ни позволява да дефинираме нов тип променлива/константа.

Декларираме enum по следния начин:
```cpp
enum <name>
{
    <enumerator1>,
    <enumerator2>,
    <enumerator3>,
    ...
};
```
Стойностите на енумераторите са нарастващи, започващи от 0 и от първия елемент.

Пример:
```cpp
enum Color
{
    Red,    // 0
    Green,  // 1
    Blue    // 2
};

int main()
{
    Color color = Green;
    cout << color; // 1
}
```
---
Можем да променим стойността на някой енумератор, като броенето ще продължи след него отново в нарастващ ред.

```cpp
enum ErrorCode
{
    BadRequest = 400,           // 400
    Unauthorized,               // 401
    PaymentRequired,            // 402
    Forbidden,                  // 403
    NotFound,                   // 404
    InternalServerError = 500,  // 500
    NotImplemented,             // 501
    BadGateway,                 // 502
    ServiceUnavailable          // 503
    CustomRequest = 600         // 600
    PersonalRequest = 600       // 600
    // Възможно е два енумератора да имат еднакви стойности
};

int main()
{
    ErrorCode code1 = NotFound; // 404

    ErrorCode code2 = 502; 

    ErrorCode code3 = 1000; // Също е валидно
}
```

---

На този тип `enum` могат да се присвояват произволни целочислени числа. Това означава, че е позолено прилагането на числа, които не са част от енумераторите на нашия `enum`. Това може да доведе до трудни за дебъгване проблеми и грешки в кода.

```cpp
enum ErrorCode
{
    BadRequest = 400,           // 400
    Unauthorized,               // 401
    PaymentRequired,            // 402
};

void handleError(ErrorCode errCode)
{
    switch(errCode)
    {
        case BadRequest: std::cout << "Bad request handled"; break;
        case Unauthorized: std::cout << "Unauthorized request handled"; break;
        case PaymentRequired: std::cout << "Payment required error handled"; break;
        default: std::cout << "Illegal error! Crash!";
    }
}

int main()
{
    handleError(BadRequest); // OK
    handleError(23); // Ще се компилира и ще работи, но не е окей, защото може да доведе до грешки
}
```

Друга причина е, че имената на енумераторите са глобални, тоест може лесно да се случи препокриване(`shadowing` или `ambiguity`). 

```cpp
enum ColorChannel
{
    Red,    // 0
    Green,  // 1
    Blue    // 2
};

enum PageColor
{
    Red,    // 0
    Purple,  // 1
    Blue    // 2
};

int main()
{
    ColorChannel color = Red // Error
}
```

За да задължим програмиста да посочва от къде взима енумераторите, пишем `enum class`. За да посочим от къде взимаме дадена стойност, използваме `::`(`scope operator`).

Това ще ни задължи да преобразуваме експилицтно (`explicit casting`) за да записваме/четем целочислени стойности.

```cpp
enum class Color
{
    Red,    // 0
    Green,  // 1
    Blue    // 2
};

void showColor(Color color)
{
    switch(color)
    {
        case Red: std::cout << "Showing red..."; break;
        case Green: std::cout << "Showing green..."; break;
        case Blue: std::cout << "Showing blue..."; break;
        default: std::cout << "No such color!";
    }
}

int main()
{
    Color color = Green;        // ERROR
    Color color = Color::Green; // OK

    Color color = 1;            // ERROR
    Color color = (Color)1;     // OK

    cout << color;              // ERROR
    cout << (int)color;         // OK

    showColor(Color::Blue)      // OK
    showColor(Blue)             // ERROR

    showColor((Color)2)         // OK
    showColor(2);               // ERROR
}
```

По подразбиране всички `enum`-и са от тип `int`. Като езика ни позолява сами да си изберем целичисления тип, който нашия `enum` ще има.

```cpp
enum ErrorCode : char           // Големина на enum-а -> 1B(8 bytes)
{
    BadRequest = 400,           // 400
    Unauthorized,               // 401
    PaymentRequired,            // 402
};

enum class Color : short        // Големина на enum-а -> 2B(16 bytes)
{
    Red,
    Green,
    Blue
};

enum class Part                 // Големина на enum-а -> 4B(32 bytes)
{
    CPU,
    GPU,
    PSU
};

enum class Weekend : double     // ERROR (double не е целичислен тип)
{
    SATURDAY,
    SUNDAY
};
```

> Енумерациите е прието да се пишат или UPPER_CASE или PascalCase. Изберете си един от двата начина и използвайте само него