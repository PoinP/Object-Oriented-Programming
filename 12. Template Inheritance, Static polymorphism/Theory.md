# Template Inheritance, Static Polymorphism

## Наследяване на шаблонни класове

Наследяването на шаблонни класове в `C++` е възможно, но има някои особености, които трябва да се вземат предвид. Тези особености се отнасят основно до начина, по който работят шаблоните и как наследяването влияе на специализациите и типовете.

```cpp
template <typename T>
void swap(T& lhs, T& rhs)
{
	T temp = lhs;
	lhs = rhs;
	rhs = temp;
}

template <typename T>
class SafePtr
{
public:
	SafePtr(T* ptr = nullptr) : ptr(ptr) {}
	SafePtr(const SafePtr& other) = delete;
	SafePtr(SafePtr&& other) : ptr(other.ptr) { other.ptr = nullptr; }
	~SafePtr() { delete ptr; }

	SafePtr& operator=(const SafePtr&) = delete;
	SafePtr& operator=(SafePtr&& other) { swap(ptr, other.ptr); }

	T* get() { return ptr; }
	const T* get() const { return ptr; }

private:
	T* ptr;
};

template <typename T>
class StrictPtr : public SafePtr<T>
{
public:
	StrictPtr(T* ptr = nullptr) : SafePtr<T>(ptr) {}
	StrictPtr(StrictPtr&&) = delete;
	StrictPtr& operator=(StrictPtr&&) = delete;

	//T* shiftRight(size_t offset) { return get() + offset; }; // Error
	//T* shiftLeft(size_t offset)  { return SafePtr::get() - offset; }; // Error

	T* shiftRight(size_t offset) { return this->get() + offset; }; // Okay
	T* shiftLeft(size_t offset)  { return SafePtr<T>::get() - offset; }; // Okay
};

class IntPtr : public SafePtr<int>
{
public:
	IntPtr(int* ptr = nullptr) : SafePtr<int>(ptr) {}
};
```

Забелязваме няколко неща:
- Шаблонен клас може да наследи друг шаблонен клас. (Шаблонен клас може да наследи и нормален клас)
- Когато наследяваме шаблон на клас, трябва да зададем екплицитно шаблонния параметър
- Наследената типизация се определя от подадения тип при самото наследяване
- Ако извикваме метод или достъпваме поле, което се намира в базовия клас, то трябва да го достъпим или през `this` или чрез `::` операторът. Ако използваме `::` операторът, трябва експлицитно да зададем шаблонния параметър.
- Когато наследим шаблонен клас, можем да специфицираме неговия шаблонен параметър(както е дадено с `int`)

Всички останали правила за наследяването си важат. Можем да създаваме полиморфни връзки и при шаблонните класове.

## Статичен полиморфизъм

Статичният полиморфизъм се постига чрез `function overloading`, шаблони на функции и шаблони на класове, които се определят по време на компилация. Това означава, че изборът на метод става по време на самата компилация, а не по време на изпълнение, както при виртуалния полиморфизъм.

### Function Overloading

Най-простият статичен полиморфизъм е т.нар. `function overloading`(не `overriding`). Той ни е вече познат и се изявява в следната форма:

```cpp
int sum(int a, int b) { return a + b; }
float sum(float a, float b) { return a + b; }
double sum(double a, double b) { return a + b; }
```

Тоест имаме по една функция за всеки тип с който бихме искали да работим. По-съобразителните биха се досетили, че това адски много прилича на автоматично генерирния код при шаблоните на функциите. Можем да обединим целия този код в един шаблон на функция и така да работи за всеки един възможен тип, който поддържа бинариня оператор `+`.

```cpp
template <typename T>
T sum(const T& lhs, const T& rhs) { return lhs + rhs; }
```

Така всеки път като извикаме `sum` с различен тип, компилаторът ще ни генерира код, който да поддържа този тип.

Същото нещо важи и при класовете:
```cpp
template <typename T>
class Calculator {
public:
    T add(const T& a, const T& b) {
        return a + b;
    }

    T multiply(const T& a,  const T& b) {
        return a * b;
    }
};

int main() {
    Calculator<int> calcInt;
    calcInt.add(3, 4);
    calcInt.multiply(5, 6);

    Calculator<double> calcDouble;
    calcDouble.add(3.5, 4.5);
    calcDouble.multiply(2.5, 3.5);
}
```

### Duck Typing

