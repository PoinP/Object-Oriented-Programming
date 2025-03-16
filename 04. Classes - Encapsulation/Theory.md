# Класове - Енкапсулация

## Основи на ООП-то

Обектно-ориентираното програмиране се гради върху четири основни идеи(`The four pillars`):
- Енкапуслация (`Encapsulation`)
- Наследяване (`Inheritance`)
- Полиморфизъм (`Polymorphism`)
- Абстракция (`Abstraction`)

В този документ ще се запознаем с това какво са класовете, как те са по-различни от структурите и какво точно е `encapsulation`.

## Клас

Класът, както структурата(`struct`) е начин по-който да пакетираме някаква обща информация за даден обект. Реално погледнато класовете са аналогични на структурите. Това означава, че всичко преподадено до момента за структурите важи и за класовете. Както структурите, класовете също могат да създават битови полета, имат същите правила за `layout`-ване и могат да се създават анонимни класове. Това означава, че ние можем да създадем клас по следния начин:

```cpp
class Mail
{
    char sender[32];
    char reciever[32];
    char content[256];
    bool delivered;
    int timestamp;
};
```

Но тук има една особеност. Класовете и структурите се различават само по **едно** нещо и това е **нивото на достъп до членовете им по-подразбиране**. При структурите ние можем да достъпваме всяко негово поле с операторите `.` или `->`. При класовете това съвсем не е така.

```cpp
int main()
{
    Mail myMail { "Ivan", "Petar", "Zdr Pesho :)", false, 450000 };
    std::cout << myMail.sender << "\n"; // Error
    std::cout << myMail.content << "\n"; // Error 
}
```

Не можем да достъпим член-данните на класа `Mail`, защото по подразбиране нивото на достъп при класовете е `private`, докато при структурите е `public`.

> Съществуват общо три нива на достъп в езика `public`, `protected`, `private`

Кой модификатор за достъп ограничава достъпа за кого може да видите в таблицата по-долу. `protected` е добавен за пълнота, с него ще се запознаем по-надълбоко когато вземем наследяване при класовете(и структурите)

| Модификатор за достъп:   | Достъп:                         |
|--------------------------|---------------------------------|
| `private`                | Само в текущия клас.            |
| `protected`              | В текущия клас и наследниците.  |
| `public`                 | От всеки                        |

Можем експлицитно да зададем модификатора за достъп по следния начин:

```cpp
class Mail
{
public:
    char sender[32];
    char reciever[32];
    char content[256];
    bool delivered;
    int timestamp;
};

int main()
{
    Mail myMail { "Ivan", "Petar", "Zdr Pesho :)", false, 450000 };
    std::cout << myMail.sender << "\n"; // OK
    std::cout << myMail.content << "\n"; // OK 
}
```

Всеички дефинирани полета и методи(член-функции) под `public:` вече могат да се достъпват извън самия клас.

Възможно е да дефинираме няколко модификатора за достъп:
```cpp
class Mail
{
public:
    char sender[32];
private:
    char reciever[32];
public:
    char content[256];
    bool delivered;
private:
    int timestamp;
};

int main()
{
    Mail myMail { "Ivan", "Petar", "Zdr Pesho :)", false, 450000 };
    std::cout << myMail.sender << "\n"; // OK
    std::cout << myMail.content << "\n"; // Error 
}
```

Вече `sender`, `content` и `delivered` са `public` и могат да се достъпват през създаден обект на класа, докато `reciever` и `timestamp` са `private` и могат да се достъпват само в самия клас. Това означава, че методите на класа имат достъп до всеки негов елемент(така като са част от класа).

## Методи (Член-функции)

В класовете както при структурите можем да си дефинираме методи или член-функции. Те се викат посредством създаден обект от класа(или структурата). Методите имат достъп до всички компоненти на един клас.

```cpp
class Mail
{
public:
    const char* getSender()
    {
        return sender;
    }

    bool isDelivered()
    {
        return delivered;
    }

private:
    char sender[32];
    char reciever[32];
    char content[256];
    bool delivered;
    int timestamp;
};

int main()
{
    Mail myMail { "Ivan", "Petar", "Zdr Pesho :)", false, 450000 };
    std::cout << myMail.getSender() << "\n"; // OK
    std::cout << myMail.isDelivered() << "\n"; // OK 
}
```

Имаме два основни вида методи(член-функции):
- Променящи (`mutable`)
- Константни (`const`)

Какъв ще бъде метода се определя от това какво върши той. Ако просто връща някаква информация, то тогава трябва да направим метода константен, в противен случай ако променя състоянието(някое от полетата) - трябва да бъде `mutable`.

