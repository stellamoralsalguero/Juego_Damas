#include"Casilla.h"

Casilla::Casilla() 
{
	color.rojo = color.verde = color.azul = 255;
	lado_casilla = 1;
	ocupacion = 0;		//Ocupacion=0 NO HAY FICHA
						//Ocupacion=1 FICHA BLANCA
						//Ocupacion=2 FICHA NEGRA
	posible = 0;
	seleccionada = 0;
}

void Casilla::setPos(float x, float y) 
{
	posicion.x = x;
	posicion.y = y;
}
Vector2D Casilla::getPosicion() 
{
	return posicion;
}
void Casilla::setOcupacion(int x) 
{
	ocupacion = x;
}

int Casilla::getOcupacion() 
{
 	return ocupacion;
}
void Casilla::setColor(Byte r, Byte g, Byte b) 
{
	color.setcolor(r, g, b);
}
void Casilla::setLado(float l) 
{
	lado_casilla = l;
}
float Casilla::getLado() 
{
	return lado_casilla;
}
void Casilla::Dibuja()
{
	glColor3ub(color.rojo, color.verde, color.azul);

	glBegin(GL_POLYGON);
	glVertex3f(posicion.x, posicion.y, 0.0f);
	glVertex3f(posicion.x, posicion.y + lado_casilla, 0.0f);
	glVertex3f(posicion.x + lado_casilla, posicion.y + lado_casilla, 0.0f);
	glVertex3f(posicion.x + lado_casilla, posicion.y, 0.0f);
	glEnd();
}
void Casilla::setPosible(int x) 
{
	posible = x;
}
int Casilla::getPosible() 
{
	return posible;
}
void Casilla::setSeleccionada(int i)
{
	seleccionada = i;
}