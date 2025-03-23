#pragma once

#include <fstream>

enum class CarType : char
{
	InvalidType = -1,

	Sedan,
	SUV,
	Hatchback,
	Coupe,

	Count
};

class Car
{
public:
	void print() const;

	const char* getBrand() const;
	const char* getModel() const;
	const char* getLicensePlate() const;
	CarType getCarType() const;
	bool getIsElectric() const;

	void setBrand(const char* brand);
	void setModel(const char* model);
	void setLicenscePlate(const char* licensePlate);
	void setCarType(CarType carType);
	bool setIsElectric(bool isElectric);

	void writeToBinFile(std::ofstream& outStream) const;
	void readFromBinFile(std::ifstream& inStream);

private:
	const char* getTypeString(CarType type) const;

private:
	char brand[16];
	char model[32];
	char licensePlate[9];
	CarType type;
	bool isElectric;
};