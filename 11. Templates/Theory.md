# Templates (Шаблони)

Шаблоните ни позволяват да пишем обобщен(или generic) код, който може да работи с различни типове, стига да удовлетворяват условията на кода.  
Имаме два основни вида шаблони:
- Шаблони на функции (Function Templates)
- Шаблони на класове (Class Templates)

## Синтаксис
Една функция или клас се преобразува в шаблон(`template`), тогава когато се добави следния синтаксис пред нея:  
`template <typename [име на шаблонния параметър]>`  
Тоест ако искаме да напишем шаблон на функция, която има шаблонен параметър `T`, ние ще напишем:  
`template <typename T>`  

Възможно е да опишем колкото си искаме шаблонни параметри:  
`template <typename T, typename U, typename Z>`  

> Можем да използваме и `class` вместо `typename`. Причината за това не е особено важна, но разлика между двата начина няма.

## Function Templates
Позволява ни да дефинираме функция, която може да работи с произволни типове.

```cpp
template <typename T>
T maxValue(const T& a, const T& b) {
    return (a > b) ? a : b;
}
```

Тук `T` представлява някакъв произволен тип(може да е `int`, `double` или дори някой потребителски тип). Единственото ограничение е, че този тип трябва да може да поддръжа оператора `>`.

```cpp
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```

Начин на използване:
```cpp
int main()
{
    int a = 10;
    int b = 20;
    swap(a, b);
    // a == 20, b == 10

    //OR
    swap<int>(a, b)
    // a == 10, b == 20 | We swap them back basically
}
```

Важно е да отбележим, че когато работим с шаблонни параметри, ние нямаме идея какъв тип може да се подаде на тази функция. За това е важно да подаваме параметрите по константна референиця(`const&`), освен ако реално не цели копие или промяна на някой от параметърите на функцията

Можем да имаме и шаблони, които имат стойност от конкретен тип, който се подават по време на компилация.

```cpp
template <int size>
void arrayExample() {
    double array[size]; // OK
}
```

Това е доста суров пример, но по-нататък ще покажа практически свързан с параметър от този тип.

## Class Templates
Дефинира шаблон на функция

```cpp
template <typename T>
class DynArray {
    T* arr;
    size_t size;
public:
    DynArray() : arr(nullptr), size(0) {}
    const T* getArr() const { return arr; }
};
```

или

```cpp
template <typename T, size_t capacity>
class DynArray {
    T[capacity] arr;
    size_t size;
public:
    DynArray() : size(0) {}
    const T* getArr() const { return arr; }
};
```

По този начин можем да си направим масив с фиксиран размер под формата на клас, който да има функционалности като `append()`, `popBack()`, `insert()`, `size()` и т.н.

Начин на използване:
```cpp
int main()
{
    DynArray<int> dynamicIntArr;
    Array<int, 20> intArr; // Array with 20 elements
}
```

## Template Specialization
Позволява дефиниране на специфично поведение за определени типове.

### Пълна спецификация

```cpp
template <typename T>
void print(const T& value) {
    std::cout << "Value: " << value << std::endl;
}

template <>
void print<char>(char element) {
    std::cout << "Char Value: " << (int)element << std::endl;
}
```

По този начин ние специализираме шаблона на функцията за специфичен тип - `char`. Така когато извикаме print с тип `int` или `double` ще се изкара на екрана както нормално, ако извикаме `print` с параметър от тип `char`, то ще се изкара на екрана числената репрезентация на символа, а не самия символ.

Същия пример, но с клас:
```cpp
template <typename T>
class Printer {
public:
    void print(const T& value) {
        std::cout << "Generic: " << value << std::endl;
    }
};

template <>
class Printer<char> {
public:
    void print(char value) {
        std::cout << "Char Value: " << (int)element << std::endl;
    }
};
```

Това се нарича **пълна спецификация**, защото се специфицират всички възможни шаблонни параметри.

### Частична спецификация
Позволява ни да специализираме само някои от параметрите.

```cpp
template <typename T1, typename T2>
class Pair {
public:
    void show() {
        std::cout << "Generic pair\n";
    }
};

template <typename T>
class Pair<T, int> {
public:
    void show() {
        std::cout << "Specialized where second pair is int\n";
    }
};
```

Това се нарича **частична спецификация** и работи само за класове, но не и за функции

## Работа с функтори(Functors)
Шаблоните ни предоставят начин по който да работим както с функтори, така и с функции.

```cpp
class Multiplier
{
public:
    Multiplier(int base) : base(base) {}
    void setBase(int base) { this->base = base; }
    int operator()(int value) const { return value * base; }
private:
    int base;
};

template<typename Func>
void mapArr(int* arr, unsigned size, const Func& func)
{
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = func(arr[i]);
    }
}

int main()
{
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    mapArr(arr, 10, [](int num) { return num *= 2; });

    int multiplierBase;
    std::cin >> multiplierBase;
    Multiplier multiplier(multiplierBase);

    mapArr(arr, 10, multiplier);
}
```

Забележете как можем да подадем обект на функцията `mapArr`. Това е така, защото шаблона на функцията изисква типа `Func`, който бива подаден да имплементира само оператора `()`. Тоест можем да подадем на тази функция на параметъра `func` всеки обект, който предефинира по някакъв начин оператора `()` с един параметър, който е `int`. Можем да направим класа и функцията да работят с всякакви типове, а не само с `int`.

```cpp
template <typename T>
class Multiplier
{
public:
    Multiplier(const T& base) : base(base) {}
    void setBase(const T& base) { this->base = base; }
    T operator()(const T& value) const { return value * base; }
private:
    T base;
};

template<typename T, typename Func>
void mapArr(T* arr, unsigned size, const Func& func)
{
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = func(arr[i]);
    }
}

int main()
{
    double arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    mapArr(arr, 10, [](double num) { return num *= 2; });

    double multiplierBase;
    std::cin >> multiplierBase;
    Multiplier<double> multiplier(multiplierBase);

    mapArr(arr, 10, multiplier);
}
```

