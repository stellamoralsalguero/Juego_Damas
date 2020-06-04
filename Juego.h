#pragma once
#include "Mesa.h"
#include"Fichejas.h"
#include"ListaFichas.h"
#include"ListaCasillas.h"
#include"Vector2D.h"
#include "ColorRGB.h"

class Juegos
{
private:
	int TURNO; //EMPIEZAN BLANCAS
	int DoubleEat;
	int N_claras_comidas;
	int N_oscuras_comidas;
	int a, b, c, d;

	float x_ojo;
	float y_ojo;
	float z_ojo;

	colorRGB fichaclara;
	colorRGB fichaoscura;
	colorRGB fichaseleccionada;
	colorRGB casillaclara;
	colorRGB casillaoscura;
	typedef unsigned char Byte;

	ListaFichas FichasBlancas;
	ListaFichas FichasNegras;
	ListaCasilla Tablero_completo;
	Mesa mesita;
	
	Vector2D seleccionada;
	Vector2D Encerrada; //0 ninguna, 1 blancas, 2 negras

public:
	Juegos();
	void Raton(int button, int state, int x, int y);
	void Dibuja(int);
	void SetOjo(float x_ojo, float y_ojo, float z_ojo);
	void Inicializa();
	void presentacion();
	void Play(int);
	void Comprobar_Posicion();
	void SetFichaSeleccionada();
	void ResetColor();
	void Mover(int);
	void Comer(int, int);
	void MoverMaquina(int, int, int);
	void ComerMaquina(int, int, int, int);
	void setTurno(int t);
	void setDoubleEat(int d);
	void ComprobarEncierro();
	void AccionMaquina();
	
	int getTurno();
	int getDoubleEat();
	int detectarcomida(int, int);
	int GetClarasComidas();
	int GetOscurasComidas();
	
	float GetX_Ojo();
	float GetY_Ojo();
	float GetZ_Ojo();
	
	Vector2D GetEncerrada();
	Vector2D LeerPosibles(int);
};