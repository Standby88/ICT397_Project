#include <iostream>

#include "GraphicsEngine.h"

int main()
{
	GraphicsEngine grap;
	if (grap.GLFWpro() == true)
	{
		return 1;
	}
	return 0;
}