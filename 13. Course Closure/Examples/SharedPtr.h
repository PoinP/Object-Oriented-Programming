#pragma once

#include <cstdint>

struct ControlBlock
{
	uint64_t refCount = 0;

	bool hasAllocations() { return refCount != 0; }
	void allocate() { refCount++; }
	void deallocate() { refCount--; }
};

// Does not support array pointers and weak refs

template <typename T>
class SharedPtr
{
public:
	SharedPtr(T* ptr = nullptr);
	SharedPtr(const SharedPtr& other);
	SharedPtr(SharedPtr&& other) noexcept;
	~SharedPtr() noexcept;

	SharedPtr& operator=(const SharedPtr& other);
	SharedPtr& operator=(SharedPtr&& other) noexcept;

	operator bool() const;

	T* get();
	const T* get() const;

	T& operator*();
	const T& operator*() const;

	T* operator->();
	const T* operator->() const;

	void swap(SharedPtr& other);
	void reset();

	uint64_t getUseCount() const;

private:
	T* ptr;
	ControlBlock* ctrlBlock;
};

#include "SharedPtr.inl"
