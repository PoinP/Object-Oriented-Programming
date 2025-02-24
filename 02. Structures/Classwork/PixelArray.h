#pragma once

#include "Draw/Pixel.h"

struct PixelArray
{
	Pixel* pixels;
	unsigned size;
};

PixelArray createPixelArray(unsigned size);
void printPixelArray(const PixelArray& array);
void inputPixelArray(PixelArray& array);
void deletePixelArray(PixelArray&);