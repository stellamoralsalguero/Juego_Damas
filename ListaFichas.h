#pragma once
#define MAX_FICHA 12
#include"Fichejas.h"
#include "ListaCasillas.h"

class ListaFichas 
{
public:
	ListaFichas();

	void Dibuja();
	void comprobarReina(int);
	bool agregar(Fichas* f);
	
	Vector2D getPosicion(int i);
	
	Fichas* operator [](int i);
private:
	Fichas* lista[MAX_FICHA];
	int numero;
};
