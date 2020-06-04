#include"Coordinador.h"
#include"../include/ETSIDI.h"
#include"../include/glut.h"

Coordinador::Coordinador() 
{
	estado = INICIO;
	juego.SetOjo(25, -25, 30);
	ETSIDI::playMusica("../sonidos/DANGER.mp3");
}

void Coordinador::tecla(unsigned char key) 
{
	if (estado == INICIO) 
	{
        if (key == 'e' || key == 'E')
        {
            estado = PRESENTACION;
        }
        else if (key == 'm' || key == 'M')
        {
            estado = MAQUINA;
            ETSIDI::stopMusica();
        }
        else if (key == 'r' || key == 'R')
        {
            estado = REGLAS;
        }
        else if (key == 's' || key == 'S')
        {
            exit(0);
        }
	}
    else if (estado == REGLAS)
    {
        if (key == 'e' || key == 'E')
        {
            estado = PRESENTACION;
        }
        else if (key == 'm' || key == 'M')
        {
            estado = MAQUINA;
            ETSIDI::stopMusica();
        }
        else if (key == 's' || key == 'S')
        {
            exit(0);
        }
    }
	else if (estado == PRESENTACION) 
	{		
		if (key == ' ') 
		{
			ETSIDI::stopMusica();
			estado = JUEGO;
		}
	}
	else if (estado == JUEGO)
	{
		if (juego.getTurno() == 1)
		{
			if (key == ' ' && juego.getDoubleEat() == 1)
			{
				juego.setTurno(2);
				juego.setDoubleEat(0);
			}
		}
		else if (juego.getTurno() == 2)
		{
			if (key == ' ' && juego.getDoubleEat() == 1)
			{
				juego.setTurno(1);
                juego.SetFichaSeleccionada();
				juego.setDoubleEat(0);
			}
		}
	}
    else if (estado == MAQUINA)
    {
        if (juego.getTurno() == 1)
        {
            if (key == ' ' && juego.getDoubleEat() == 1)
            {
                
                juego.setTurno(2);
                juego.SetFichaSeleccionada();
                juego.setDoubleEat(0);
            }
        }
    }
    else if (estado == GAMEOVER_BLANCAS || estado == GAMEOVER_NEGRAS || estado == TABLAS)
    {
        if (key == 's' || key == 'S')
        {
            exit(0);
        }
    }
    
}

void Coordinador::mueve() 
{
	if (estado == JUEGO)
	{
		if (juego.GetOscurasComidas() != 12 && juego.GetClarasComidas() != 12 && juego.GetEncerrada().x == 0 && juego.GetEncerrada().y == 0)
		{
            if (juego.GetClarasComidas() == 11 && juego.GetOscurasComidas() == 11)
            {
                estado = TABLAS;
                ETSIDI::playMusica("../sonidos/Tablas.mp3"); //CANCIÓN AMIGOS PARA SIEMPRE
            }
            else
            juego.Play(1);
		}
		else if (juego.GetOscurasComidas() == 12 || juego.GetEncerrada().y == 1)
		{
			estado = GAMEOVER_NEGRAS;
            ETSIDI::playMusica("../sonidos/loser.mp3");
		}
		else if (juego.GetClarasComidas() == 12 || juego.GetEncerrada().x == 1)
		{
			estado = GAMEOVER_BLANCAS;
            ETSIDI::playMusica("../sonidos/loser.mp3");
		}
	}
    else if (estado == MAQUINA)
    {
        if (juego.GetOscurasComidas() != 12 && juego.GetClarasComidas() != 12 && juego.GetEncerrada().x == 0 && juego.GetEncerrada().y == 0)
        {
             if (juego.GetClarasComidas() == 11 && juego.GetOscurasComidas() == 11)
             {
                 estado = TABLAS;
                 ETSIDI::playMusica("../sonidos/Tablas.mp3"); //CANCIÓN AMIGOS PARA SIEMPRE
             }
             else
            juego.Play(2);
        }
        else if (juego.GetOscurasComidas() == 12 || juego.GetEncerrada().y == 1)
        {
            estado = GAMEOVER_NEGRAS;
            ETSIDI::playMusica("../sonidos/loser.mp3");
        }
        else if (juego.GetClarasComidas() == 12 || juego.GetEncerrada().x == 1)
        {
            estado = GAMEOVER_BLANCAS;
            ETSIDI::playMusica("../sonidos/loser.mp3");
        }
    }
	else if (estado == PRESENTACION) 
	{
		juego.presentacion();
	}
}

