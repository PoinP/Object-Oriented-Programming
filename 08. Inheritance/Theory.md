# Наследяване

Наследяването представлява основен механизъм в обектно-ориентираното програмиране, при който един клас (наследник или производен клас) може да наследи член-данни(полета) и методи(член-функции) от друг клас (базов клас или родител).

## Ниво на достъп

Както се запознахме в минали уроци, съществуват три вида нива на достъп при класовете(и структурите), като достъп имат:
- `Private`: само членовете на класа и приятелски(`friend`) класове или функции
- `Proteced`: членовете на класа, както и негови наследници (и приятели)
- `Public`: членовете на класа, негови наследници и други вънпни обекти/функции (и приятели)

Същите нива се наблюдават и при самото наследяване:

```cpp
class Base {
    // Член-данни и методи
};

class Derived : <access_specifier> Base {
    // Нови член-данни и методи
};
```

`access_specifier` може да бъде:
- `public` – публично наследяване (най-често използвано), всички членове на базовия клас си запазват нивото на достъп
- `protected` – всички `public` членове се превръщат в `protected` за класа наследник
- `private` – всички `public` и `protected` членове се превръщат в `private` за класа наследник

***Какво значи се превръщат?***  
Това означава, че ако наследим с ниво на достъп `private`, то всички полета и методи на класа родител, които са `public` И `protected` ще бъдат `private` за наследника.  

```cpp
class Object 
{
public:
    void reshape(const char* shape);

protected:
    bool hasReshaped() const;

private:
    void construct();
};

class Sphere : private Object
{
public:
    void roll();

protected:
    void changeMaterial(const char* material);

private:
    void initialize()
    {
        // construct(); // Error, construct is private for Object, can not be accesed from Sphere
        reshape("Sphere"); // OK, reshape(const char*) is private for Sphere, public for Object
        if (!hasReshaped()) // OK, hasReshaped() is private for Sphere, protected for Object
            throw std::exception();
    }
};

class GlassSphere : public Sphere
{
public:
    void doStuff()
    {
        roll() // OK, roll() is public for GlassSphere, public for Sphere
        // initalize() // Error, initalize() is private for Sphere, can not be accessed from GlassSphere
        changeMaterial("Glass") // OK, changeMaterial(const char*) is protected for GlassSphere and protected for Sphere
    }
};

int main() 
{
    Object obj;
    obj.reshape("Door") // OK, reshape() is public
    // obj.hasReshaped() // Error, hasReshaped() is protected
    
    Sphere sph;
    sph.roll() // OK, roll() is public
    sph.reshape("Car") // Error reshape() is inherited privately, so it's private for Sphere

    GlassSphere glassSph;
    glassSph.doStuff() // OK, doStuff() is public
    glassSph.roll() // OK, roll() is inherited publicly, so it stays public
    // glassSph.changeMaterial("Glass") // Error, changeMaterial(const char*) is inherited publicly, so it stays protected just like in Sphere
}
```

Ето таблица с различните типове наследяване:

| В базовия клас | `public` наследяване  | `protected` наследяване  | `private` наследяване  |
| -------------- | --------------------- | ------------------------ | ---------------------- |
| `public`       | `public` в наследника | `protected` в наследника | `private` в наследника |
| `protected`    | `protected`           | `protected`              | `private`              |
| `private`      | недостъпен            | недостъпен               | недостъпен             |


## Ред на извикване на конструкторите и деструкторите

### Ред на конструкторите

При създаване на обект от производен клас, конструкторите се извикват в следния ред:
1. Конструктор на базовия клас
2. Конструктори на член-обекти на базовия клас (ако има такива)
3. Конструктор на производния клас
4. и т.н.

```cpp
class Base {
public:
    Base() { std::cout << "Base constructor\n"; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "Derived constructor\n"; }
};
```
```
Base constructor
Derived constructor
```

### Ред на деструкторите
Деструкторите се извикват в обратен ред:
1. Деструктор на производния клас
2. Деструктори на член-обекти на производния клас
3. Деструктор на базовия клас
4. и т.н.

