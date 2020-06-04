#include "Mesa.h"

Mesa::Mesa()
{
	x = y = z = 0;
    color.rojo = 151;
    color.verde = 121;
    color.azul = 97;
}

void Mesa::Dibuja()
{
    //DIBUJAR PATAS
    {
        glColor3ub(color.rojo, color.verde, color.azul);
        glLineWidth(5);
        glBegin(GL_LINE_LOOP);
        glVertex3f(-7, -7, -1);
        glVertex3f(-7, -7, -8);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex3f(-7, 15, -1);
        glVertex3f(-7, 15, -8);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex3f(13, 15, -1);
        glVertex3f(13, 15, -8);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex3f(15, -7, -1);
        glVertex3f(15, -7, -8);
        glEnd();
        glBegin(GL_POLYGON);
        glEnd();
    }
    //DIBUJAR PARTE SUPERIOR
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("../imagenes/Madera.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glTexCoord2d(0, 1);		glVertex3f(-8.0f, -8.0f, -1.0f);
        glTexCoord2d(1, 1);		glVertex3f(-8.0f, 16.0f, -1.0f);
        glTexCoord2d(1, 0);		glVertex3f(16.0f, 16.0f, -1.0f);
        glTexCoord2d(0, 0);		glVertex3f(16.0f, -8.0f, -1.0f);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }
    //DIBUJAR BORDE
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("../imagenes/borde.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glTexCoord2d(0, 0);		glVertex3f(-0.25f, -0.25f, -0.1f);
        glTexCoord2d(0, 1);		glVertex3f(-0.25f, 8.25f, -0.1f);
        glTexCoord2d(1, 1);		glVertex3f(8.25f, 8.25f, -0.1f);
        glTexCoord2d(1, 0);		glVertex3f(8.25f, -0.25f, -0.1f);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }
}