void Coordinador::dibuja() 
{
    if (estado == INICIO)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 7.5, 30, // posicion del ojo
            0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0)
            0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("../imagenes/arthurs.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);

        glColor3f(1, 1, 1);
        glTexCoord2d(0, 1);        glVertex3f(-10, 3, -0.1);
        glTexCoord2d(1, 1);        glVertex3f(10, 3, -0.1);
        glTexCoord2d(1, 0);        glVertex3f(10, 18, -0.1);
        glTexCoord2d(0, 0);        glVertex3f(-10, 18, -0.1);
        glEnd();

        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        ETSIDI::setTextColor(255, 255, 255);
        ETSIDI::setFont("../fuentes/GrandHotel-Regular.ttf", 40);
        ETSIDI::printxy("Damas", -5, 8);
        ETSIDI::setTextColor(255, 255, 255);
        ETSIDI::setFont("../fuentes/Timeless.ttf", 20);
        ETSIDI::printxy("Pulse la tecla 'E' para multijugador", -10, 1);
        ETSIDI::printxy("Pulse la tecla 'M' para jugar contra la maquina", -10, 0);
        ETSIDI::printxy("Pulse la tecla 'R' para leer las reglas", -10, -1);
        ETSIDI::printxy("Pulse la tecla 'S' para salir", -10, -2);
        glutSwapBuffers();

    }
    else if (estado == REGLAS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 7.5, 30, // posicion del ojo
            0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0)
            0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("../imagenes/textura.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);

        glColor3f(1, 1, 1);
        glTexCoord2d(0, 1);        glVertex3f(-20, -20, -0.1);
        glTexCoord2d(1, 1);        glVertex3f(20, -20, -0.1);
        glTexCoord2d(1, 0);        glVertex3f(20, 20, -0.1);
        glTexCoord2d(0, 0);        glVertex3f(-20, 20, -0.1);
        glEnd();

        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    
        ETSIDI::setTextColor(0, 0, 0);
        ETSIDI::setFont("../fuentes/Ubuntu.ttf", 30);
        ETSIDI::printxy("REGLAS", -3, 15);
        ETSIDI::setFont("../fuentes/Montserrat.ttf", 15);
        ETSIDI::printxy("CLICK PARA SELECCIONAR UNA FICHA", -13, 12);
        ETSIDI::printxy("Se mostrarán todos los posibles movimientos", -11, 11);
        ETSIDI::printxy("Seleccione una ficha tantas veces como quiera", -11, 10);
        ETSIDI::printxy("CLICK PARA SELECCIONAR EL DESTINO", -13, 8);
        ETSIDI::printxy("DESPUÉS DE COMER, PULSE ESPACIO PARA CAMBIAR DE TURNO", -13, 6);
        ETSIDI::setFont("../fuentes/Montserrat.ttf", 13);
        ETSIDI::printxy("PULSE LA TECLA 'E' PARA MULTIJUGADOR", -13, 0);
        ETSIDI::printxy("PULSE LA TECLA 'M' PARA JUGAR CONTRA LA MÁQUINA", -13, -1);
        ETSIDI::printxy("PULSE LA TECLA 'S' PARA SALIR", -13, -2);
        glutSwapBuffers();
    }
    else if (estado == JUEGO)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        juego.Inicializa();
        juego.SetOjo(5.4, 4, 11.5);
        gluLookAt(juego.GetX_Ojo(), juego.GetY_Ojo(), juego.GetZ_Ojo(),
                  juego.GetX_Ojo(), juego.GetY_Ojo(), 0.0,
                  0.0, 1.0, 0.0);
        juego.Dibuja(1);
        glutSwapBuffers();
    }
    else if (estado == MAQUINA)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        juego.Inicializa();
        juego.SetOjo(5.4, 4, 11.5);
        gluLookAt(juego.GetX_Ojo(), juego.GetY_Ojo(), juego.GetZ_Ojo(),
                  juego.GetX_Ojo(), juego.GetY_Ojo(), 0.0,
                   0.0, 1.0, 0.0);
        juego.Dibuja(1);
        glutSwapBuffers();
    }
    else if (estado == PRESENTACION)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        juego.Inicializa();
        gluLookAt(juego.GetX_Ojo(), juego.GetY_Ojo(), juego.GetZ_Ojo(),
                  4, 4, 0.0,
                  0.0, 0.0, 1.0);
        ETSIDI::setTextColor(255, 255, 255);
        ETSIDI::setFont("../fuentes/Timeless.ttf", 16);
        ETSIDI::printxy("Pulse la barra espaciadora para comenzar", -20, 5);

        juego.Dibuja(0);
        glutSwapBuffers();
    }
    else if (estado == GAMEOVER_BLANCAS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 7.5, 30, // posicion del ojo
                  0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0)
                  0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)

        ETSIDI::setTextColor(255, 255, 255);
        ETSIDI::setFont("../fuentes/Impact.ttf", 20);
        ETSIDI::printxy("GAMEOVER", -5, 12);
        ETSIDI::printxy("HAN PERDIDO: BLANCAS", -5, 10);
        ETSIDI::printxy("Pulse la tecla 'S' para salir", -5, 3);

        glutSwapBuffers();
    }

    else if (estado == GAMEOVER_NEGRAS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 7.5, 30, // posicion del ojo
                  0.0, 7.5, 0.0,    // hacia que punto mira (0,7.5,0)
                  0.0, 1.0, 0.0);   // definimos hacia arriba (eje Y)

        ETSIDI::setTextColor(255, 255, 255);
        ETSIDI::setFont("../fuentes/Impact.ttf", 20);
        ETSIDI::printxy("GAMEOVER", -5, 12);
        ETSIDI::printxy("HAN PERDIDO: NEGRAS", -5, 10);
        ETSIDI::printxy("Pulse la tecla 'S' para salir", -5, 3);

        glutSwapBuffers();
    }

    else if (estado == TABLAS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 7.5, 30, // posicion del ojo
            0.0, 7.5, 0.0,    // hacia que punto mira (0,7.5,0)
            0.0, 1.0, 0.0);   // definimos hacia arriba (eje Y)

        ETSIDI::setTextColor(255, 255, 255);
        ETSIDI::setFont("../fuentes/Impact.ttf", 20);
        ETSIDI::printxy("TABLAS", -5, 12);
        ETSIDI::printxy("No hay mas movimientos posibles", -5, 10);
        ETSIDI::printxy("Pulse la tecla 'S' para salir", -5, 3);

        glutSwapBuffers();
    }
}

void Coordinador::Raton(int button, int state, int x, int y) 
{
	juego.Raton(button, state, x, y);
}
int Coordinador::GetEstado()
{
	return estado;
}