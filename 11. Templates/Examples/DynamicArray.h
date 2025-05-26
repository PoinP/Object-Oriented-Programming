#pragma once

#include <cstdint>

template <typename T>
class DynamicArray
{
public:
	DynamicArray();
	DynamicArray(size_t capacity);

	DynamicArray(const DynamicArray& other);
	DynamicArray(DynamicArray&& other) noexcept;

	~DynamicArray() noexcept;

	DynamicArray& operator=(const DynamicArray& other);
	DynamicArray& operator=(DynamicArray&& other) noexcept;

	DynamicArray& operator+=(const T& rhs);
	DynamicArray& operator+=(const DynamicArray<T> rhs);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	bool isEmpty() const;
	size_t getSize() const;
	size_t getCapacity() const;

	void append(const T& element);
	void append(const DynamicArray& toAppend);

	void clear();
	void resize(size_t newCapacity);

private:
	void nullify();

	static void copyInto(T* dest, const T* source, size_t size);
	static T* createCopy(const T* source, size_t size, size_t capacity);

private:
	T* array;
	size_t size;
	size_t capacity;
};

template<typename T>
DynamicArray<T> operator+(DynamicArray<T> lhs, const T& rhs)
{
	return lhs += rhs;
}

template<typename T>
DynamicArray<T> operator+(DynamicArray<T> lhs, const DynamicArray<T>& rhs)
{
	return lhs += rhs;
}

#include "DynamicArray.inl"
