// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <random>
#include <time.h>

using namespace std;

double tiempoactual, tiempoanterior;

float posXtriangulo = 0.0f, posYtriangulo = 0.0f,rotXtriangulo = 0.0f, rotYtriangulo = 0.0f;


//Declarar ventana
GLFWwindow* window;

int grid[10][10];

void generarGridAleatorio() {
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			bool crearPared = (rand() % 5) == 0;
			grid[i][j] = crearPared ? 3 : 0;
		}
	}
}

bool puedeMoverX(float offsetX) {
	float auxPosY = posYtriangulo + 1;
	float auxPosX = posXtriangulo + 1;

	float auxPosicionActualGridY = auxPosY * 5.0f;
	float auxPosicionActualGridX = (auxPosX + offsetX) * 5.0f;

	int posicionActualGridYTruncado = trunc(auxPosicionActualGridY);
	int posicionActualGridYRedondeado = round(auxPosicionActualGridY);
	int posicionActualGridX = trunc(auxPosicionActualGridX);

	float margenTolerancia = 0.10f;
	bool entraEnMargen = (auxPosicionActualGridY - posicionActualGridYTruncado <= 0.5 + margenTolerancia &&
		auxPosicionActualGridY - posicionActualGridYTruncado >= 0.5 - margenTolerancia);

	if (posicionActualGridYRedondeado == posicionActualGridYTruncado && !entraEnMargen) {
		posicionActualGridYTruncado--;
	}

	if (posicionActualGridYRedondeado != posicionActualGridYTruncado && entraEnMargen) {
		posicionActualGridYRedondeado--;
	}

	return grid[posicionActualGridX][posicionActualGridYTruncado] == 0 &&
		grid[posicionActualGridX][posicionActualGridYRedondeado] == 0 &&
		posicionActualGridX < 10 && auxPosicionActualGridX >= 0;
}

bool puedeMoverY(float offsetY) {
	float auxPosY = posYtriangulo + 1;
	float auxPosX = posXtriangulo + 1;

	float auxPosicionActualGridY = (auxPosY + offsetY) * 5.0f;
	float auxPosicionActualGridX = auxPosX * 5.0f;

	int posicionActualGridY = trunc(auxPosicionActualGridY);
	int posicionActualGridXTruncado = trunc(auxPosicionActualGridX);
	int posicionActualGridXRedondeado = round(auxPosicionActualGridX);

	float margenTolerancia = 0.10f;
	bool entraEnMargen = (auxPosicionActualGridX - posicionActualGridXTruncado <= 0.5 + margenTolerancia &&
		auxPosicionActualGridX - posicionActualGridXTruncado >= 0.5 - margenTolerancia);

	if (posicionActualGridXRedondeado == posicionActualGridXTruncado && !entraEnMargen) {
		posicionActualGridXTruncado--;
	}

	if (posicionActualGridXRedondeado != posicionActualGridXTruncado && entraEnMargen) {
		posicionActualGridXRedondeado--;
	}

	return grid[posicionActualGridXTruncado][posicionActualGridY] == 0 &&
		grid[posicionActualGridXRedondeado][posicionActualGridY] == 0 &&
		posicionActualGridY < 10 && auxPosicionActualGridY >= 0;
}

