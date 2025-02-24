#include "Pixel.h"

#include <iostream>

void printPixel(const Pixel& pixel)
{
	std::cout << "R: " << pixel.red << " "
		<< "G: " << pixel.green << " "
		<< "B: " << pixel.blue << " ";
}