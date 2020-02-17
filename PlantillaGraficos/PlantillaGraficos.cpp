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

float posXtanque = 0.0f, posYtanque = 0.0f,rotXcanon = 0.0f, rotYtriangulo = 0.0f;

const float* axes;

int count;

int present;

float sensibilidadstick;

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
	float auxPosY = posYtanque + 1;
	float auxPosX = posXtanque + 1;

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
	float auxPosY = posYtanque + 1;
	float auxPosX = posXtanque + 1;

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

	int count;

	axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

	std::cout << " Number of axis avaiable " << axes[2] << std::endl;


	if (axes[0] > 0.3)
	{
		if (puedeMoverX(0.1f)) {
			posXtanque += 0.5 * tiempoDiferencial;
		}
	}


	if (axes[0] < -0.5)
	{
		if (puedeMoverX(-0.1f)) {
			posXtanque -= 0.5 * tiempoDiferencial;
		}
	}
	
	if (axes[1] < 0.5)
	{
		if (puedeMoverY(0.1f)) {
			posYtanque += 0.5 * tiempoDiferencial;
		}
	}
	
	if (axes[1] > -0.5)
	{ 
		if (puedeMoverY(-0.1f)) {
			posYtanque -= 0.5 * tiempoDiferencial;
		}
	}
	
	rotXcanon += axes[2] * -360 * tiempoDiferencial;

	int buttoncount;

	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttoncount);

	if (GLFW_PRESS == buttons[0])
	{
		std::cout << "Boton puchado" << std::endl;
	}

	int estadoR = glfwGetKey(window, GLFW_KEY_R);
	
	if (estadoR == GLFW_PRESS) {
		generarGridAleatorio();
	}

	tiempoanterior = tiempoactual;
}

void canon()
{
	//Cañon
	glPushMatrix();
	glTranslatef(posXtanque, posYtanque, 0.0f);
	glRotatef(rotXcanon, 0.0f, 0.0f, 1.0f);
	glScalef(0.1f, 0.1f, 0.0f);

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 1.0f, 0.6f);//White

	glVertex3f(-0.1f, 0.9f, 0.0f);
	glVertex3f(0.0f, 0.9f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(-0.1f, 0.2f, 0.0f);

	glEnd();

	glPopMatrix();
}