void actualizar()
{
	tiempoactual = glfwGetTime();

	double tiempoDiferencial = tiempoactual - tiempoanterior;

	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);

	if (estadoDerecha == GLFW_PRESS)
	{
		if (puedeMoverX(0.1f)) {
			posXtriangulo += 0.5 * tiempoDiferencial;
		}
	}

	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);

	if (estadoIzquierda == GLFW_PRESS)
	{
		if (puedeMoverX(-0.1f)) {
			posXtriangulo -= 0.5 * tiempoDiferencial;
		}
	}

	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);

	if (estadoArriba == GLFW_PRESS)
	{
		if (puedeMoverY(0.1f)) {
			posYtriangulo += 0.5 * tiempoDiferencial;
		}
	}

	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);

	if (estadoAbajo == GLFW_PRESS)
	{
		if (puedeMoverY(-0.1f)) {
			posYtriangulo -= 0.5 * tiempoDiferencial;
		}
	}

	int estadoRotIzquierda = glfwGetKey(window, GLFW_KEY_A);

	if(estadoRotIzquierda == GLFW_PRESS)
	{
		rotXtriangulo -= 24 * tiempoDiferencial;;
	}

	int estadoRotDerecha = glfwGetKey(window, GLFW_KEY_D);
	
	if (estadoRotDerecha == GLFW_PRESS)
	{
		rotXtriangulo += 24 * tiempoDiferencial;;
	}

	int estadoR = glfwGetKey(window, GLFW_KEY_R);
	
	if (estadoR == GLFW_PRESS) {
		generarGridAleatorio();
	}

	tiempoanterior = tiempoactual;
}

void laberinto()
{
	glBegin(GL_QUADS);

	glColor3f(1.0f, 1, 1.0f);

	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.0f, 0, 0.0f);

	glVertex3f(-0.9f, 0.9f, 0.0f);
	glVertex3f(0.9f, 0.9f, 0.0f);
	glVertex3f(0.9f, -0.9f, 0.0f);
	glVertex3f(-0.9f, -0.9f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(1.0f, 1, 1.0f);

	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glEnd();
}

void dibujarMapa() {
	float unidad = 2.0f / 10.0f;
	float inicio = -1.0f;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (grid[i][j] > 0) {
				glPushMatrix();
				glTranslatef(i * unidad, j * unidad, 0.0f);
				glBegin(GL_POLYGON);

				glColor3f(0.0f, 0.0f, 0.0f);
				
				glVertex3f(-1.0f, -1.0f, 0.0f);
				glVertex3f(-1.0f, -0.8f, 0.0f);
				glVertex3f(-0.8f, -0.8f, 0.0f);
				glVertex3f(-0.8f, -1.0f, 0.0f);
				
				glEnd();
				glPopMatrix();
			}
		}
	}
}

void dibujar() 
{
	//generarGridAleatorio();
	dibujarMapa();
	//laberinto();
	

	glPushMatrix();

	glTranslatef(posXtriangulo, posYtriangulo,0.0f);

	glRotatef(1.0f,0.0f, rotXtriangulo,0.0f);

	glBegin(GL_TRIANGLES);

	glColor3f(0.2, 0.6, 0.1);

	glVertex3f(0.0f,0.10f,0.0f);
	glVertex3f(-0.10f, -0.10f, 0.0f);
	glVertex3f(0.10f, -0.10f, 0.0f);

	glEnd();

	glPopMatrix();
}

int main()
{

	//Si no se pudo iniciar GLFW 
	//Terminamos ejecucion.

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	//Si se puedo iniciar GLFW
	//Inicializmos la ventana
	//Todas las funciones especificas de GLFW tienen el sufijo glfw
	window = glfwCreateWindow(1000,1000,"Ventana",NULL,NULL);

	//Si no pudo crear la ventana
	//Terminamos ejecucion
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	//Una vex establecido el contexto
	//Se activan las funciones "Modernas" (gpu) 

	
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK)
	{
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL = glGetString(GL_VERSION);
	cout << "Version Opengl: " << versionGL;

	tiempoactual = glfwGetTime();
	tiempoactual = tiempoanterior;

	//Establecemos que con cada evento de teclado
	// Se llama a la funcion telcado_callback
	//glfwSetKeyCallback(window, teclado_callback);

	generarGridAleatorio();

	//Ciclo de dibujo (Draw Loop)
	while (!glfwWindowShouldClose(window))
	{
		//Establecer region de dibujo
		glViewport(0, 0, 1000, 1000);
		//Establecemos el color de borrado.
		glClearColor(1,0.8,0,1);
		//Borrar!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Actualizar valores y dibujar

		dibujar();

		actualizar();


		glfwPollEvents();

		glfwSwapBuffers(window);

	}
	//Despues del ciclo de dibujo
	//Eliminamos venta y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}

