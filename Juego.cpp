#include "Juego.h"
#include<math.h>
#include"../include/ETSIDI.h"
#include"../include/glut.h"
#define DIM 8

Juegos::Juegos() 
{
	DoubleEat = 0;
	TURNO = 1;
	Encerrada.x = 0;
	Encerrada.y = 0;
	seleccionada.x = -1;
	seleccionada.y = -1;
	N_claras_comidas = 0;
	N_oscuras_comidas = 0;
	a = 0;
	b = 0;
	c = 0;
	d = 0;
	fichaclara.rojo = 0;
	fichaclara.verde = 255;
	fichaclara.azul = 200;
	fichaoscura.rojo = 180;
	fichaoscura.verde = 65;
	fichaoscura.azul = 105;
	casillaclara.rojo = 200;
	casillaclara.verde = 200;
	casillaclara.azul = 200;
	casillaoscura.rojo = 50;
	casillaoscura.verde = 50;
	casillaoscura.azul = 50;
	fichaseleccionada.rojo = 250;
	fichaseleccionada.verde = 240;
	fichaseleccionada.azul = 70;
}

void Juegos::Comer(int i, int j) //i la que muevo, j la que desaparece
{
	if (TURNO == 1)
	{
		Mover(i);
		Tablero_completo.devuelveCasilla(FichasNegras[j]->GetPosicion().x, FichasNegras[j]->GetPosicion().y)->setOcupacion(0);
		FichasNegras[j]->setMuerta();
		N_oscuras_comidas += 1;
		if (N_oscuras_comidas == 5 || N_oscuras_comidas == 9)
		{
			a = 0;
			b++;
		}
		ETSIDI::playMusica("../sonidos/eexplode.wav");
		FichasNegras[j]->setPosicion(8 + a * 0.65, b * 0.65); //Desplazar al lateral en funcion del numero de comidas

		a++;
	}
	if (TURNO == 2)
	{
		Mover(i);
		Tablero_completo.devuelveCasilla(FichasBlancas[j]->GetPosicion().x, FichasBlancas[j]->GetPosicion().y)->setOcupacion(0);
		FichasBlancas[j]->setMuerta();
		N_claras_comidas += 1;
		if (N_claras_comidas == 5 || N_claras_comidas == 9)
		{
			c = 0;
			d++;
		}
		ETSIDI::playMusica("../sonidos/eexplode.wav");
		FichasBlancas[j]->setPosicion(8 + c * 0.65, 7 - d * 0.65); //Desplazar al lateral en funcion del numero de comidas
		c++;
	}
}

void Juegos::Mover(int i)
{
	if (TURNO == 1)
	{

		Tablero_completo.devuelveCasilla(FichasBlancas[i]->GetPosicion().x, FichasBlancas[i]->GetPosicion().y)->setOcupacion(0);
		FichasBlancas[i]->setPosicion(seleccionada.y, seleccionada.x);
		ETSIDI::playMusica("../sonidos/ficha.mp3");
		if (DoubleEat == 0)
		{
			FichasBlancas[i]->SetSeleccionada(0);
		}
		FichasBlancas.comprobarReina(1);
	}
	if (TURNO == 2)
	{
		Tablero_completo.devuelveCasilla(FichasNegras[i]->GetPosicion().x, FichasNegras[i]->GetPosicion().y)->setOcupacion(0);
		FichasNegras[i]->setPosicion(seleccionada.y, seleccionada.x);
		ETSIDI::playMusica("../sonidos/ficha.mp3");
		if (DoubleEat == 0)
		{
			FichasNegras[i]->SetSeleccionada(0);
		}
		FichasNegras.comprobarReina(2);
	}
}
void Juegos::Raton(int button, int state, int x, int y) //EXTRAPOLAR LA POSICIÓN DEL MOUSE DE LA PANTALLA AL TABLERO
{
	if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN))
	{
		if (y >= 14 && y < 584)
		{
			if (x >= 14 && x < 85.25)       seleccionada.y = 0;
			if (x >= 85.25 && x < 156.5)    seleccionada.y = 1;
			if (x >= 156.5 && x < 227.75)   seleccionada.y = 2;
			if (x >= 227.75 && x < 299)     seleccionada.y = 3;
			if (x >= 299 && x < 370.25)     seleccionada.y = 4;
			if (x >= 370.25 && x < 441.5)   seleccionada.y = 5;
			if (x >= 441.5 && x < 512.75)   seleccionada.y = 6;
			if (x >= 512.75 && x < 584)     seleccionada.y = 7;
		}
		//y
		if (x >= 14 && x < 584)
		{
			if (y >= 14 && y < 85.25)       seleccionada.x = 7;
			if (y >= 85.25 && y < 156.5)    seleccionada.x = 6;
			if (y >= 156.5 && y < 227.75)   seleccionada.x = 5;
			if (y >= 227.75 && y < 299)     seleccionada.x = 4;
			if (y >= 299 && y < 370.25)     seleccionada.x = 3;
			if (y >= 370.25 && y < 441.5)   seleccionada.x = 2;
			if (y >= 441.5 && y < 512.75)   seleccionada.x = 1;
			if (y >= 512.75 && y < 584)     seleccionada.x = 0;
		}
	}
	Tablero_completo.setSeleccionada(seleccionada.y, seleccionada.x);
}