void tanque()
{
	glPushMatrix();

	glTranslatef(posXtanque, posYtanque, 0.0f);
	glRotatef(rotXcanon, 0.0f, 0.0f, 1.0f);
	glScalef(0.1f, 0.1f, 0.0f);

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 0.7f, 0.2f);//Orange

	glVertex3f(0.3f, 0.5f, 0.0f);
	glVertex3f(0.6f, 0.5f, 0.0f);
	glVertex3f(0.6f, -0.6f, 0.0f);
	glVertex3f(0.3f, -0.6f, 0.0f);


	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 0.7f, 0.2f);//Orange

	glVertex3f(0.4f, -0.6f, 0.0f);
	glVertex3f(0.6f, -0.6f, 0.0f);
	glVertex3f(0.6f, -0.7f, 0.0f);
	glVertex3f(0.4f, -0.7f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 0.7f, 0.2f);//Orange

	glVertex3f(-0.6f, 0.4f, 0.0f);
	glVertex3f(0.2f, 0.4f, 0.0f);
	glVertex3f(0.4f, -0.5f, 0.0f);
	glVertex3f(-0.6f, -0.5f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 0.7f, 0.2f);//Orange

	glVertex3f(-0.6f, -0.6f, 0.0f);
	glVertex3f(-0.4f, -0.6f, 0.0f);
	glVertex3f(-0.4f, -0.7f, 0.0f);
	glVertex3f(-0.6f, -0.7f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 0.7f, 0.2f);//Orange

	glVertex3f(-0.7f, 0.5f, 0.0f);
	glVertex3f(-0.6f, 0.5f, 0.0f);
	glVertex3f(-0.6f, 0.4f, 0.0f);
	glVertex3f(-0.7f, 0.4f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 1.0f, 0.6f);//White

	glVertex3f(-0.7f, 0.4f, 0.0f);
	glVertex3f(-0.6f, 0.4f, 0.0f);
	glVertex3f(-0.6f, -0.7f, 0.0f);
	glVertex3f(-0.7f, -0.7f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 1.0f, 0.6f);//White

	glVertex3f(-0.5f, 0.4f, 0.0f);
	glVertex3f(-0.3f, 0.4f, 0.0f);
	glVertex3f(-0.3f, 0.3f, 0.0f);
	glVertex3f(-0.5f, 0.3f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 1.0f, 0.6f);//White

	glVertex3f(-0.4f, 0.3f, 0.0f);
	glVertex3f(-0.2f, 0.3f, 0.0f);
	glVertex3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 1.0f, 0.6f);//White

	glVertex3f(-0.4f, 0.1f, 0.0f);
	glVertex3f(-0.3f, 0.1f, 0.0f);
	glVertex3f(-0.3f, -0.5f, 0.0f);
	glVertex3f(-0.4f, -0.5f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 1.0f, 0.6f);//White

	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(-0.2f, -0.5f, 0.0f);
	glVertex3f(-0.2f, -0.6f, 0.0f);
	glVertex3f(-0.5f, -0.6f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 1.0f, 0.6f);//White

	glVertex3f(-0.2f, -0.0f, 0.0f);
	glVertex3f(-0.1f, -0.0f, 0.0f);
	glVertex3f(-0.1f, -0.4f, 0.0f);
	glVertex3f(-0.2f, -0.4f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 1.0f, 0.6f);//White

	glVertex3f(-0.1, -0.3, 0.0f);
	glVertex3f(-0.0, -0.3, 0.0f);
	glVertex3f(-0.0, -0.4, 0.0f);
	glVertex3f(-0.1, -0.4, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(-0.6f, 0.5f, 0.0f);
	glVertex3f(-0.4f, 0.5f, 0.0f);
	glVertex3f(-0.4f, 0.4f, 0.0f);
	glVertex3f(-0.6f, 0.4f, 0.0f);


	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(-0.2f, 0.5f, 0.0f);
	glVertex3f(-0.1f, 0.5f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.2f, 0.4f, 0.0f);


	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.1f, 0.5f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(0.4f, 0.4f, 0.0f);
	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(0.1f, 0.1f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(0.4f, -0.6f, 0.0f);
	glVertex3f(0.2f, -0.6f, 0.0f);
	glVertex3f(0.2f, 0.1f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(0.1f, -0.5f, 0.0f);
	glVertex3f(0.2f, -0.5f, 0.0f);
	glVertex3f(0.2f, -0.6f, 0.0f);
	glVertex3f(0.1f, -0.6f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(0.4f, 0.5f, 0.0f);
	glVertex3f(0.6f, 0.5f, 0.0f);
	glVertex3f(0.6f, 0.4f, 0.0f);
	glVertex3f(0.4f, 0.4f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(0.4f, 0.3f, 0.0f);
	glVertex3f(0.6f, 0.3f, 0.0f);
	glVertex3f(0.6f, 0.2f, 0.0f);
	glVertex3f(0.4f, 0.2f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(0.6f, 0.1f, 0.0f);
	glVertex3f(0.6f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(0.4f, -0.1f, 0.0f);
	glVertex3f(0.6f, -0.1f, 0.0f);
	glVertex3f(0.6f, -0.2f, 0.0f);
	glVertex3f(0.4f, -0.2f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(0.4f, -0.3f, 0.0f);
	glVertex3f(0.6f, -0.3f, 0.0f);
	glVertex3f(0.6f, -0.4f, 0.0f);
	glVertex3f(0.4f, -0.4f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(0.4f, -0.5f, 0.0f);
	glVertex3f(0.6f, -0.5f, 0.0f);
	glVertex3f(0.6f, -0.6f, 0.0f);
	glVertex3f(0.4f, -0.6f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(0.1f, 0.1f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(-0.1f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, -0.3f, 0.0f);
	glVertex3f(0.0f, -0.3f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(-0.7f, 0.3f, 0.0f);
	glVertex3f(-0.5f, 0.3f, 0.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.7f, 0.2f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(-0.7f, 0.1f, 0.0f);
	glVertex3f(-0.5f, 0.1f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(-0.7f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(-0.7f, -0.1f, 0.0f);
	glVertex3f(-0.5f, -0.1f, 0.0f);
	glVertex3f(-0.5f, -0.2f, 0.0f);
	glVertex3f(-0.7f, -0.2f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(-0.7f, -0.3f, 0.0f);
	glVertex3f(-0.5f, -0.3f, 0.0f);
	glVertex3f(-0.5f, -0.4f, 0.0f);
	glVertex3f(-0.7f, -0.4f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);

	glVertex3f(-0.7f, -0.5, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, -0.6f, 0.0);
	glVertex3f(-0.7f, -0.6f, 0.0f);

	glEnd();

	glPopMatrix();
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

	canon();
	tanque();
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

     int present1 = glfwJoystickPresent(GLFW_JOYSTICK_1);

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

		cout << axes;

		glfwPollEvents();

		glfwSwapBuffers(window);

	}
	//Despues del ciclo de dibujo
	//Eliminamos venta y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}