`Duck Typing` е подход, който е известен при динамичните езици като `JavaScript` и `Python`. Базира се на идеята, че ако нещо квака като паток и се движи като такъв, то значи е паток. С други думи, ако даден обект поддържа функционалности като `draw`, `perimeter` и `area`, то тогава този обект най-вероятно е някаква фигура.

```cpp
#include <iostream>

template <typename Shape>
void extractShapeData(const Shape& shape)
{
	shape.draw();
	std::cout << "Area: " << shape.getArea() << "\n";
	std::cout << "Perimeter: " << shape.getPerimeter() << std::endl;
}

struct SampleTriangle
{
	void draw() const { std::cout << "Drawing triangle!\n"; }
	double getArea() const { return 12.3; }
	double getPerimeter() const { return 30; }
};

struct SampleSquare
{
	void draw() const { std::cout << "Drawing Square!\n"; }
	int getArea() const { return 25; }
	int getPerimeter() const { return 20; }
};

struct NotReallyAShape
{
	void draw() const { std::cout << "Drawing Some Lines\n"; }
	int getArea() const { return 0; }
	int getPerimeter() const { return 0; }
};

int main()
{
	extractShapeData(SampleTriangle{});
	extractShapeData(SampleSquare{});
	extractShapeData(NotReallyAShape{});
}
```

Реално трите класа нямат общ наследник или като цяло общ елемент помежду си. Въпреки това, те удовлетвояват условието на шаблона за изискваните методи и заради това програмата се изпълнява без проблем. По този начин се получава статичен полиморфизъм.

> If it quacks like a duck and walks like a duck, then it's probably a duck

### CRTP - Curiously recurring template pattern

Това е идея в `C++` в която един клас `X` наследява шаблонен клас `Y`, като задава себе си като шаблонен параметър. Формално се описва като `F-bound polymorphism`.

```cpp
#include <iostream>

template <typename T>
class Notification
{
public:
	void sendMessage(const char* message) const
	{
		const T* derivedClassPtr = static_cast<const T*>(this);
		derivedClassPtr->sendMessage(message);

		// We can also shorthand it:
		// static_cast<const T*>(this)->sendMessage(message)

		// If the method was mutable, we would have had
		// T* derivedClassPtr = static_cast<T*>(this);
	}
};

class EmailNotification : public Notification<EmailNotification>
{
public:
	void sendMessage(const char* message) const
	{
		std::cout << "Email Notification: " << message << std::endl;
	}
};

class PushNotification : public Notification<PushNotification>
{
public:
	void sendMessage(const char* message) const
	{
		std::cout << "Push Notification: " << message << std::endl;
	}
};

class ConsoleNotification : public Notification<ConsoleNotification>
{
public:
	void sendMessage(const char* message) const
	{
		std::cout << "Console Notification: " << message << std::endl;
	}
};

template<typename T>
void sendNotification(const Notification<T>& notification, const char* message)
{
	notification.sendMessage(message);
}

int main()
{
	PushNotification pNotif;
	EmailNotification eNotif;
	ConsoleNotification cNotif;

	sendNotification(pNotif, "Sending push notification!");
	sendNotification(eNotif, "Sending email notification!");
	sendNotification(cNotif, "Sending console notification!");
}
```

### Допълнителни конструкции
Останалите конструкции са само за по-любознателните, като няма да навлизам в детайли за тях, но може да разгледате различните начини за получаване на статичен полиморфизъм чрез:
- std::any
- std::variant
- std::tuple
- Overload Idiom 


## Статичен полимофизъм VS Динамичен полиморфизъм

Статичния полиморфизъм предоставя по-добра производителност, поради липсата на виртуалната таблица и динамичното извкване на функциите. Но може да доведе до прекомерно увеличаване на количеството код и ниска гъвкавост. От друга стана, динамичният(или виртуалният) полиморфизъм се определя по време на изпълнението на прогрмата, осигурявайки по-висока гъвкавост и разшируемост, особено за по сложни системи. Позволява и определяне на използваните типове на база на някакво условие(тип на връзката, ниво на достъпа, използваната база от данни).  

Статичният полиморфизъм е идеален за код с високи изисквания за производителност и фиксирано поведение, докато виртуалният полиморфизъм е по-подходящ за ситуации, изискващи динамично поведение и разширяемост. И двата подхода могат да се използват заедно в практиката, за да се балансират гъвкавостта и ефективността.