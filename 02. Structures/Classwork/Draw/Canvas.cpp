#include "Canvas.h"

#include <iostream>

void printCanvas(const Canvas& canvas)
{
	for (int i = 0; i < canvas.width; i++)
	{
		for (int j = 0; j < canvas.height; j++)
		{
			printPixel(canvas.pixels[i][j]);
			std::cout << std::endl;
		}
	}
}