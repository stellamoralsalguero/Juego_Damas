#pragma once
#include"Casilla.h"
#include "ColorRGB.h"
#define DIM 8
class ListaCasilla
{

public:
	ListaCasilla();

	bool agregar(Casilla* c);
	void Dibuja();
	void setOcupacion(int i, int j, int oc);
	void setFila(int i);
	void setColumna(int i);
	void resetColor();
	void setSeleccionada(int x, int y);

	int getFila();
	int getColumna();
	int CanMove(int, int);

	Vector2D getPosicion(int i, int j);
	Vector2D posibilidades(int a, int b, int turno, bool reina, bool DoubleEat, int u, int mostrar);

	Casilla* devuelveCasilla(int x, int y);

	colorRGB colorposible;
	colorRGB colorcomible;
	typedef unsigned char Byte;
private:
	Casilla* matriz[DIM][DIM];
	Vector2D seleccionada;

	int fila, columna;
	int ColorCasillaPosible[3];
	int ColorCasillaComible[3];
};