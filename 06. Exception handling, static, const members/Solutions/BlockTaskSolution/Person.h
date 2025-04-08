#pragma once

#include "BasicString.h"

class Person
{
public:
	Person(const BasicString& firstName, const BasicString& lastName, const BasicString& egn);
	// We do not need the rule of four here.
	// Only a single constructor is sufficient
	// The implicitly generated copy-ctor, copy operator= and destructor
	// are enough to handle the class' lifecycle.
	// As we have said many times if we have only stack allocated memebers,
	// so no pointers that own dynamic memory we can skip on the rule of four!

	// This is important! Keep in mind the following:
	// When letting the compiler generate a copy assignment operator(operator=)
	// it guarantees only a basic exception safety. It does NOT guarantee
	// and rearly(if ever) generates a strong exception safety code.
	// This is because the copy-swap idiom may be expensive.
	// I will still add a commented code that executes with strong exception safety behaviour
	// Person& operator=(const Person& other);

	// Just to recap, currently Person's implicitly generated operator=
	// by the compiler guarantees only a basic exception safety.
	// In order to guarantee strong exception safety, we need to define
	// our own copy assignment operator(operator=)

	const BasicString& getFirstName() const;
	const BasicString& getLastName() const;

	// We may return a BasicString here
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