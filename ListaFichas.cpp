#include"ListaFichas.h"

ListaFichas::ListaFichas() 
{
	numero = 0;
	for (int i = 0; i < MAX_FICHA; i++) 
	{
		lista[i] = 0;
	}
}
Fichas* ListaFichas::operator [](int i) //SOBRECARGA DEL OPERADOR []
{
	if (i >= numero || i < 0)
	{
		return 0;
	}
	
	return lista[i];
}

bool ListaFichas::agregar(Fichas* f) 
{
	if (numero < MAX_FICHA) 
	{
		lista[numero] = f;
		numero++;
		return true;
	}
	return false;
}
void ListaFichas::Dibuja() 
{
	for (int i = 0; i < numero; i++) 
	{
		lista[i]->Dibuja();
	}
}
Vector2D ListaFichas::getPosicion(int i) 
{
	return lista[i]->GetPosicion();
}
void ListaFichas::comprobarReina(int TURNO) //COMPRUEBA SI UNA FICHA HA LLEGADO AL FINAL DEL TABLERO
{
	for (int i = 0; i < 12; i++) 
	{
		if (lista[i]->GetPosicion().y == 7 && TURNO == 1 && lista[i]->getMuerta() == 0 && lista[i]->getReina() == false) 
		{
			lista[i]->setReina(true);
		}
		if (lista[i]->GetPosicion().y == 0 && TURNO == 2 && lista[i]->getMuerta() == 0 && lista[i]->getReina() == false) 
		{
			lista[i]->setReina(true);
		}
	}
}