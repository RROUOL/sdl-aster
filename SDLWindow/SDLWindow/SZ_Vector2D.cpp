#include "SZ_Vector2D.h"
#include <cmath>

SZ_Vector2D::SZ_Vector2D()
{
	X = 1;
	Y = 1;
}

SZ_Vector2D::SZ_Vector2D(int aX, int aY)
{
	X = aX;
	Y = aY;
}


float SZ_Vector2D::magnitude()
{
	return std::sqrt(std::pow(X, 2) + std::pow(Y, 2));
}
