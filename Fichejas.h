#pragma once
#include"Vector2D.h"
#include"../include/ETSIDI.h"
#include "ColorRGB.h"
#include"../include/glut.h"
class Fichas
{
private:
	int seleccionada;
	
	float radio;
	
	bool muerta;
	bool reina;

	colorRGB color;
	typedef unsigned char Byte;
	
	Vector2D posicion;

public:

	Fichas(float x, float y);

	void Dibuja();
	void SetColor(Byte, Byte, Byte);
	void SetSeleccionada(int);
	void setPosicion(float, float);
	void setMuerta();
	void setReina(bool);
	
	int GetSeleccionada();

	bool getReina();
	bool getMuerta();
	
	Vector2D GetPosicion();
};