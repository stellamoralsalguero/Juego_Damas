#pragma once
#include"Juego.h"
class Coordinador 
{
public:
	Coordinador();

	void Raton(int button, int state, int x, int y);
	void tecla(unsigned char key);
	void mueve();
	void dibuja();

	int GetEstado();
private:
	enum Estado { INICIO, JUEGO, MAQUINA, PRESENTACION, GAMEOVER_BLANCAS, GAMEOVER_NEGRAS, TABLAS, REGLAS};
	Estado estado;
	Juegos juego;
};