#pragma once

#include "BasicString.h"

class Person
{
public:
	Person(const BasicString& firstName, const BasicString& lastName, const BasicString& egn);

	Person& operator=(const Person& other);

	const BasicString& getFirstName() const;
	const BasicString& getLastName() const;
	const char* getEGN() const;

	void setFirstName(const BasicString& firstName);
	void setLastName(const BasicString& lastName);

private:
	void setEGN(const BasicString& egn);

private:
	char egn[11];
	BasicString firstName;
	BasicString lastName;
};