```cpp
class Base {
public:
    ~Base() { std::cout << "Base destructor\n"; }
};

class Derived : public Base {
public:
    ~Derived() { std::cout << "Derived destructor\n"; }
};
```
```
Derived destructor
Base destructor
```

С други думи:
- При конструкторите, първо се вика конструктора на най-базовия клас, неговите член данни и след това на наследнците. Извикването продължава до извикването на конструктора на последния наследник и неговите член данни
- При деструкторите, извикването им се случва в обратен ред. Първо се викат деструкторите на член данните(обектите) и деструктора на най-последния наследник и накрая деструктора на най-базовия клас

> Под базов клас се има предвид всеки клас, който има наследник. Най-базовия клас е този, който няма предшественици(не наследява друг клас). Същото важи за наследник, но в обратен ред.

### Особености

1. Конструкторите и деструкторите не се наследяват.
2. Трябва експлицитно да се извикват конструкторите с параметри на даден базов клас. В противен случай се вика имплицитно този по подразбиране.
3. Имаме ли копиращ конструктор, то трябва да извикаме копиращия конструктор на базовия клас
4. Имаме ли копиращ оператор за присвояване(operator=), то трябва да извикаме и оператора на базовия клас в тялото му.
5. Ако базов клас няма конструктор по подразбиране, трябва експлицитно да се извика някой негов конструктор с парметри.
6. Наследяват се само `public` и `protected` елементи на даден клас.
7. Производният клас може да разширява или променя поведението на базовия. Например: добавяне на нови методи или „скриване“ на базови методи (със същото име).
8. Множествено наследяване съществува, но може да доведе до проблеми като “диамантен проблем” – извън обхвата на тази тема. Ще го разгледаме другата седмица.

Пример 1:

```cpp
class Logger 
{
public:
    Logger()
        : Logger("LOG")
    {
    }

    Logger(const char* prefix) : prefix(new char[strlen(prefix) + 1]) 
    {
        strcpy(this->prefix, prefix);
    }
    
    ~Logger() noexcept
    {
        delete[] prefix;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(const char* message) const 
    {
        std::cout << "[" << prefix << "] " << message << std::endl;
    }

protected:
    char* prefix;
};

class MixedLogger : public Logger 
{
public:
    MixedLogger(const char* filename)
        // Извиква се конструктора по подразбиране на базовия клас
        // Ако такъв конструкор не съществуваше, щеше да се появи грешка
        // Note: По правилно е да извикаме конструкотра на MixedLogger,
        // но го показвам като пример.
        : filename(new char[strlen(filename) + 1]) 
    {
        strcpy(this->filename, filename);
    }

    MixedLogger(const char* filename)
        : Logger("FileLogging"), // Извикваме експлицитно конструктора на базовия клас с параметър
          filename(new char[strlen(filename) + 1]) 
    {
        strcpy(this->filename, filename);
    }

    ~MixedLogger() noexcept
    {
        delete[] filename;
    }

    // Note: Copy constructor и operator=
    // също са изтрити за наследника!
    // Можем да си ги дефинираме експлицитно,
    // но не е препоръчително!

    void writeToFile(const char* message) const
    {
        std::ofstream ofs(filename, std::ios::app);
        ofs << "[" << prefix << "] " << message << std::endl;
    }

private:
    char* filename;
};
```