void Juegos::Comprobar_Posicion() //SE UTILIZA PARA VER EL ESTADO DEL TABLERO EN TODO MOMENTO, SI TIENE FICHA O NO Y DE QUÉ COLOR
{

	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			for (int k = 0; k < 12; k++)
			{
				if ((FichasBlancas[k]->GetPosicion().x == Tablero_completo.getPosicion(i, j).x) && (FichasBlancas[k]->GetPosicion().y == Tablero_completo.getPosicion(i, j).y))
				{
					Tablero_completo.setOcupacion(i, j, 1); //1 ocupado de blancas
				}
				else if ((FichasNegras[k]->GetPosicion().x == Tablero_completo.getPosicion(i, j).x) && (FichasNegras[k]->GetPosicion().y == Tablero_completo.getPosicion(i, j).y))
				{
					Tablero_completo.setOcupacion(i, j, 2); //2 ocupado de negras
				}
			}
		}
	}
}
void Juegos::Dibuja(int i) //VARIABLE AUXILIAR 'i' PARA QUE NO SE DIBUJE EL TEXTO EN LA PRESENTACIÓN
{
	FichasBlancas.Dibuja();
	FichasNegras.Dibuja();
	Tablero_completo.Dibuja();
	mesita.Dibuja();
	if (i)
	{
		if (TURNO == 1)
		{
			ETSIDI::setTextColor(255, 255, 255);
			ETSIDI::setFont("../fuentes/PatrickHandSC-Regular.ttf", 20);
			ETSIDI::printxy("   TURNO: CLARAS", 8.5, 4);
			if (DoubleEat == 1)
			{
				ETSIDI::setTextColor(0, 0, 0);
				ETSIDI::setFont("../fuentes/PatrickHandSC-Regular.ttf", 11.5);
				ETSIDI::printxy("      ESPACIO PARA TURNO OSCURAS", 8, 3.5);
			}
		}
		
		else if (TURNO == 2)
		{
			ETSIDI::setTextColor(255, 255, 255);
			ETSIDI::setFont("../fuentes/PatrickHandSC-Regular.ttf", 20);
			ETSIDI::printxy("   TURNO: OSCURAS", 8.5, 4);
			if (DoubleEat == 1)
			{
				ETSIDI::setTextColor(0, 0, 0);
				ETSIDI::setFont("../fuentes/PatrickHandSC-Regular.ttf", 11.5);
				ETSIDI::printxy("      ESPACIO PARA TURNO CLARAS", 8, 5.5);
			}
		}
		
	}
}
int Juegos::getTurno()
{
	return TURNO;
}
void Juegos::setTurno(int t)
{
	TURNO = t;
}
void Juegos::SetOjo(float x, float y, float z)
{
	x_ojo = x;
	y_ojo = y;
	z_ojo = z;
}
void Juegos::Inicializa() //INICIALIZA LAS CASILLAS Y LAS FICHAS. ESQUINA INFERIOR IZQUIERDA DEL TABLERO ES (0,0)
{
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			Casilla* casilla = new Casilla();
			casilla->setPos(j, i);
			if ((i + j) % 2 == 0)
			{
				casilla->setColor(casillaclara.rojo, casillaclara.verde, casillaclara.azul);
			}
			else
			{
				casilla->setColor(casillaoscura.rojo, casillaoscura.verde, casillaoscura.azul);
			}
			casilla->setPosible(0);
			Tablero_completo.agregar(casilla);
		}
		Tablero_completo.setFila(Tablero_completo.getFila() + 1);
		Tablero_completo.setColumna(0);
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 0)
			{
				Fichas* aux = new Fichas(j, i);
				if (i >= 0 && i <= 2)			  //FILA 0,1,2
				{
					aux->SetColor(fichaclara.rojo, fichaclara.verde, fichaclara.azul);
					FichasBlancas.agregar(aux);
				}
				if (i >= 5 && i <= 7)
				{
					aux->SetColor(fichaoscura.rojo, fichaoscura.verde, fichaoscura.azul);
					FichasNegras.agregar(aux);
				}
			}
		}
	}
}
void Juegos::AccionMaquina() //LLAMADA EN EL MODO HOMBRE-MAQUINA
{

	bool flag = 0;
	for (int i = 0; i < 12; i++) //PRIORIDAD DE COMER, PRIMERA FICHA QUE PUEDA
	{
		int PuedeComer=0;
		PuedeComer = Tablero_completo.posibilidades(FichasNegras[i]->GetPosicion().y, FichasNegras[i]->GetPosicion().x, TURNO, FichasNegras[i]->getReina(), 0, 1, 0).y;
		if (PuedeComer == 1 && FichasNegras[i]->getReina() == 0)
		{
			Vector2D casilla;
			casilla = LeerPosibles(1);
			int j;
			j = detectarcomida(FichasNegras[i]->GetPosicion().y, FichasNegras[i]->GetPosicion().x);
			ComerMaquina(i, casilla.x, casilla.y,j);//i se mueve, j es la comida
			flag = 1;
			break;
		}
	}
	while (flag == 0) //MIENTRAS NO REALICE UN MOVIMIENTO
	{
		int azar = ETSIDI::lanzaDado(11);
		int PuedeMover = 0;
		PuedeMover = Tablero_completo.posibilidades(FichasNegras[azar]->GetPosicion().y, FichasNegras[azar]->GetPosicion().x, TURNO, FichasNegras[azar]->getReina(), 0, 1,0).x;
		if (PuedeMover == 1)
		{
			Vector2D casilla;
			casilla = LeerPosibles(0);
			MoverMaquina(azar, casilla.x, casilla.y); //.x es la columna
			flag = 1;
			break;
		}	
	}

	TURNO = 1;
	
}
int Juegos::detectarcomida(int filainicial, int columnainicial) //SE BARRE PARA VER LA FICHA COMIDA Y ELIMINARLA POSTERIORMENTE
{
	for (int j = 0; j < 12; j++) 
	{
	
		if ((FichasBlancas[j]->GetPosicion().x - columnainicial == 1)&&(FichasBlancas[j]->GetPosicion().y-filainicial==-1)) //Comemos a derechas
		{
			return j;
		}
		else if ((FichasBlancas[j]->GetPosicion().x - columnainicial == -1) && (FichasBlancas[j]->GetPosicion().y - filainicial == -1)) //Comemos a izquierdas
		{ 
			return j;
		}
		
	}
	
}
Vector2D Juegos::LeerPosibles(int c) //casillas a las que puede mover, elige la primera
{
	for (int j = 0; j < 8; j++)
	{
		for (int k = 0; k < 8; k++)
		{
			if (Tablero_completo.devuelveCasilla(j, k)->getPosible() == 1 && c == 0) //solo quiero mover
			{
				Vector2D aux;
				aux.x = j; //columna
				aux.y = k; //fila
				return aux; //devuelve la primera
			}
			if (Tablero_completo.devuelveCasilla(j, k)->getPosible() == 2 && c == 1) //quiero comer
			{
				Vector2D aux;
				aux.x = j; //columna
				aux.y = k; //fila
				return aux; //devuelve la primera
			}
		}
	}
}
void Juegos::MoverMaquina(int i, int columna, int fila)
{
	Tablero_completo.devuelveCasilla(FichasNegras[i]->GetPosicion().x, FichasNegras[i]->GetPosicion().y)->setOcupacion(0);
	FichasNegras[i]->setPosicion(columna, fila);
	ETSIDI::playMusica("../sonidos/ficha.mp3");
	FichasNegras.comprobarReina(2);
}
void Juegos::ComerMaquina(int i, int columna,int fila,int j)
{
	if (j >= 0 && j <= 11)
	{
		MoverMaquina(i, columna, fila);
		
		Tablero_completo.devuelveCasilla(FichasBlancas[j]->GetPosicion().x, FichasBlancas[j]->GetPosicion().y)->setOcupacion(0);
		Tablero_completo.devuelveCasilla(FichasNegras[i]->GetPosicion().x, FichasNegras[i]->GetPosicion().y)->setOcupacion(2);
		FichasBlancas[j]->setMuerta();
		N_claras_comidas += 1;
		if (N_claras_comidas == 5 || N_claras_comidas == 9)
		{
			c = 0;
			d++;
		}
		ETSIDI::playMusica("../sonidos/eexplode.wav");
		FichasBlancas[j]->setPosicion(8 + c * 0.65, 7 - d * 0.65);
		c++;
	}

}
void Juegos::presentacion() //MOVIMIENTO ROTATIVO
{
	float theta = atan2(y_ojo, x_ojo);
	float d = sqrt(pow(x_ojo, 2) + pow(y_ojo, 2));
	theta = theta + 0.01;
	SetOjo(d * cos(theta), d * sin(theta), z_ojo);
}

