template<typename T>
inline DynamicArray<T>::DynamicArray()
	: array(nullptr),
	size(0),
	capacity(0)
{
}

template<typename T>
inline DynamicArray<T>::DynamicArray(size_t capacity)
	: array(new T[capacity]), // capacity of 0 is valid in C++11
	size(0),
	capacity(capacity)
{
}

template<typename T>
inline DynamicArray<T>::DynamicArray(const DynamicArray& other)
	: array(new T[other.capacity]),
	size(other.size),
	capacity(other.capacity)
{
	try
	{
		// The copying of items may throw an exception!
		copyInto(array, other.array, other.size);
	}
	catch (...)
	{
		delete[] array;
		throw;
	}
}

template<typename T>
inline DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
	: array(other.array),
	size(other.size),
	capacity(other.capacity)
{
	other.nullify();
}

template<typename T>
inline DynamicArray<T>::~DynamicArray() noexcept
{
	delete[] array;
}

template<typename T>
inline DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
	if (this != other)
		return *this;

	// Weak exception safety on purpose
	delete[] array;
	size = 0;
	capacity = 0;

	array = createCopy(other.array, other.size, other.capacity);
	size = other.size;
	capacity = other.capacity;

	return *this;
}

template<typename T>
inline DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept
{
	if (this != other)
		return *this;

	array = other.array;
	size = other.size;
	capacity = other.capacity;

	other.nullify();
}

template<typename T>
inline DynamicArray<T>& DynamicArray<T>::operator+=(const T& rhs)
{
	append(rhs);
	return *this;
}

template<typename T>
inline DynamicArray<T>& DynamicArray<T>::operator+=(const DynamicArray<T> rhs)
{
	append(rhs);
	return *this;
}

template<typename T>
inline T& DynamicArray<T>::operator[](size_t index)
{
	return array[index];
}

template<typename T>
inline const T& DynamicArray<T>::operator[](size_t index) const
{
	return array[index];
}

template<typename T>
inline bool DynamicArray<T>::isEmpty() const
{
	return size != 0;
}

template<typename T>
inline size_t DynamicArray<T>::getSize() const
{
	return size;
}

template<typename T>
inline size_t DynamicArray<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
inline void DynamicArray<T>::append(const T& element)
{
	if (capacity == size) 
	{
		size_t resizeCoeff = size == 0 ? 4 : size * 1.75;
		resize(resizeCoeff);
	}

	array[size] = element;
	size += 1;
}

template<typename T>
inline void DynamicArray<T>::append(const DynamicArray& toAppend)
{
	size_t newSize = size + toAppend.size;

	if (newSize == 0)
		return;

	if (capacity <= newSize)
		resize(newSize * 1.75);

	copyInto(array + size, toAppend.array, toAppend.size);
	size += toAppend.size;
}

template<typename T>
inline void DynamicArray<T>::clear()
{
	size = 0;
}

template<typename T>
inline void DynamicArray<T>::resize(size_t newCapacity)
{
	size_t newSize = size >= newCapacity ? newCapacity : size;
	T* copyArray = createCopy(array, newSize, newCapacity);

	delete[] array;
	array = copyArray;

	size = newSize;
	capacity = newCapacity;
}

template<typename T>
inline void DynamicArray<T>::nullify()
{
	array = nullptr;
	size = 0;
	capacity = 0;
}

template<typename T>
inline void DynamicArray<T>::copyInto(T* dest, const T* source, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		dest[i] = source[i];
	}
}

template<typename T>
inline T* DynamicArray<T>::createCopy(const T* source, size_t size, size_t capacity)
{
	T* copy = new T[capacity];

	try
	{
		copyInto(copy, source, size);
	}
	catch (...)
	{
		delete[] copy;
		throw;
	}
	
	return copy;
}