#pragma once

#include <stdint.h>

class BasicString
{
public:
	BasicString(const char* string = "");
	BasicString(const BasicString& other);
	~BasicString();

	BasicString& operator=(const BasicString& other);

	uint64_t getLength() const;
	const char* getString() const;
	bool isEqualTo(const BasicString& other) const;

	// This method is used to swap the underlying
	// data with another BasicString object
	// This method will be particularly useful when we
	// implement strong exception safety.
	// If we strive to make our program have a basic
	// exception safety implementation, we can skip on
	// this method as a whole.
	void swap(BasicString& other);

	// Think of it being the same as using [] for arrays
	// Instead of [] we are using a method that has the same behaviour
	char& at(uint64_t index);
	char at(uint64_t index) const;

	// We have two 'at' methods. This is intentional.
	// ---------------------------------------------------
	// The mutable 'at' method returns a reference to the element at a particular index
	// This means we can edit said element and the state of our class will change
	// ---------------------------------------------------
	// The const 'at' method returns a copy to the element at particular index
	// This way if we do any changes to the copy, the state of our class won't change

private:
	char* cString;
	uint64_t length;
};