template<typename T>
inline SharedPtr<T>::SharedPtr(T* ptr)
	: ptr(ptr),
	ctrlBlock(new ControlBlock())
{
	ctrlBlock->allocate();
}

template<typename T>
inline SharedPtr<T>::SharedPtr(const SharedPtr& other)
	: ptr(other.ptr),
	ctrlBlock(other.ctrlBlock)
{
	ctrlBlock->allocate();
}

template<typename T>
inline SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept
	: ptr(other.ptr),
	ctrlBlock(other.ctrlBlock)
{
	other.ptr = nullptr;
	other.ctrlBlock = nullptr;
}

template<typename T>
inline SharedPtr<T>::~SharedPtr() noexcept
{
	ctrlBlock->deallocate();
	if (!ctrlBlock->hasAllocations())
	{
		delete ptr;
		delete ctrlBlock;
	}
}

template<typename T>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other)
{
	if (this != &other)
		return *this;

	SharedPtr<T> copy(other);
	swap(copy);
	return *this;
}

template<typename T>
inline SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept
{
	if (this != &other)
		return *this;

	swap(other);
	other.release();
}

template<typename T>
inline SharedPtr<T>::operator bool() const
{
	return ptr != nullptr;
}

template<typename T>
inline T* SharedPtr<T>::get()
{
	return ptr;
}

template<typename T>
inline const T* SharedPtr<T>::get() const
{
	return ptr;
}

template<typename T>
inline T& SharedPtr<T>::operator*()
{
	return *ptr;
}

template<typename T>
inline const T& SharedPtr<T>::operator*() const
{
	return *ptr;
}

template<typename T>
inline T* SharedPtr<T>::operator->()
{
	return ptr;
}

template<typename T>
inline const T* SharedPtr<T>::operator->() const
{
	return ptr;
}

template<typename T>
inline void SharedPtr<T>::swap(SharedPtr& other)
{
	T* tempPtr = ptr;
	ptr = other.ptr;
	other.ptr = tempPtr;

	ControlBlock* tempCtrlBlock = ctrlBlock;
	ctrlBlock = other.ctrlBlock;
	other.ctrlBlock = tempCtrlBlock;
}

template<typename T>
inline void SharedPtr<T>::reset()
{
	ctrlBlock->deallocate();
	if (!ctrlBlock->hasAllocations())
	{
		delete ptr;
		ptr = nullptr;

		delete ctrlBlock;
		ctrlBlock = nullptr;
	}
}

template<typename T>
inline uint64_t SharedPtr<T>::getUseCount() const
{
	if (!ctrlBlock)
		return 0;

	return ctrlBlock->refCount;
}