void Juegos::SetFichaSeleccionada() //SE UTILIZA PARA SELECCIONAR LA FICHA (SELECCIONADA = 1) Y CAMBIAR EL COLOR POSTERIORMENTE
{
	if (TURNO == 1)
	{
		for (int i = 0; i < 12; i++)
		{
			FichasNegras[i]->SetSeleccionada(0);
			if (Tablero_completo.devuelveCasilla(seleccionada.y, seleccionada.x)->getOcupacion() == 1 && DoubleEat == 0)
			{
				if (FichasBlancas[i]->GetPosicion().x == seleccionada.y && FichasBlancas[i]->GetPosicion().y == seleccionada.x)
				{
					FichasBlancas[i]->SetSeleccionada(1);
				}
				else
				{
					FichasBlancas[i]->SetSeleccionada(0);
				}
			}
		}
	}
	if (TURNO == 2)
	{
		for (int i = 0; i < 12; i++)
		{
			FichasBlancas[i]->SetSeleccionada(0);
			if (Tablero_completo.devuelveCasilla(seleccionada.y, seleccionada.x)->getOcupacion() == 2 && DoubleEat == 0)
			{
				if (FichasNegras[i]->GetPosicion().x == seleccionada.y && FichasNegras[i]->GetPosicion().y == seleccionada.x)
				{
					FichasNegras[i]->SetSeleccionada(1);
				}
				else
				{
					FichasNegras[i]->SetSeleccionada(0);
				}
			}
		}
	}
}
void Juegos::ResetColor() //RESETEA EL COLOR DE LAS NO SELECCIONADAS PARA PODER CAMBIAR DE FICHA SELECCIONADA
{
	for (int i = 0; i < 12; i++)
	{
		if (FichasBlancas[i]->GetSeleccionada() == 1)
		{
			FichasBlancas[i]->SetColor(fichaseleccionada.rojo, fichaseleccionada.verde, fichaseleccionada.azul);
		}
		else
		{
			FichasBlancas[i]->SetColor(fichaclara.rojo, fichaclara.verde, fichaclara.azul);
		}

		if (FichasNegras[i]->GetSeleccionada() == 1)
		{
			FichasNegras[i]->SetColor(fichaseleccionada.rojo, fichaseleccionada.verde, fichaseleccionada.azul);
		}
		else
		{
			FichasNegras[i]->SetColor(fichaoscura.rojo, fichaoscura.verde, fichaoscura.azul);
		}
	}
}

