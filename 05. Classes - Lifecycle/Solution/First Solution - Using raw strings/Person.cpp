#include "Person.h"

#include <cstring>

#pragma warning(disable:4996)

Person::Person(const char* firstName, const char* lastName, const char* egn)
    : firstName(nullptr), lastName(nullptr)
{
    setEGN(egn);
    setFirstName(firstName);
    setLastName(lastName);
}

Person::Person(const Person& other)
    : Person(other.firstName, other.lastName, other.egn)
{
}

Person::~Person()
{
    delete[] firstName;
    delete[] lastName;
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

const char* Person::getFirstName() const
{
    return firstName;
}

const char* Person::getLastName() const
{
    return lastName;
}

const char* Person::getEGN() const
{
    return egn;
}

void Person::setFirstName(const char* firstName)
{
    if (!firstName)
        firstName = ""; // or throw exception
    
    char* newName = new char[strlen(firstName) + 1];
    strcpy(newName, firstName);

    delete[] this->firstName;
    this->firstName = newName;
}

void Person::setLastName(const char* lastName)
{
    if (!lastName)
        lastName = ""; // or throw exception;

    char* newName = new char[strlen(lastName) + 1];
    strcpy(newName, lastName);

    delete[] this->lastName;
    this->lastName = newName;
}

void Person::setEGN(const char* egn)
{
    if (!egn || strlen(egn) != 10)
        egn = "0000000000"; // or throw exception;

    strcpy(this->egn, egn);
}
