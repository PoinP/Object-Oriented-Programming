#define _CRT_SECURE_NO_WARNINGS

#include "Car.h"

#include <cstring>
#include <iostream>

void Car::print() const
{
    std::cout << "Brand: " << brand << "\n";
    std::cout << "Model: " << model << "\n";
    std::cout << "License Plate: " << licensePlate << "\n";
    std::cout << "Is electric: " << std::boolalpha << isElectric << "\n";
    std::cout << "Type: " << getTypeString(type) << "\n";
}

const char* Car::getBrand() const
{
    return brand;
}

const char* Car::getModel() const
{
    return model;
}

const char* Car::getLicensePlate() const
{
    return licensePlate;
}

CarType Car::getCarType() const
{
    return type;
}

bool Car::getIsElectric() const
{
    return isElectric;
}

void Car::setBrand(const char* brand)
{
    if (!brand || strlen(brand) >= 16)
        return;

    strcpy(this->brand, brand);
}

void Car::setModel(const char* model)
{
    if (!model || strlen(model) >= 32)
        return;

    strcpy(this->model, model);
}

void Car::setLicenscePlate(const char* licensePlate)
{
    if (!licensePlate || strlen(licensePlate) != 8)
        return;

    strcpy(this->licensePlate, licensePlate);
}

void Car::setCarType(CarType carType)
{
    this->type = carType;
}

bool Car::setIsElectric(bool isElectric)
{
    return false;
}

void Car::writeToBinFile(std::ofstream& outStream) const
{
    if (!outStream)
        return;

    outStream.write(reinterpret_cast<const char*>(this), sizeof(Car));
}

void Car::readFromBinFile(std::ifstream& inStream)
{
    if (!inStream)
        return;

    inStream.read(reinterpret_cast<char*>(this), sizeof(Car));
}

const char* Car::getTypeString(CarType type) const
{
    switch (type)
    {
    case CarType::InvalidType:
        return "Invalid type";
    case CarType::Sedan:
        return "Sedan";
    case CarType::SUV:
        return "SUV";
    case CarType::Hatchback:
        return "Hatchback";
    case CarType::Coupe:
        return "Coupe";
    default:
        return nullptr;
    }
}