void Juegos::Play(int estado) //AQUÍ SE EXPANDE TODO EL JUEGO, DETERMINA CUÁNDO LLAMAR A LOS DISTINTOS MÉTODOS
{
	Tablero_completo.resetColor();

	Comprobar_Posicion();
	ComprobarEncierro();
	if (TURNO == 1)
	{
		int i;
		SetFichaSeleccionada();
		for (i = 0; i < 12; i++)
		{
			if (FichasBlancas[i]->GetSeleccionada() == 1)
				break;
		}
		if (i >= 0 && i < 12)
		{
			Tablero_completo.posibilidades(FichasBlancas[i]->GetPosicion().y, FichasBlancas[i]->GetPosicion().x, TURNO, FichasBlancas[i]->getReina(), DoubleEat, 1,1);

			if ((Tablero_completo.CanMove(seleccionada.y, seleccionada.x) == 1) && (FichasBlancas[i]->GetSeleccionada() == 1))
			{
				int a = FichasBlancas[i]->GetPosicion().y; //fila en la que esta la ficha que quiero mover
				int b = FichasBlancas[i]->GetPosicion().x; //columna en la que esta la ficha que quiero mover
				int c = seleccionada.x; //fila final
				int d = seleccionada.y; //columna final
				int k, m;
				if (FichasBlancas[i]->getReina() == false)
				{
					if (d - b == 2 || d - b == -2) //-2 he comido a la izquierda, 2 a la derecha
					{
						if (d - b == -2) //he comido a la izquierda
						{
							int p = Tablero_completo.posibilidades(FichasBlancas[i]->GetPosicion().y, FichasBlancas[i]->GetPosicion().x, TURNO, FichasBlancas[i]->getReina(), DoubleEat, 1, 1).y;
							for (int j = 0; j < 12; j++) //detectar que ficha como
							{

								int e = FichasNegras[j]->GetPosicion().y; //fila de la ficha comida
								int f = FichasNegras[j]->GetPosicion().x; //columna de la ficha comida
								if (f == b - 1 && e == a + 1)
								{

									if (p == 1)
									{
										DoubleEat = 1;
										Comer(i, j);
									}


								}

							}

						}
						else if (d - b == 2) //he comido a la derecha
						{
							int p = Tablero_completo.posibilidades(FichasBlancas[i]->GetPosicion().y, FichasBlancas[i]->GetPosicion().x, TURNO, FichasBlancas[i]->getReina(), DoubleEat, 1, 1).y;
							for (int j = 0; j < 12; j++)
							{
								int e = FichasNegras[j]->GetPosicion().y; //fila de la ficha comida
								int f = FichasNegras[j]->GetPosicion().x; //columna de la ficha comida
								if (f - b == 1 && e - a == 1)
								{
									if (p == 1)
									{
										DoubleEat = 1;
										Comer(i, j);
									}
								}
							}
						}
					}
					else
					{
						Mover(i);
						TURNO = 2;
					}
				}
				if (FichasBlancas[i]->getReina() == true)
				{ //ESTO SE HACE PARA DETECTAR LA FICHA COMIDA
					if (c - a > 0) //HACIA ARRIBA (MOVER O COMER, HAY QUE DIFERENCIAR BUSCANDO PIEZA EN DIAGONAL)
					{
						if (d - b > 0) //ARRIBA DERECHA
						{
							int p = Tablero_completo.posibilidades(FichasBlancas[i]->GetPosicion().y, FichasBlancas[i]->GetPosicion().x, TURNO, FichasBlancas[i]->getReina(), DoubleEat, 1, 1).y;
							for (k = a, m = b; k < c && m < d; k++, m++)
							{
								{
									for (int j = 0; j < 12; j++)
									{
										if (FichasNegras[j]->GetPosicion().x == m && FichasNegras[j]->GetPosicion().y == k)
										{
											if (p == 1)
											{
												DoubleEat = 1;
												Comer(i, j);
											}
										}
									}
								}
							}

							if (TURNO == 1 && DoubleEat == 0)
							{
								Mover(i);
								TURNO = 2;
							}
						}
						if (d - b < 0) //ARRIBA IZQUIERDA
						{
							int p = Tablero_completo.posibilidades(FichasBlancas[i]->GetPosicion().y, FichasBlancas[i]->GetPosicion().x, TURNO, FichasBlancas[i]->getReina(), DoubleEat, 1, 1).y;
							for (k = a, m = b; k < c && m > d; k++, m--)
							{
								{
									for (int j = 0; j < 12; j++)
									{
										if (FichasNegras[j]->GetPosicion().x == m && FichasNegras[j]->GetPosicion().y == k)
										{
											if (p == 1)
											{
												DoubleEat = 1;
												Comer(i, j);
											}
										}
									}
								}
							}
							if (TURNO == 1 && DoubleEat == 0)
							{
								Mover(i);
								TURNO = 2;
							}
						}
					}
					if (c - a < 0) //HACIA ABAJO
					{
						if (d - b > 0) //ABAJO DERECHA
						{
							int p = Tablero_completo.posibilidades(FichasBlancas[i]->GetPosicion().y, FichasBlancas[i]->GetPosicion().x, TURNO, FichasBlancas[i]->getReina(), DoubleEat, 1, 1).y;
							for (k = a, m = b; k > c && m < d; k--, m++)
							{
								//if (k <= 6 && m >= 1)
								{
									for (int j = 0; j < 12; j++)
									{
										if (FichasNegras[j]->GetPosicion().x == m && FichasNegras[j]->GetPosicion().y == k)
										{
											if (p == 1)
											{
												DoubleEat = 1;
												Comer(i, j);
											}
										}
									}
								}
							}
							if (TURNO == 1 && DoubleEat == 0)
							{
								Mover(i);
								TURNO = 2;
							}
						}
						if (d - b < 0) //ABAJO IZQUIERDA
						{
							int p = Tablero_completo.posibilidades(FichasBlancas[i]->GetPosicion().y, FichasBlancas[i]->GetPosicion().x, TURNO, FichasBlancas[i]->getReina(), DoubleEat, 1, 1).y;
							for (k = a, m = b; k > c && m > d; k--, m--)
							{
								{
									for (int j = 0; j < 12; j++)
									{
										if (FichasNegras[j]->GetPosicion().x == m && FichasNegras[j]->GetPosicion().y == k)
										{
											if (p == 1)
											{
												DoubleEat = 1;
												Comer(i, j);
											}
										}
									}
								}
							}
							if (TURNO == 1 && DoubleEat == 0)
							{
								Mover(i);
								TURNO = 2;
							}
						}
					}
				}
			}

		}
	}
	Comprobar_Posicion();
	if (estado == 1)
	{
		if (TURNO == 2)
		{

			int i;
			SetFichaSeleccionada();
			for (i = 0; i < 12; i++)
			{
				if (FichasNegras[i]->GetSeleccionada() == 1)
				{
					break;
				}
			}
			if (i >= 0 && i < 12)
			{
				Tablero_completo.posibilidades(FichasNegras[i]->GetPosicion().y, FichasNegras[i]->GetPosicion().x, TURNO, FichasNegras[i]->getReina(), DoubleEat, 1, 1);
				if ((Tablero_completo.CanMove(seleccionada.y, seleccionada.x) == 1) && (FichasNegras[i]->GetSeleccionada() == 1))
				{
					int a = FichasNegras[i]->GetPosicion().y; //fila en la que esta la ficha que quiero mover
					int b = FichasNegras[i]->GetPosicion().x; //columna en la que esta la ficha que quiero mover
					int c = seleccionada.x; //fila a la que voy
					int d = seleccionada.y; //columna a la que voy
					int k, m;
					if (FichasNegras[i]->getReina() == false)
					{
						if (d - b == 2 || d - b == -2) //he comido
						{

							if (d - b == -2) //he comido a la izquierda
							{
								int p = Tablero_completo.posibilidades(FichasNegras[i]->GetPosicion().y, FichasNegras[i]->GetPosicion().x, TURNO, FichasNegras[i]->getReina(), DoubleEat, 1, 1).y;
								for (int j = 0; j < 12; j++) //detectar que ficha como
								{
									int e = FichasBlancas[j]->GetPosicion().y; //fila de la ficha comida
									int f = FichasBlancas[j]->GetPosicion().x; //columna de la ficha comida
									if (f - b == -1 && e - a == -1)
									{
										if (p == 1)
										{
											DoubleEat = 1;
											Comer(i, j);
										}
									}
								}
							}
							if (d - b == 2) //he comido a la derecha
							{
								int p = Tablero_completo.posibilidades(FichasNegras[i]->GetPosicion().y, FichasNegras[i]->GetPosicion().x, TURNO, FichasNegras[i]->getReina(), DoubleEat, 1, 1).y;
								for (int j = 0; j < 12; j++)
								{
									int e = FichasBlancas[j]->GetPosicion().y; //fila de la ficha comida
									int f = FichasBlancas[j]->GetPosicion().x; //columna de la ficha comida
									if (f - b == 1 && e - a == -1)
									{
										if (p == 1)
										{
											DoubleEat = 1;
											Comer(i, j);
										}
									}
								}
							}

						}
						else
						{
							Mover(i);
							TURNO = 1;
						}
					}
					else if (FichasNegras[i]->getReina() == true)
					{ //ESTO SE HACE PARA DETECTAR LA FICHA COMIDA
						if (c - a > 0) //HACIA ARRIBA (MOVER O COMER, HAY QUE DIFERENCIAR BUSCANDO PIEZA EN DIAGONAL)
						{
							if (d - b > 0) //HACIA DERECHA
							{
								int p = Tablero_completo.posibilidades(FichasNegras[i]->GetPosicion().y, FichasNegras[i]->GetPosicion().x, TURNO, FichasNegras[i]->getReina(), DoubleEat, 1, 1).y;
								for (k = a, m = b; k < c && m < d; k++, m++)
								{
									{
										for (int j = 0; j < 12; j++)
										{
											if (FichasBlancas[j]->GetPosicion().x == m && FichasBlancas[j]->GetPosicion().y == k)
											{
												if (p == 1)
												{
													DoubleEat = 1;
													Comer(i, j);
												}
											}
										}
									}
								}

								if (TURNO == 2 && DoubleEat == 0)
								{
									Mover(i);
									TURNO = 1;
								}
							}

							if (d - b < 0) //HACIA IZQUIERDA
							{
								int p = Tablero_completo.posibilidades(FichasNegras[i]->GetPosicion().y, FichasNegras[i]->GetPosicion().x, TURNO, FichasNegras[i]->getReina(), DoubleEat, 1, 1).y;
								for (k = a, m = b; k <c && m > d; k++, m--)
								{
									{
										for (int j = 0; j < 12; j++)
										{
											if (FichasBlancas[j]->GetPosicion().x == m && FichasBlancas[j]->GetPosicion().y == k)
											{
												if (p == 1)
												{
													DoubleEat = 1;
													Comer(i, j);
												}
											}
										}
									}
								}
								if (TURNO == 2 && DoubleEat == 0)
								{
									Mover(i);
									TURNO = 1;
								}
							}
						}
						if (c - a < 0) //HACIA ABAJO
						{
							if (d - b > 0) //HACIA DERECHA
							{
								int p = Tablero_completo.posibilidades(FichasNegras[i]->GetPosicion().y, FichasNegras[i]->GetPosicion().x, TURNO, FichasNegras[i]->getReina(), DoubleEat, 1, 1).y;
								for (k = a, m = b; k > c && m < d; k--, m++)
								{
									{
										for (int j = 0; j < 12; j++)
										{
											if (FichasBlancas[j]->GetPosicion().x == m && FichasBlancas[j]->GetPosicion().y == k)
											{
												if (p == 1)
												{
													DoubleEat = 1;
													Comer(i, j);
												}
											}
										}
									}
								}
								if (TURNO == 2 && DoubleEat == 0)
								{
									Mover(i);
									TURNO = 1;
								}
							}
							if (d - b < 0) //HACIA IZQUIERDA
							{
								int p = Tablero_completo.posibilidades(FichasNegras[i]->GetPosicion().y, FichasNegras[i]->GetPosicion().x, TURNO, FichasNegras[i]->getReina(), DoubleEat, 1, 1).y;
								for (k = a, m = b; k > c && m > d; k--, m--)
								{
									{
										for (int j = 0; j < 12; j++)
										{
											if (FichasBlancas[j]->GetPosicion().x == m && FichasBlancas[j]->GetPosicion().y == k)
											{
												if (p == 1)
												{
													DoubleEat = 1;
													Comer(i, j);
												}
											}
										}
									}
								}
								if (TURNO == 2 && DoubleEat == 0)
								{
									Mover(i);
									TURNO = 1;
								}
							}
						}
					}
				}
			}

		}
		ResetColor();
		Dibuja(1);
	}
	//ResetColor();
	if (estado == 2) //maquina
	{
		seleccionada.x = -1; //para que no se quede seleccionada
		seleccionada.y = -1;
		if (TURNO == 2)
		{
			AccionMaquina();
		}
	}
	ResetColor();
	Dibuja(1);
}

