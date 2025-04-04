#pragma once

class Person
{
public:
	Person(const char* firstName, const char* lastName, const char* egn);
	Person(const Person& other);
	~Person();

	Person& operator=(const Person& other);

	const char* getFirstName() const;
	const char* getLastName() const;
	const char* getEGN() const;

	void setFirstName(const char* firstName);
	void setLastName(const char* lastName);

private:
	void setEGN(const char* egn);

private:
	char egn[11];
	char* firstName;
	char* lastName;
};