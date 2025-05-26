#pragma once

#include <memory>

// This does not work on array pointers!
template <typename T>
class UniquePtr
{
public:
	UniquePtr(T* ptr = nullptr);

	UniquePtr(const UniquePtr&) = delete;
	UniquePtr(UniquePtr&& other) noexcept;

	~UniquePtr() noexcept;

	UniquePtr& operator=(const UniquePtr&) = delete;
	UniquePtr& operator=(UniquePtr&& other) noexcept;

	operator bool() const;

	T* get();
	const T* get() const;

	T& operator*();
	const T& operator*() const;

	T* operator->();
	const T* operator->() const;

	void swap(UniquePtr& other);

	T* release();
	void reset();

private:
	T* ptr;
};

#include "UniquePtr.inl"