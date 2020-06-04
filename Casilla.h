#pragma once
#include"Vector2D.h"
#include "ColorRGB.h"
#include"../include/glut.h"

class Casilla 
{
private:

	int ocupacion;
	int posible;
	int seleccionada;

	float lado_casilla;

	colorRGB color;
	typedef unsigned char Byte;

	Vector2D posicion;

public:
	Casilla();

	void Dibuja();
	void setLado(float);
	void setPosible(int);
	void setPos(float, float);
	void setOcupacion(int oc);
	void setColor(Byte r, Byte g, Byte b);
	void setSeleccionada(int i);

	int getPosible();
	int getOcupacion();
	
	float getLado();
	
	Vector2D getPosicion();
};
