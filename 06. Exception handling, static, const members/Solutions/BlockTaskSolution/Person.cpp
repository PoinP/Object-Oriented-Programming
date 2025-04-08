#include "Person.h"

#include <cstring>
#include <stdexcept>

#pragma warning(disable:4996)

Person::Person(const BasicString& firstName, const BasicString& lastName, const BasicString& egn)
    : firstName(firstName), lastName(lastName)
{
    // Even if setEGN throws, the allocated memory for
    // 'firstName' and 'lastName' will be deallocated(deleted)
    // because they are already created and the stack unwinding
    // will call their destructors without an issue
    setEGN(egn);
}

//Person& Person::operator=(const Person& other)
//{
//    if (this != &other)
//    {
//        BasicString newFirstName = other.firstName;
//        BasicString newLastName = other.lastName;
//
//        // Notice that we are using the swap method here.
//        // This way we can guarantee ourselves a strong exception safety
//        // First we create the two new objects. If they throw an exception
//        // our object is in the same state as before. Otherwise we just swap
//        // the underlying char* and the length. After we swap them,
//        // this->firstName and this->lastName will now own(and handle),
//        // newFirstName and newLastName's data and newFirstName and newLastName
//        // will handle this->firstName and this-lastName's old data.
//        // At the end of this if block, newFirstName and newLastName
//        // will deallocated the old memory.
//
//        this->firstName.swap(newFirstName);
//        this->lastName.swap(newLastName);
//        strcpy(this->egn, other.egn);
//    }
//
//    return *this;
//}

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
    // All is okay because BasicString's operator=
    // guarantees strong exception safety
    this->firstName = firstName;
}

void Person::setLastName(const BasicString& lastName)
{
    // All is okay because BasicString's operator=
    // guarantees strong exception safety
    this->lastName = lastName;
}

void Person::setEGN(const BasicString& egn)
{
    if (egn.getLength() != 10)
        throw std::logic_error("EGN must be exactly 10 characters!");

    strcpy(this->egn, egn.getString());
}