## Примери

```cpp
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename Strategy>
class Sorter {
public:
    Sorter(const Strategy& strategy) : strategy(strategy) {}

    template <typename T>
    void sort(T* arr, unsigned size) {
        strategy(arr, size);
    }

private:
    Strategy strategy;
};

class AscendingSort {
public:
    template <typename T>
    void operator()(T* arr, unsigned size) {
        for (size_t i = 0; i < size; i++)
        {
            T* min = &arr[i];
            for (size_t j = i + 1; j < size; j++)
            {
                if (*min > arr[j])
                    min = &arr[j];
            }

            if (min == &arr[i])
                return;

            swap(*min, arr[i]);
        }
    }
};

class DescendingSort {
public:
    template <typename T>
    void operator()(T* arr, unsigned size) {
        for (size_t i = 0; i < size; i++)
        {
            T* max = &arr[i];
            for (size_t j = i + 1; j < size; j++)
            {
                if (*max < arr[j])
                    max = &arr[j];
            }

            if (max == &arr[i])
                return;

            swap(*max, arr[i]);
        }
    }
};

int main() 
{
    Sorter<DescendingSort> s1(DescendingSort{});
    int arr[] = { 5, 3, 8 };
    s1.sort(arr, 3);
}
```

Втори пример:

```cpp
template <typename T>
class Logger
{
public:
	static void log(const T& value)
	{
		std::cout << value << std::endl;
	}
};

// Частична специализация за масиви на Logger класа
template <typename T, size_t size>
class Logger<T[size]>
{
public:
	static void log(T* arr)
	{
		for (size_t i = 0; i < size; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
};

int main() 
{
	int arr[] = { 3, 2, 4, 5, 6 };
	Logger<int[5]>::log(arr);
}
```

Това е възможно, защото в `C++` съществува специална специализация за масвиви.

Трети пример:

```cpp
template <typename T, T val>
struct IntegralValue
{
	constexpr operator T() { return val; }
};

using FalseValue = IntegralValue<bool, false>;
using TrueValue = IntegralValue<bool, true>;

template <typename T, typename U>
struct IsSame : FalseValue {};

template <typename T>
struct IsSame<T, T> : TrueValue {};

int main()
{
	if (IsSame<int, int32_t>{})
		std::cout << "Everything is normal!";
	else if (IsSame<int, int64_t>{})
		std::cout << "ILP64 data model is being used!";
	else
		std::cout << "We are building on some embedded architecture probably";
}
```

## Шаблони, компилация и auto complete
През целия този документ споменвам, че имаме шаблон на функция/клас, а не шаблонна функция/клас. Това е така, защото шаблоните описват начина по който да се опише един клас или функция по време на компилация. Когато започнем компилация на кода ни, чак тогава се създават реално класове и функции на база на използваните шаблони.

Тоест ако от втория пример логнем четири типа: `int`, `long`, `double`, `bool`, то тогава ще се създадат 4 отделни класа, всеки от които ще може да логва един от четитите типа. Това генриране на класовете и функциите по време на компилация не позволява да описваме дефинициите им в `.cpp` файлове. Те трябва да се опишат или в `.h` файловете или в отделен файл, който да се `#include`-не в `.h` файла.

Също така при `template`-ите не работи или е доста ограничен `auto complete`-ът. И също така няма да излязат компилационни грешки в техния код докато не бъде извикан специфичния метод на класа или фунцкията.

> Ако съществува шаблон на даден клас, то всички негови методи също са шаблони

Следователно един клас би изглкеждал по следния начин:

```cpp
template <typename Func>
class ScopeExit
{
public:
	explicit ScopeExit(const Func& func);
	
	ScopeExit(const ScopeExit&) = delete;
	ScopeExit(ScopeExit&& other) noexcept = delete;
	
	~ScopeExit() noexcept;

	ScopeExit& operator=(const ScopeExit&) = delete;
	ScopeExit& operator=(ScopeExit&& other) noexcept = delete;

	void release();

private:
	Func func;
	bool isReleased;
};

template<typename Func>
inline ScopeExit<Func>::ScopeExit(const Func& func)
	: func(func),
	  isReleased(false)
{
}

template<typename Func>
inline ScopeExit<Func>::~ScopeExit() noexcept
{
	if (!isReleased)
		func();
}

template<typename Func>
inline void ScopeExit<Func>::release()
{
	isReleased = true;
}
```

Или

ScopeExit.h
```cpp
template <typename Func>
class ScopeExit
{
public:
	explicit ScopeExit(const Func& func);
	
	ScopeExit(const ScopeExit&) = delete;
	ScopeExit(ScopeExit&& other) noexcept = delete;
	
	~ScopeExit() noexcept;

	ScopeExit& operator=(const ScopeExit&) = delete;
	ScopeExit& operator=(ScopeExit&& other) noexcept = delete;

	void release();

private:
	Func func;
	bool isReleased;
};

#include "ScopeExit.impl" // Забележете, че не е .cpp. Тук може да е всичко, но често се среща .impl
```

ScopeExit.impl
```cpp
template<typename Func>
inline ScopeExit<Func>::ScopeExit(const Func& func)
	: func(func),
	  isReleased(false)
{
}

template<typename Func>
inline ScopeExit<Func>::~ScopeExit() noexcept
{
	if (!isReleased)
		func();
}

template<typename Func>
inline void ScopeExit<Func>::release()
{
	isReleased = true;
}
```