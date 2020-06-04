#pragma once
#include"../include/ETSIDI.h"
#include "ColorRGB.h"
#include"../include/glut.h"

class Mesa
{
private:
	float x;
	float y;
	float z;

	colorRGB color;
	typedef unsigned char Byte;
public:
	Mesa();

	void Dibuja();
};