float Juegos::GetX_Ojo()
{
	return x_ojo;
}
float Juegos::GetY_Ojo()
{
	return y_ojo;
}
float Juegos::GetZ_Ojo()
{
	return z_ojo;
}
int Juegos::getDoubleEat()
{
	return DoubleEat;
}
void Juegos::setDoubleEat(int d)
{
	DoubleEat = d;
}
int Juegos::GetClarasComidas()
{
	return N_claras_comidas;

}
int Juegos::GetOscurasComidas()
{
	return N_oscuras_comidas;
}
Vector2D Juegos::GetEncerrada()
{
	return Encerrada;
}
void Juegos::ComprobarEncierro() //BARRE TODAS LAS FICHAS Y SI AL MENOS UNA TIENE UNA OPORTUNIDAD DE MOVER Y/O COMER
{
	
	if (TURNO == 1) //llamo a posibilidades pasandole la posicion de cada ficha y que compruebe si alguna se puede mover tras movimiento del rival (llamada)
	{
		int aux1 = 1;
		int a = 0;
		int b = 0;
		for (int i = 0; i < 12; i++)
		{
			a = Tablero_completo.posibilidades(FichasBlancas[i]->GetPosicion().y, FichasBlancas[i]->GetPosicion().x, 1, FichasBlancas[i]->getReina(), 0,0,1).x; //si 1, puede mover
			b = Tablero_completo.posibilidades(FichasBlancas[i]->GetPosicion().y, FichasBlancas[i]->GetPosicion().x, 1, FichasBlancas[i]->getReina(), 0,0,1).y; //si 1, puede comer
			if (a == 1 && FichasBlancas[i]->getMuerta() == 0 || b == 1 && FichasBlancas[i]->getMuerta() == 0)
			{
				aux1 = 0; //no encerrada
				break;
			}
		}
		Encerrada.x = aux1; //BLANCA, 0 NO ENCERRADA, 1 ENCERRADA
	}
	else if (TURNO == 2)
	{
		int aux2 = 1;
		int c = 0;
		int d = 0;
		for (int j = 0; j < 12; j++)
		{
			c = Tablero_completo.posibilidades(FichasNegras[j]->GetPosicion().y, FichasNegras[j]->GetPosicion().x, 2, FichasBlancas[j]->getReina(), 0,0,1).x; //si 1, puede mover
			d = Tablero_completo.posibilidades(FichasNegras[j]->GetPosicion().y, FichasNegras[j]->GetPosicion().x, 2, FichasBlancas[j]->getReina(), 0,0,1).y; //si 1, puede comer
			if (c == 1 && FichasNegras[j]->getMuerta() == 0 || d == 1 && FichasNegras[j]->getMuerta() == 0)
			{
				aux2 = 0; //no encerrada
				break;
			}
		}
		Encerrada.y = aux2; //NEGRA, 0 NO ENCERRADA, 1 ENCERRADA
	}
}