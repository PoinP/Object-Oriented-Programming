#pragma once

#include "Pixel.h"

struct Canvas
{
	const int width = 25;
	const int height = 25;
	Pixel pixels[25][25];
};

void printCanvas(const Canvas& canvas);