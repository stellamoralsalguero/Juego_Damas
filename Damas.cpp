#pragma once
#include <stdio.h>
#include <math.h>
#include"Coordinador.h"
#include "Juego.h"
#include"Mesa.h"
#include "../include/glut.h"

void OnDraw(void);
void OnTimer(int value);
void OnKeyboardDown(unsigned char key, int x, int y);
void onMouse(int button, int state, int x, int y);

Coordinador coordinador;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("DAMAS");
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	glutDisplayFunc(OnDraw);
	glutTimerFunc(100, OnTimer, 0);
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(onMouse);
	glutMainLoop();

	return 0;
}
void OnDraw(void)
{
	coordinador.dibuja();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	coordinador.tecla(key);
	glutPostRedisplay();
}
void onMouse(int button, int state, int x, int y)
{
	if (coordinador.GetEstado() == 1 || coordinador.GetEstado() == 2)
	coordinador.Raton(button, state, x, y);
}

void OnTimer(int value)
{
	coordinador.mueve();
	glutTimerFunc(50, OnTimer, 0);
	glutPostRedisplay();
}