Пример 2 (с копиращ конструктор и operator=):
```cpp
class Logger 
{
public:
    Logger()
        : Logger("LOG")
    {
    }

    Logger(const char* prefix) : prefix(new char[strlen(prefix) + 1]) 
    {
        strcpy(this->prefix, prefix);
    }
    
    ~Logger() noexcept
    {
        delete[] prefix;
    }

    Logger(const Logger& other)
        : Logger(other.prefix)
    {
    }

    Logger& operator=(const Logger& other)
    {
        if (this == &other)
            return *this;

        // Strong exception safety
        char* newPrefix = strcpy(new char[strlen(other.prefix) + 1], prefix);
        delete[] prefix;
        prefix = newPrefix;

        return *this;
    }

    void log(const char* message) const 
    {
        std::cout << "[" << prefix << "] " << message << std::endl;
    }

protected:
    char* prefix;
};

class MixedLogger : public Logger 
{
public:
    MixedLogger()
        // Извиква се конструктора по подразбиране на базовия клас
        // Ако такъв конструкор не съществуваше, щеше да се появи грешка
        // Note: По правилно е да извикаме конструкотра на MixedLogger,
        // но го показвам като пример.
        : MixedLogger("log.txt")
    {
    }

    MixedLogger(const char* filename)
        : Logger("FileLogging"), // Извикваме експлицитно конструктора на базовия клас с параметър
          filename(strcpy(new char[strlen(filename) + 1], filename))

    {
    }

    ~MixedLogger() noexcept
    {
        delete[] filename;
    }

    MixedLogger(const MixedLogger& other)
        : Logger(other),
          filename(strcpy(new char[strlen(other.filename) + 1], other.filename))
    {
        // ВАЖНО:
        // Note: Тук си запазваме Basic/Strong exception safety-то.
        // Ако Logger се изпълни успешно и MixedLogger хвърли exception,
        // то деструктора на Logger ще се извика и ще освободи заделената памет.
    }

    MixedLogger& operator=(const MixedLogger& other) 
    {
        if (this == &other)
            return *this;

        // Basic exception safety
        Logger::operator=(other);

        delete[] filename;
        filename = strcpy(new char[strlen(other.prefix) + 1], prefix);

        // This can easily be transformed into
        // Strong exception safety by using move semantics.
        // Or just implementing a move() method.
    }

    void writeToFile(const char* message) const
    {
        std::ofstream ofs(filename, std::ios::app);
        ofs << "[" << prefix << "] " << message << std::endl;
    }

private:
    char* filename;
};
```


Пример 3:

> Приемаме, че си имаме имплементиран собсвен `String`

```cpp
class User 
{
public:
    User(const String& uname) : username(uname) {}

    void login() const
    {
        std::cout << username.cString() << " logged in.\n";
    }

    void post(const String& message) const
    {
        std::cout << username.cString() << ": " << message.cString() << std::endl;
    }

protected:
    String username;
};

class Admin : public User 
{
public:
    // Admin() {} Error: No default ctor for User
    Admin(const String& uname) : User(uname) {}

    void accessAdminPanel() const
    {
        std::cout << username.cString() << " accessed the admin panel.\n";
    }

    // Method shadowing
    void post(const String& message) const
    {
        std::cout << "<Admin Message> ";
        // post(message); Wrong! Bottomless recurssion!
        User::post(message); // Resuing the shadowed post(const String&) of User
    }

private:
    bool isOwner = false;
};

void postUserMessage(const User& user, const String& message)
{
    user.post(message);
}

void postAdminMessage(const Admin& admin, const String& message)
{
    admin.post(message);
}

int main()
{
    User user("user");
    Admin admin("admin");

    postUserMessage(user, "Hey"); // OK, prints user: Hey
    postAdminMessage(admin, "No memes in #general!"); // OK, prints <Admin Message> admin: No memes in #general!
    postUserMessage(admin, "lol, bro!"); // OK, prints admin: lol, bro!
    // postAdminMessage(user, "ERROR!!!") // Error, User can not be converted to Admin
}
```

Този пример показва, че могат да се подават обекти-наследници на функции, които очакват като параметър/и техен базов клас. Това означава, че наследниците могат да се преобразуват имплицитно към някой от техните базови типове.  
Трябва да внимаваме с това поведение, защото като преобразуваме обект към негов базов тип, то той губи функционалностите си. Затова, когато извикаме `postUserMessage(const User&, const String&)`, с обект от тип `Admin` реално се извиква метода `User::post(const String&)`, а не `Admin::post(const String&)`.