#include <iostream>

#include "Draw/Canvas.h"
#include "PixelArray.h"

int main()
{
	PixelArray array = createPixelArray(5);
	inputPixelArray(array);
	printPixelArray(array);
	deletePixelArray(array);
}