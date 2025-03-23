#include "Car.h"

int main()
{
	Car c;
	c.setBrand("Audi");
	c.setModel("A5");
	c.setLicenscePlate("CB8871AA");
	c.setIsElectric(false);
	c.setCarType(CarType::Coupe);

	std::ofstream ofs("car.bin", std::ios::binary);
	c.writeToBinFile(ofs);
	ofs.close();

	Car c2;
	std::ifstream ifs("car.bin", std::ios::binary);
	c2.readFromBinFile(ifs);
	ifs.close();

	c2.print();
}