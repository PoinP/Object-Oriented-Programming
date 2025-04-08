#pragma once

class BasicString
{
public:
	BasicString(const char* string = "");
	BasicString(const BasicString& other);
	~BasicString();

	BasicString& operator=(const BasicString& other);

	uint64_t getLength() const;
	const char* getString() const;

private:
	char* cString;
};