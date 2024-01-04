#ifndef aVector2dFILE
#define aVector2dFILE

class SZ_Vector2D
{
public:
	SZ_Vector2D();
	SZ_Vector2D(int aX, int aY);
	int X = 0;
	int Y = 0;
	float magnitude();
};
#endif