> **ВАЖНО:** Когато връщаме указатели трябва много да внимаваме как ги връщаме! Ако искаме да върнем указател, който не променя състоянието на класа, то тогава трябва да върнем константен указател и да направим метода константен. В противен случай трябва да върнем нормален указател като метода **НЕ** трябва да бъде константен.(Трябва да бъде **`mutable`**)

```cpp
#include <cstring>

class Mail
{
public:
    const char* getSender() const // Константен метод
    {
        return sender;
    }

    char* getReciever() // mutable метод
    {
        return reciever;
    }

    bool isDelivered() const // Константен метод
    {
        return delivered;
    }

    void setContent(const char* newContent) // mutable метод
    {
        if (!newContent || strlen(newContent) > 255)
            return;

        strcpy(content, newContent);
    }

private:
    char sender[32];
    char reciever[32];
    char content[256];
    bool delivered;
    int timestamp;
};
```

Можем да имаме два метода с едно и също име, като единия е `const`, а другия `mutable`. Това е напълно валиден и често срещан `use-case`! 

```cpp
class Mail
{
public:
    const char* getSender() const // Константен метод
    {
        return sender;
    }

    char* getSender() // mutable метод
    {
        return sender;
    }
private:
    char sender[32];
    char reciever[32];
    char content[256];
    bool delivered;
    int timestamp;
};
```

`const` и `mutable` методите ни позволяват да контролираме кои методи могат да се използват при константни обекти и кои не могат. Те са ключов елемент в езика, който позволява да определим по точно какъв начин да се държи нашия клас.

```cpp
#include <cstring>

class Mail
{
public:
    const char* getSender() const // Константен метод
    {
        return sender;
    }

    char* getSender() // mutable метод
    {
        return sender;
    }

    bool isDelivered() const // Константен метод
    {
        // delivered = true; // Error, променя се състоянието в константен метод
        return delivered;
    }

    void setContent(const char* newContent) // mutable метод
    {
        if (!newContent || strlen(newContent) > 255)
            return;

        strcpy(content, newContent); // ОК, променя се състоянието в mutable метод
    }
private:
    char sender[32];
    char reciever[32];
    char content[256];
    bool delivered;
    int timestamp;
};

int main()
{
    Mail mutableMail { "Denkata", "Petar", "Zdr Pesho :)", false, 450000 };
    const Mail constMail { "Dobri", "Damyan", "Kude sa fakturite?", false, 450000 };

    mutableMail.isDelivered(); // OK
    mutableMail.setContent("Zdr, Pepi"); // OK
    mutableMail.getSender(); // OK - Връща char* (Извиква mutable метода)

    constMail.isDelivered() // OK
    constMail.setContent("Fakturite?") // Error
    constMail.getSender() // OK - Връща const char* (Извиква const метода)
}
```

Важно е да внимаваме кои методи правим `const` и кои методи правим `mutable`.

```cpp
#include <cstring>

class Mail
{
public:
    bool isDelivered() // mutable метод
    {
        return delivered;
    }

    void setContent(const char* newContent) const // const метод
    {
        if (!newContent || strlen(newContent) > 255)
            return;

        strcpy(newContent, content); // Error
    }
private:
    char sender[32];
    char reciever[32];
    char content[256];
    bool delivered;
    int timestamp;
};

int main()
{
    const Mail constMail { "Dobri", "Damyan", "Kude sa fakturite?", false, 450000 };
    constMail.setContent("Fakturite??"); // OK
    constMail.isDelivered(); // Error
}
```

> `strcpy(newContent, content);` ще даде грешка, но за целите на примера, нека кажем че ще се компилира и ще работи.

И сега какво се получава? Обекта ми е константен(тоест не се очаква да мога да променя състоянието му по какъвто и да е начин), но все пак мога да извикам `setContent` и да променя неговото състояние. Което е нелогично. Другото нелогично е, че не мога да извикам `isDelivered` въпреки че този метод не променя състоянието по какъвто и да е начин.  
Затова е важно да внимаваме кои методи правим `const` и кои `mutable`.

### Getters и Setters

Най-накратко това са такива методи, които позволяват модифицирането на състоянието на един обект, както и достъпа до някои от полетата му.

Пример за `getters` са методите от по-горе `isDelivered`, `getSender` и `getReciever`.  
Пример за `setter` е метода `setContent`.

> Забележете как `setContent` валидира по някакъв начин подадените данни. Това е основната идея на енкапсуалцията! `Getters` и `Setters` имат за цел да запазят вътрешното състояние на обекта валидно, независимо от това какви данни им се подадат. Тоест състоянието може да бъде достъпено и модифицирано само чрез зададените публични методи на класа.

