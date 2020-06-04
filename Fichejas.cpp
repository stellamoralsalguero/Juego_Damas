#include<math.h>
#include "Fichejas.h"
#include"../include/ETSIDI.h"

Fichas::Fichas(float _x, float _y)
{
	posicion.x = _x;
	posicion.y = _y;
	radio = 0.35;
	seleccionada = 0;
	muerta = false;
	reina = false;
}
void Fichas::SetSeleccionada(int i)
{
	seleccionada = i;
}
int Fichas::GetSeleccionada()
{
	return seleccionada;
}
bool Fichas::getMuerta()
{
	return muerta;
}
void Fichas::Dibuja() 
{
	
	glEnable(GL_LIGHTING);
	if (reina)
	{
		glColor3ub(color.rojo, color.verde, color.azul);
		glTranslatef(posicion.x + 0.5, posicion.y + 0.5, 0);
		glutSolidCube(0.65);
		glTranslatef(-posicion.x - 0.5, -posicion.y - 0.5, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("../imagenes/corona2.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);


		glTexCoord2d(0, 1);		glVertex3f(posicion.x + 0.35, posicion.y + 0.35, 0.65);
		glTexCoord2d(1, 1);		glVertex3f(posicion.x + 0.70, posicion.y + 0.35, 0.65);
		glTexCoord2d(1, 0);		glVertex3f(posicion.x + 0.7, posicion.y + 0.7, 0.65);
		glTexCoord2d(0, 0);		glVertex3f(posicion.x + 0.35, posicion.y + 0.7, 0.65);
		glEnd();

		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		glColor3ub(color.rojo, color.verde, color.azul);
		glTranslatef(posicion.x + 0.5, posicion.y + 0.5, 0);
		glutSolidSphere(0.3, 70, 70);
		glTranslatef(-posicion.x - 0.5, -posicion.y - 0.5, 0);
	}
	glDisable(GL_LIGHTING);
}
Vector2D Fichas::GetPosicion()
{
	return posicion;
}
void Fichas::setPosicion(float x, float y) 
{
	posicion.x = x;
	posicion.y = y;
}

void Fichas::SetColor(Byte r, Byte g, Byte b) 
{
	color.setcolor(r, g, b);
}
void Fichas::setReina(bool r) 
{
	reina = r;
}
bool Fichas::getReina() 
{
	return reina;
}
void Fichas::setMuerta() 
{
	muerta = true;
}
