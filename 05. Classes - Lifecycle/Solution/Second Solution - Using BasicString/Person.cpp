#include "Person.h"

#include <cstring>

#pragma warning(disable:4996)

Person::Person(const BasicString& firstName, const BasicString& lastName, const BasicString& egn)
    : firstName(firstName), lastName(lastName)
{
    setEGN(egn);
}

Person& Person::operator=(const Person& other)
{
    if (this != &other)
    {
        setEGN(other.egn);
        setFirstName(other.firstName);
        setLastName(other.lastName);
    }

    return *this;
}

const BasicString& Person::getFirstName() const
{
    return firstName;
}

const BasicString& Person::getLastName() const
{
    return lastName;
}

const char* Person::getEGN() const
{
    return egn;
}

void Person::setFirstName(const BasicString& firstName)
{
    this->firstName = firstName;
}

void Person::setLastName(const BasicString& lastName)
{
    this->lastName = lastName;
}

void Person::setEGN(const BasicString& egn)
{
    if (egn.getLength() != 10)
    {
        strcpy(this->egn, "0000000000");
        return;
    }

    strcpy(this->egn, egn.getString());
}