### `this` - Указател към класа

`this` може да си го представим като допълнителен параметър, който се подава имплицитно(неявно) на всеки метод от един клас(или структура).

```cpp
class Square
{
public:
    double setWidth(double newWidth)
    {
        if (newWidth >= 0)
            width = newWidth;
    }

    double setHeight(double newHeight)
    {
        if (newHeight >= 0)
            height = newHeight;
    }

    double getArea() const
    {
        return width * height;
    }

private:
    double width = 0;
    double height = 0
}
```

Можем да си представим, че всеки методи изглежда по следния начин:
```cpp
double setWidth(Square* const this, double newWidth)
{
    if (newWidth >= 0)
        width = newWidth;
}

double setHeight(Square* const this, double newHeight)
{
    if (newHeight >= 0)
        height = newHeight;
}

double getArea(const Square* const this) const
{
    return width * height;
}
```

`this` се подава имплицитно от компилатора и представлява текущата инстанция на класа. И вече можем да достъпваме полета на класа по следния начин:

```cpp
class Square
{
public:
    double setWidth(double newWidth)
    {
        if (newWidth >= 0)
            this->width = newWidth;
    }

    double setHeight(double newHeight)
    {
        if (newHeight >= 0)
            this->height = newHeight;
    }

    double getArea() const
    {
        return this->width * this->height;
    }

private:
    double width = 0;
    double height = 0
}
```

Общо взето `this` представлява указател към текущата инстаниця на класа и всеки метод има достъп до него. Като `this` има различна репрезентация спрямо това дали се достъпва от `const` или `mutable` метод.

- Ако е от `const` метод - `const Class* const this`
- Ако е от `mutable` метод - `Class* const this`

> Не можем да променяме на къде сочи `this`!

Следния израз е валиден, но се използва рядко:

```cpp
class Square
{
public:
    void createNewSquare(Square square) const
    {
        *this = square;
    }

private:
    double width = 0;
    double height = 0
}
```

-----------------------------------------------------
При следните два метода ще се получи `shadowing`

```cpp
class Square
{
public:
    double setWidth(double width)
    {
        if (width >= 0)
            width = width;   // Работим само с параметъра тук
    }

    double setHeight(double height)
    {
        if (height >= 0)
            height = height;
    }

private:
    double width = 0;
    double height = 0
}
```

Можем да го оправим по следния начин:

```cpp
class Square
{
public:
    double setWidth(double width)
    {
        if (width >= 0)
            this->width = width;   // Работим само с параметъра тук
    }

    double setHeight(double height)
    {
        if (height >= 0)
            this->height = height;
    }

private:
    double width = 0;
    double height = 0
}
```

### `mutable` keyword

Това е такава ключова дума на езика, която се използва много рядко и не би трябвало да ви се наложи да я използвате в рамките на курса. Ситуациите в които би било удачно и правилно да се използва са **много редки**, затова **много внимавайте** с нея. 

> Добавена е към този документ с цел пълнота на изучавания материал. 

Това е такава ключова дума, която се прилага на поле(или полета) от един клас(или структура). Тези полета на които сме приложили `mutable` могат да бъдат променяни в `const` методи на класа.

```cpp
#include <cstring>

class Mail
{
public:
    bool isDelivered() const // Константен метод
    {
        delivered = true; // OK
        return delivered;
    }

    void setContent(const char* newContent) const // const метод
    {
        if (!newContent || strlen(newContent) > 255)
            return;

        strcpy(content, newContent); // OK
    }
private:
    char sender[32];
    char reciever[32];
    mutable char content[256];
    mutable bool delivered;
    int timestamp;
};
```

# Разделна компилация
При класовете, синтаксисът и идеята са аналгоични с тези на структурите.

# Кога структури и кога класове?
В общия случай може да спазвате следната идея

- Ако искате да пакетирате просто ралзични типове, и не се нуждаете от методи (следователно са публични), използвайте структури (`struct`)
- В противен случай използвайте класове (`class`)

Пример:

```cpp
struct Pixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}

class Canvas
{
public:
    void drawCanvas() const;
    void paint(unsigned x, unsigned y, const Pixel& pixel);

    Pixel& getColor(unsigned x, unsigned y);
    const Pixel& getColor(unsigned x, unsigned y) const;

private:
    Pixel pixels[256][256];
    double contrast;
    double brightness;
}
```

> Дефинициите са описани в съответния `.cpp` файл на класа.