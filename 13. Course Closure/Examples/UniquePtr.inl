template<typename T>
inline UniquePtr<T>::UniquePtr(T* ptr)
	: ptr(ptr)
{
}

template<typename T>
inline UniquePtr<T>::UniquePtr(UniquePtr&& other) noexcept
	: ptr(other.ptr)
{
	other.ptr = nullptr;
}

template<typename T>
inline UniquePtr<T>::~UniquePtr() noexcept
{
	delete ptr;
}

template<typename T>
inline UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept
{
	if (this == &other)
		return *this;

	ptr = other.ptr;
	other.ptr = nullptr;
	return *this;
}

template<typename T>
inline UniquePtr<T>::operator bool() const
{
	return ptr != nullptr;
}

template<typename T>
inline T* UniquePtr<T>::get()
{
	return ptr;;
}

template<typename T>
inline const T* UniquePtr<T>::get() const
{
	return ptr;;
}

template<typename T>
T& UniquePtr<T>::operator*()
{
	return *ptr;
}

template<typename T>
const T& UniquePtr<T>::operator*() const
{
	return *ptr;
}

template<typename T>
inline T* UniquePtr<T>::operator->()
{
	return ptr;
}

template<typename T>
inline const T* UniquePtr<T>::operator->() const
{
	return ptr;
}

template<typename T>
inline void UniquePtr<T>::swap(UniquePtr& other)
{
	T* temp = ptr;
	ptr = other.ptr;
	other.ptr = temp;
}

template<typename T>
inline T* UniquePtr<T>::release()
{
	T* temp = ptr;
	ptr = nullptr;
	return temp;
}

template<typename T>
inline void UniquePtr<T>::reset()
{
	delete ptr;
	ptr = nullptr;
}