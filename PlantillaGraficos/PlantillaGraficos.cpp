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

bool grid[10][10];


void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && (key == GLFW_KEY_RIGHT))
	{
		posXtriangulo += 0.01;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && (key == GLFW_KEY_LEFT))
	{
		posXtriangulo -= 0.01;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && (key == GLFW_KEY_UP))
	{
		posYtriangulo += 0.01;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && (key == GLFW_KEY_DOWN))
	{
		posYtriangulo -= 0.01;
	}
	*/
}

void actualizar()
{
	tiempoactual = glfwGetTime();

	double tiempoDiferencial = tiempoactual - tiempoanterior;


	int estadoderecha = glfwGetKey(window, GLFW_KEY_RIGHT);

	if (estadoderecha == GLFW_PRESS)
	{
		posXtriangulo += 0.5 * tiempoDiferencial;
	}


	int estadoizquierda = glfwGetKey(window, GLFW_KEY_LEFT);

	if (estadoizquierda == GLFW_PRESS)
	{
		posXtriangulo -= 0.5 * tiempoDiferencial;;
	}

	int estadoarriba = glfwGetKey(window, GLFW_KEY_UP);

	if (estadoarriba == GLFW_PRESS)
	{
		posYtriangulo += 0.5 * tiempoDiferencial;;
	}

	int estadoabajo = glfwGetKey(window, GLFW_KEY_DOWN);

	if (estadoabajo == GLFW_PRESS)
	{
		posYtriangulo -= 0.5 * tiempoDiferencial;;
	}

	int estadorotizquierda = glfwGetKey(window, GLFW_KEY_A);

	if(estadorotizquierda == GLFW_PRESS)
	{
		rotXtriangulo -= 24 * tiempoDiferencial;;
	}

	int estadorotderecha = glfwGetKey(window, GLFW_KEY_D);
	
	if (estadorotderecha == GLFW_PRESS)
	{
		rotXtriangulo += 24 * tiempoDiferencial;;
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

void generarGridAleatorio() {
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		int paredesX = 0;
		for (int j = 0; j < 10; j++) {
			grid[i][j] = (rand() % 5) == 0;
			paredesX++;
		}
	}
}

void dibujarMapa() {
	float unidad = 2.0f / 10.0f;
	float inicio = -1.0f;
	int count = 0;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (grid[i][j]) {
				glBegin(GL_POLYGON);
				glColor3f(0.0f, 0.0f, 0.0f);

				float prueba = inicio + i * unidad;
				float prueba2 = inicio + unidad + i * unidad;
				float prueba3 = inicio + j * unidad;
				float prueba4 = inicio + unidad + j * unidad;
				
				glVertex3f(inicio + i * unidad, inicio + j * unidad, 0.0f);
				glVertex3f(inicio + i * unidad, inicio + unidad + j * unidad, 0.0f);
				glVertex3f(inicio + unidad + i * unidad, inicio + unidad + j * unidad, 0.0f);
				glVertex3f(inicio + unidad + i * unidad, inicio + j * unidad, 0.0f);
				
				glEnd();
				count++;
			}
		}
	}
}

void dibujar() 
{
	dibujarMapa();
	//laberinto();
	

	glPushMatrix();

	glTranslatef(posXtriangulo, posYtriangulo,0.0f);

	glRotatef(1.0f,0.0f, rotXtriangulo,0.0f);

	glBegin(GL_TRIANGLES);

	glColor3f(0.2, 0.6, 0.1);

	glVertex3f(0.0f,0.15f,0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);

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

