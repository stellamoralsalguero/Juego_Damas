#include"ListaCasillas.h"
#include"Casilla.h"

ListaCasilla::ListaCasilla()
{
	fila = 0;
	columna = 0;
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++) 
		{
			matriz[i][j] = 0;
		}
	}
	seleccionada.x = -1;
	seleccionada.y = -1;
	colorposible.rojo = 181;
	colorposible.verde = 126;
	colorposible.azul = 220;
	colorcomible.rojo = 255;
	colorcomible.verde = 0;
	colorcomible.azul = 100;	

}
Vector2D ListaCasilla::getPosicion(int i, int j)
{
	return matriz[i][j]->getPosicion();
}
bool ListaCasilla::agregar(Casilla* f)
{
	if (fila < DIM)
	{
		if (columna < DIM) 
		{
			matriz[fila][columna] = f;
			columna++;
			return true;
		}
		else 
		{
			fila++;
			columna = 0;
		}
	}
	else 
	{
		return false;
	}
}

void ListaCasilla::Dibuja()
{
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			matriz[i][j]->Dibuja();
		}
	}
}

void ListaCasilla::setOcupacion(int i,int j, int oc) 
{
	matriz[i][j]->setOcupacion(oc);
}

Vector2D ListaCasilla::posibilidades(int filasel, int columsel, int turno, bool reina, bool DoubleEat, int u, int mostrar) //RETORNA 1 SI PUEDE COMER
//MUESTRA TODAS LAS POSIBILIDADES ASÍ COMO CAMBIA LOS ATRIBUTOS A LAS CASILLAS PARA PODER REALIZAR MOVIMIENTOS. DEVUELVE VALORES DE CanEat y CanMove PARA COMPROBAR ENCIERRO
{
	Vector2D aux;
	int CanMove = 0;
	int CanEat = 0;
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			matriz[i][j]->setPosible(0);
		}
	}
	if (turno == 1)
	{
		if (reina == false)
		{
			if (filasel != 7)
			{
				//mover izq
				if (columsel != 0 && DoubleEat == 0)
				{
					if (matriz[filasel + 1][columsel - 1]->getOcupacion() == 0)
					{
						if (u)
						{
							if(mostrar)
							matriz[filasel + 1][columsel - 1]->setColor(colorposible.rojo, colorposible.verde, colorposible.azul);
							matriz[filasel + 1][columsel - 1]->setPosible(1);

						}
						CanMove = 1;
					}
				}
				//mover der
				if (columsel != 7 && columsel <= 6 && DoubleEat == 0)
				{
					if (matriz[filasel + 1][columsel + 1]->getOcupacion() == 0)
					{
						if (u)
						{
							if (mostrar)
							matriz[filasel + 1][columsel + 1]->setColor(colorposible.rojo, colorposible.verde, colorposible.azul);
							matriz[filasel + 1][columsel + 1]->setPosible(1);
						}
						CanMove = 1;
					}
				}
				if (filasel < 6)
				{
					//comer izq
					if (columsel != 1)
					{
						if ((matriz[filasel + 1][columsel - 1]->getOcupacion() == 2) && (matriz[filasel + 2][columsel - 2]->getOcupacion() == 0))//DERECHA
						{
							if (u)
							{
								if (mostrar)
								matriz[filasel + 2][columsel - 2]->setColor(colorcomible.rojo, colorcomible.verde, colorcomible.azul);
								matriz[filasel + 2][columsel - 2]->setPosible(2);
							}
							CanEat = 1;
						}
					}
					if (columsel != 6)
					{
						//comer der
						if ((matriz[filasel + 1][columsel + 1]->getOcupacion() == 2) && (matriz[filasel + 2][columsel + 2]->getOcupacion() == 0))//DERECHA
						{
							if (u)
							{
								if (mostrar)
								matriz[filasel + 2][columsel + 2]->setColor(colorcomible.rojo, colorcomible.verde, colorcomible.azul);
								matriz[filasel + 2][columsel + 2]->setPosible(1);
							}
							CanEat = 1;
						}
					}
				}
			}
		}
	
	}
	if (turno == 2)
	{
		if (reina == false)
		{
			if (filasel != 0)
			{
				//mover izq
				if (columsel != 0 && DoubleEat == 0)
				{
					if (matriz[filasel - 1][columsel - 1]->getOcupacion() == 0)
					{
						if (u)
						{
							if (mostrar)
							matriz[filasel - 1][columsel - 1]->setColor(colorposible.rojo, colorposible.verde, colorposible.azul);
							matriz[filasel - 1][columsel - 1]->setPosible(1);
						}
						CanMove = 1;
					}
				}
				//mover der
				if (columsel != 7 && columsel <= 6 && DoubleEat == 0)
				{
					if (matriz[filasel - 1][columsel + 1]->getOcupacion() == 0)
					{
						if (u)
						{
							if (mostrar)
							matriz[filasel - 1][columsel + 1]->setColor(colorposible.rojo, colorposible.verde, colorposible.azul);
							matriz[filasel - 1][columsel + 1]->setPosible(1);
						}
						CanMove = 1;
					}
				}
				if (filasel > 1)
				{
					//comer izq
					if (columsel != 1)
					{
						if ((matriz[filasel - 1][columsel - 1]->getOcupacion() == 1) && (matriz[filasel - 2][columsel - 2]->getOcupacion() == 0))//DERECHA
						{
							if (u)
							{
								if (mostrar)
								matriz[filasel - 2][columsel - 2]->setColor(colorcomible.rojo, colorcomible.verde, colorcomible.azul);
								matriz[filasel - 2][columsel - 2]->setPosible(2);
							}
							CanEat = 1;
						}
					}
					if (columsel != 6)
					{
						//comer der
						if ((matriz[filasel - 1][columsel + 1]->getOcupacion() == 1) && (matriz[filasel - 2][columsel + 2]->getOcupacion() == 0))//DERECHA
						{
							if (u)
							{
								if (mostrar)
								matriz[filasel - 2][columsel + 2]->setColor(colorcomible.rojo, colorcomible.verde, colorcomible.azul);
								matriz[filasel - 2][columsel + 2]->setPosible(2);
							}
							CanEat = 1;
						}
					}
				}
			}
		}
	}
	if (reina == true) //ES REINA, EN FUNCION DE TURNO
	{
		int a;
		if (turno == 1)
		{
			a = 2;
		}
		if (turno == 2)
		{
			a = 1;
		}
		if (columsel != 0)
		{

			//Arriba izquierda
			if (filasel != 7)
			{
				int i; int j; int enemiga = 0;
				for (i = filasel + 1, j = columsel - 1; i <= 7 && j >= 0; i++, j--)
				{

					if (matriz[i][j]->getOcupacion() == turno)
					{
						break;
					}
					if (matriz[i][j]->getOcupacion() == a)
					{
						enemiga = 1;
					}
					if (matriz[i][j]->getOcupacion() == 0 && enemiga == 0 && DoubleEat == 0)
					{
						if (u)
						{
							if (mostrar)
							matriz[i][j]->setColor(colorposible.rojo, colorposible.verde, colorposible.azul);
							matriz[i][j]->setPosible(1);
						}
						CanMove = 1;
					}
					if (i <= 6 && columsel != 1 && j >= 1)
					{
						if (matriz[i + 1][j - 1]->getOcupacion() == 0 && enemiga == 1)
						{
							if (u)
							{
								if (mostrar)
								matriz[i + 1][j - 1]->setColor(colorcomible.rojo, colorcomible.verde, colorcomible.azul);
								matriz[i + 1][j - 1]->setPosible(2);
							}
							CanEat = 1;
						}
						if (matriz[i + 1][j - 1]->getOcupacion() == a && enemiga == 1)
						{
							break;
						}
					}
				}
			}
			//Abajo izquierda
			if (filasel != 0)
			{
				int i; int j; int enemiga = 0;
				for (i = filasel - 1, j = columsel - 1; i >= 0 && j >= 0; i--, j--)
				{

					if (matriz[i][j]->getOcupacion() == turno)
					{
						break;
					}
					if (matriz[i][j]->getOcupacion() == a)
					{
						enemiga = 1;
					}
					if (matriz[i][j]->getOcupacion() == 0 && enemiga == 0 && DoubleEat == 0)
					{
						if (u)
						{
							if (mostrar)
							matriz[i][j]->setColor(colorposible.rojo, colorposible.verde, colorposible.azul);
							matriz[i][j]->setPosible(1);
						}
						CanMove = 1;
					}
					if (i >= 1 && columsel != 1 && j >= 1)
					{
						if (matriz[i - 1][j - 1]->getOcupacion() == 0 && enemiga == 1)
						{
							if (u)
							{
								if (mostrar)
								matriz[i - 1][j - 1]->setColor(colorcomible.rojo, colorcomible.verde, colorcomible.azul);
								matriz[i - 1][j - 1]->setPosible(2);
							}
							CanEat = 1;
						}
						if (matriz[i - 1][j - 1]->getOcupacion() == a && enemiga == 1)
						{
							break;
						}
					}
				}
			}
		}
		if (columsel != 7 && columsel <= 6)
		{

			//Arriba derecha
			if (filasel != 7)
			{
				int i; int j; int enemiga = 0;
				for (i = filasel + 1, j = columsel + 1; i <= 7 && j <= 7; i++, j++)
				{

					if (matriz[i][j]->getOcupacion() == turno)
					{
						break;
					}
					if (matriz[i][j]->getOcupacion() == a)
					{
						enemiga = 1;
					}
					if (matriz[i][j]->getOcupacion() == 0 && enemiga == 0 && DoubleEat == 0)
					{
						if (u)
						{
							if (mostrar)
							matriz[i][j]->setColor(colorposible.rojo, colorposible.verde, colorposible.azul);
							matriz[i][j]->setPosible(1);
						}
						CanMove = 1;
					}
					if (i <= 6 && columsel != 6 && j <= 6)
					{
						if (matriz[i + 1][j + 1]->getOcupacion() == 0 && enemiga == 1)
						{
							if (u)
							{
								if (mostrar)
								matriz[i + 1][j + 1]->setColor(colorcomible.rojo, colorcomible.verde, colorcomible.azul);
								matriz[i + 1][j + 1]->setPosible(2);
							}
							CanEat = 1;
						}
						if (matriz[i + 1][j + 1]->getOcupacion() == a && enemiga == 1)
						{
							break;
						}
					}
				}
			}
			//Abajo derecha
			if (filasel != 0)
			{
				int i; int j; int enemiga = 0;
				for (i = filasel - 1, j = columsel + 1; i >= 0 && j <= 7; i--, j++)
				{

					if (matriz[i][j]->getOcupacion() == turno)
					{
						break;
					}
					if (matriz[i][j]->getOcupacion() == a)
					{
						enemiga = 1;
					}
					if (matriz[i][j]->getOcupacion() == 0 && enemiga == 0 && DoubleEat == 0 )
					{
						if (u)
						{
							if (mostrar)
							matriz[i][j]->setColor(colorposible.rojo, colorposible.verde, colorposible.azul);
							matriz[i][j]->setPosible(1);
						}
						CanMove = 1;
					}
					if (i >= 1 && columsel != 6 && j <= 6)
					{
						if (matriz[i - 1][j + 1]->getOcupacion() == 0 && enemiga == 1)
						{
							if (u)
							{
								if (mostrar)
								matriz[i - 1][j + 1]->setColor(colorcomible.rojo, colorcomible.verde, colorcomible.azul);
								matriz[i - 1][j + 1]->setPosible(2);
							}
							CanEat = 1;
						}
						if (matriz[i - 1][j + 1]->getOcupacion() == a && enemiga == 1)
						{
							break;
						}
					}
				}
			}
		}
	}
	aux.x = CanMove;
	aux.y = CanEat;
	return aux;
}
int ListaCasilla::getFila()
{
	return fila;
}
int ListaCasilla::getColumna()
{
	return columna;
}
void ListaCasilla::setFila(int i)
{
	fila = i;
}
void ListaCasilla::setColumna(int i)
{
	columna = i;
}
void ListaCasilla::resetColor() {
	
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++)
		{
				if ((i + j) % 2 == 0)
				{
					matriz[i][j]->setColor(50, 50, 50); // casilla negra
				}
				else 
				{
					matriz[i][j]->setColor(200, 200, 200); // casilla blanca
					
				}
	
		}
	}

}

void ListaCasilla::setSeleccionada(int x, int y)
{
	matriz[y][x]->setSeleccionada(1);
}
int ListaCasilla::CanMove(int x,int y) //MOVIMIENTO LEGAL O ILEGAL
{
	if (matriz[y][x]-> getPosible() == 1 || matriz[y][x]->getPosible() == 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
Casilla* ListaCasilla::devuelveCasilla(int x, int y) //ALTERNATIVA A LA SOBRECARGA DE LOS OPERADORES [] []
{
	return matriz[y][x];
}
