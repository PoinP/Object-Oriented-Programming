#pragma once

class BasicString
{
public:
	BasicString(const char* string = "");
	BasicString(const BasicString& other);
	~BasicString();

	BasicString& operator=(const BasicString& other);

	unsigned getLength() const;
	const char* getString() const;
	bool isEqualTo(const BasicString& other) const;

	char& at(unsigned index);
	char at(unsigned index) const;

private:
	char* cString;
};