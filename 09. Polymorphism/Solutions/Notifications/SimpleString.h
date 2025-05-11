#pragma once

#include <iostream>
#include <cstdint>

class SimpleString
{
public:
	SimpleString(const char* string = "");
	SimpleString(const SimpleString& other);
	~SimpleString();

	SimpleString& operator=(const SimpleString& other);

	size_t getLength() const;
	const char* getCString() const;
	void swap(SimpleString& other);

private:
	size_t length;
	char* cString;
};

std::ostream& operator<<(std::ostream& oStream, const SimpleString& string);