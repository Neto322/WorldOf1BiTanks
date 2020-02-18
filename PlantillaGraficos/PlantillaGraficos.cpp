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

float posXtanque1 = -0.8f, posYtanque1 = -0.8f, rotXcanon1 = 0.0f, posXtanque2 = 0.8f, posYtanque2 = 0.8f, rotXcanon2 = 0.0f;

const float* axes;

const float* axes2;

int count;

int count2;




float posXbala1 = 2.0f, posYbala1 = 2.0f, posXbala2 = 2.0f, posYbala2 = 2.0f;

float hitsbala1 = 0.0f, hitsbala2 = 0.0f;



float velocidadbalaX1 = 0.0f, velocidadbalaY1 = 0.0f, velocidadbalaX2 = 0.0f, velocidadbalaY2 = 0.0f;

double color1, color2, color3, color4, color5, color6;


float ultimoangulo = 0.0f;

float ultimoangulo2 = 0.0f;

bool readytofire = true;

bool readytofire2 = true;

bool death1 = false;

bool death2 = false;

//Declarar ventana
GLFWwindow* window;

int grid[10][10];

void generarGridAleatorio() {
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			bool crearPared = (rand() % 6) == 0;
			grid[i][j] = crearPared ? 3 : 0;
		}
	}
}

bool puedeMoverX(float offsetX, float PosobjetoY, float PosobjetoX, float tolerancia) {
	float auxPosY = PosobjetoY + 1;
	float auxPosX = PosobjetoX + 1;

	float auxPosicionActualGridY = auxPosY * 5.0f;
	float auxPosicionActualGridX = (auxPosX + offsetX) * 5.0f;

	int posicionActualGridYTruncado = trunc(auxPosicionActualGridY);
	int posicionActualGridYRedondeado = round(auxPosicionActualGridY);
	int posicionActualGridX = trunc(auxPosicionActualGridX);

	float margenTolerancia = tolerancia;
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

bool puedeMoverY(float offsetY, float PosobjetoY, float PosobjetoX, float tolerancia) {
	float auxPosY = PosobjetoY + 1;
	float auxPosX = PosobjetoX + 1;

	float auxPosicionActualGridY = (auxPosY + offsetY) * 5.0f;
	float auxPosicionActualGridX = auxPosX * 5.0f;

	int posicionActualGridY = trunc(auxPosicionActualGridY);
	int posicionActualGridXTruncado = trunc(auxPosicionActualGridX);
	int posicionActualGridXRedondeado = round(auxPosicionActualGridX);

	float margenTolerancia = tolerancia;
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

float scala1 = 0.07f, scala2 = 0.07f;


void actualizar()
{
	tiempoactual = glfwGetTime();

	double tiempoDiferencial = tiempoactual - tiempoanterior;

	int count;


	if (

		posXbala1 + 0.001f >= posXbala2 - 0.05f &&

		posXbala1 - 0.001f <= posXbala2 + 0.05f &&

		posYbala1 + 0.001f >= posYbala2 - 0.05f &&

		posYbala1 - 0.001f <= posYbala2 + 0.05f

		)
	{
		posXbala1 = 2.0f;
		posXbala1 = 2.0f;
		posYbala2 = 2.0f;
		posYbala2 = 2.0f;

		readytofire = true;
		readytofire2 = true;


	}


	if (

		posXbala1 + 0.001f >= posXtanque2 - 0.05f &&

		posXbala1 - 0.001f <= posXtanque2 + 0.05f &&

		posYbala1 + 0.001f >= posYtanque2 - 0.05f &&

		posYbala1 - 0.001f <= posYtanque2 + 0.05f

		)
	{
		death2 = true;

	}

	if (

		posXbala2 + 0.001f >= posXtanque1 - 0.05f &&

		posXbala2 - 0.001f <= posXtanque1 + 0.05f &&

		posYbala2 + 0.001f >= posYtanque1 - 0.05f &&

		posYbala2 - 0.001f <= posYtanque1 + 0.05f

		)
	{
		death1 = true;

	}

	if (death2 == true)
	{
		rotXcanon2 += 4500 * tiempoDiferencial;
		scala2 -= -0.01 * tiempoDiferencial;

	}

	if (death1 == true)
	{
		rotXcanon1 += 4500 * tiempoDiferencial;
		scala1 -= -0.01 * tiempoDiferencial * .35;

	}

	std::cout << cos((ultimoangulo + 90) * 3.141592 / 180.0f) << "    TURU TURU TURU TURU       " << sin((ultimoangulo + 90) * 3.141592 / 180.0f) << std::endl;

	if (int present = glfwJoystickPresent(GLFW_JOYSTICK_1))
	{


		axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
		if (axes[0] > 0.3)
		{
			if (puedeMoverX(0.05f, posYtanque1, posXtanque1, 0.14f)) {
				posXtanque1 += 0.5 * tiempoDiferencial;
			}
		}

		if (axes[0] < -0.5)
		{
			if (puedeMoverX(-0.05f, posYtanque1, posXtanque1, 0.14f)) {
				posXtanque1 -= 0.5 * tiempoDiferencial;
			}
		}

		if (axes[1] < 0.5)
		{
			if (puedeMoverY(0.05f, posYtanque1, posXtanque1, 0.14f)) {
				posYtanque1 += 0.5 * tiempoDiferencial;
			}
		}

		if (axes[1] > -0.5)
		{
			if (puedeMoverY(-0.05f, posYtanque1, posXtanque1, 0.14f)) {
				posYtanque1 -= 0.5 * tiempoDiferencial;
			}
		}

		if (axes[2] > 0.5)
		{
			rotXcanon1 += axes[2] * -360 * tiempoDiferencial * .5;
		}

		if (axes[2] < -0.5)
		{
			rotXcanon1 += axes[2] * -360 * tiempoDiferencial * .5;
		}

		if (rotXcanon1 < -360)
		{
			rotXcanon1 = 0;
		}
		if (rotXcanon1 > 360)
		{
			rotXcanon1 = 0;
		}

		int buttoncount;

		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttoncount);
		if (GLFW_PRESS == buttons[0])
		{
			if (readytofire == true)
			{
				posXbala1 = posXtanque1;
				posYbala1 = posYtanque1;
				hitsbala1 = 280;
				velocidadbalaX1 = 1;
				velocidadbalaY1 = 1;
				readytofire = false;
			}
			ultimoangulo = rotXcanon1;

		}
		if (readytofire == false)
		{


			if (!puedeMoverX(0.001f, posYbala1, posXbala1, 0.0f))
			{
				velocidadbalaX1 = 1;
				hitsbala1--;
			}

			if (!puedeMoverX(-0.001f, posYbala1, posXbala1, 0.0f))
			{
				velocidadbalaX1 = -1;
				hitsbala1--;

			}

			if (!puedeMoverY(0.001f, posYbala1, posXbala1, 0.0f))
			{
				velocidadbalaY1 = 1;
				hitsbala1--;

			}
			if (!puedeMoverY(-0.001f, posYbala1, posXbala1, 0.0f))
			{
				velocidadbalaY1 = -1;
				hitsbala1--;

			}

			posXbala1 += velocidadbalaX1 * cos((ultimoangulo + 90) * 3.141592 / 180.0f) * tiempoDiferencial;

			posYbala1 += velocidadbalaY1 * sin((ultimoangulo + 90) * 3.141592 / 180.0f) * tiempoDiferencial;

			if (hitsbala1 <= 0)
			{
				posXbala1 = 2.0f;
				posXbala1 = 2.0f;
				readytofire = true;
			}
		}



	}


	if (int present = glfwJoystickPresent(GLFW_JOYSTICK_2))
	{


		axes2 = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &count);
		if (axes2[0] > 0.3)
		{
			if (puedeMoverX(0.05f, posYtanque2, posXtanque2, 0.14f)) {
				posXtanque2 += 0.5 * tiempoDiferencial;
			}
		}

		if (axes2[0] < -0.5)
		{
			if (puedeMoverX(-0.05f, posYtanque2, posXtanque2, 0.14f)) {
				posXtanque2 -= 0.5 * tiempoDiferencial;
			}
		}

		if (axes2[1] < 0.5)
		{
			if (puedeMoverY(0.05f, posYtanque2, posXtanque2, 0.14f)) {
				posYtanque2 += 0.5 * tiempoDiferencial;
			}
		}

		if (axes2[1] > -0.5)
		{
			if (puedeMoverY(-0.05f, posYtanque2, posXtanque2, 0.14f)) {
				posYtanque2 -= 0.5 * tiempoDiferencial;
			}
		}

		if (axes2[2] > 0.5)
		{
			rotXcanon2 += axes2[2] * -360 * tiempoDiferencial * .5;
		}

		if (axes2[2] < -0.5)
		{
			rotXcanon2 += axes2[2] * -360 * tiempoDiferencial * .5;
		}

		if (rotXcanon2 < -360)
		{
			rotXcanon2 = 0;
		}
		if (rotXcanon2 > 360)
		{
			rotXcanon2 = 0;
		}

		int buttoncount;

		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &buttoncount);
		if (GLFW_PRESS == buttons[0])
		{
			if (readytofire2 == true)
			{
				posXbala2 = posXtanque2;
				posYbala2 = posYtanque2;
				hitsbala2 = 280;
				velocidadbalaX2 = 1;
				velocidadbalaY2 = 1;
				readytofire2 = false;
			}
			ultimoangulo2 = rotXcanon2;

		}
		if (readytofire2 == false)
		{


			if (!puedeMoverX(0.001f, posYbala2, posXbala2, 0.0f))
			{
				velocidadbalaX2 = 1;
				hitsbala2--;
			}

			if (!puedeMoverX(-0.001f, posYbala2, posXbala2, 0.0f))
			{
				velocidadbalaX2 = -1;
				hitsbala2--;

			}

			if (!puedeMoverY(0.001f, posYbala2, posXbala2, 0.0f))
			{
				velocidadbalaY2 = 1;
				hitsbala2--;

			}
			if (!puedeMoverY(-0.001f, posYbala2, posXbala2, 0.0f))
			{
				velocidadbalaY2 = -1;
				hitsbala2--;

			}

			posXbala2 += velocidadbalaX2 * cos((ultimoangulo2 + 90) * 3.141592 / 180.0f) * tiempoDiferencial;

			posYbala2 += velocidadbalaY2 * sin((ultimoangulo2 + 90) * 3.141592 / 180.0f) * tiempoDiferencial;

			if (hitsbala2 <= 0)
			{
				posXbala2 = 2.0f;
				posXbala2 = 2.0f;
				readytofire2 = true;
			}
		}



	}


	int estadoR = glfwGetKey(window, GLFW_KEY_R);

	if (estadoR == GLFW_PRESS) {
		generarGridAleatorio();
		posYtanque1 = -0.8f;
		posXtanque1 = -0.8f;

		posYtanque2 = 0.8f;
		posXtanque2 = 0.8f;

		death1 = false;
		death2 = false;
		rotXcanon1 = 0.0f;
		rotXcanon2 = 0.0f;

		posXbala1 = 2.0f;
		posXbala2 = 2.0f;

		readytofire = true;
		readytofire2 = true;
	}

	tiempoanterior = tiempoactual;
}

void canon()
{
	//Cañon
	glPushMatrix();
	glTranslatef(posXtanque1, posYtanque1, 0.0f);
	glRotatef(rotXcanon1, 0.0f, 0.0f, 1.0f);
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

void canon2()
{
	//Cañon
	glPushMatrix();
	glTranslatef(posXtanque2, posYtanque2, 0.0f);
	glRotatef(rotXcanon2, 0.0f, 0.0f, 1.0f);
	glScalef(0.1f, 0.1f, 0.0f);

	glBegin(GL_POLYGON);

	glColor3f(0.27f, 0.66f, 1.00f);//White

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

	glTranslatef(posXtanque1, posYtanque1, 0.0f);
	glRotatef(rotXcanon1, 0.0f, 0.0f, 1.0f);
	glScalef(scala1, scala1, 0.0f);

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

void tanque2()
{
	glPushMatrix();

	glTranslatef(posXtanque2, posYtanque2, 0.0f);
	glRotatef(rotXcanon2, 0.0f, 0.0f, 1.0f);
	glScalef(scala1, scala1, 0.0f);

	glBegin(GL_POLYGON);

	glColor3f(0.22f, 0.30f, 1.00f);//Blue

	glVertex3f(0.3f, 0.5f, 0.0f);
	glVertex3f(0.6f, 0.5f, 0.0f);
	glVertex3f(0.6f, -0.6f, 0.0f);
	glVertex3f(0.3f, -0.6f, 0.0f);


	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.22f, 0.30f, 1.00f);//Orange

	glVertex3f(0.4f, -0.6f, 0.0f);
	glVertex3f(0.6f, -0.6f, 0.0f);
	glVertex3f(0.6f, -0.7f, 0.0f);
	glVertex3f(0.4f, -0.7f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.22f, 0.30f, 1.00f);//Orange

	glVertex3f(-0.6f, 0.4f, 0.0f);
	glVertex3f(0.2f, 0.4f, 0.0f);
	glVertex3f(0.4f, -0.5f, 0.0f);
	glVertex3f(-0.6f, -0.5f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.22f, 0.30f, 1.00f);//Orange

	glVertex3f(-0.6f, -0.6f, 0.0f);
	glVertex3f(-0.4f, -0.6f, 0.0f);
	glVertex3f(-0.4f, -0.7f, 0.0f);
	glVertex3f(-0.6f, -0.7f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.22f, 0.30f, 1.00f);//Orange

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

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(-0.6f, 0.5f, 0.0f);
	glVertex3f(-0.4f, 0.5f, 0.0f);
	glVertex3f(-0.4f, 0.4f, 0.0f);
	glVertex3f(-0.6f, 0.4f, 0.0f);


	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(-0.2f, 0.5f, 0.0f);
	glVertex3f(-0.1f, 0.5f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.2f, 0.4f, 0.0f);


	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.1f, 0.5f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(0.4f, 0.4f, 0.0f);
	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(0.1f, 0.1f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(0.4f, -0.6f, 0.0f);
	glVertex3f(0.2f, -0.6f, 0.0f);
	glVertex3f(0.2f, 0.1f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(0.1f, -0.5f, 0.0f);
	glVertex3f(0.2f, -0.5f, 0.0f);
	glVertex3f(0.2f, -0.6f, 0.0f);
	glVertex3f(0.1f, -0.6f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(0.4f, 0.5f, 0.0f);
	glVertex3f(0.6f, 0.5f, 0.0f);
	glVertex3f(0.6f, 0.4f, 0.0f);
	glVertex3f(0.4f, 0.4f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(0.4f, 0.3f, 0.0f);
	glVertex3f(0.6f, 0.3f, 0.0f);
	glVertex3f(0.6f, 0.2f, 0.0f);
	glVertex3f(0.4f, 0.2f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(0.6f, 0.1f, 0.0f);
	glVertex3f(0.6f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(0.4f, -0.1f, 0.0f);
	glVertex3f(0.6f, -0.1f, 0.0f);
	glVertex3f(0.6f, -0.2f, 0.0f);
	glVertex3f(0.4f, -0.2f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(0.4f, -0.3f, 0.0f);
	glVertex3f(0.6f, -0.3f, 0.0f);
	glVertex3f(0.6f, -0.4f, 0.0f);
	glVertex3f(0.4f, -0.4f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(0.4f, -0.5f, 0.0f);
	glVertex3f(0.6f, -0.5f, 0.0f);
	glVertex3f(0.6f, -0.6f, 0.0f);
	glVertex3f(0.4f, -0.6f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(0.1f, 0.1f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(-0.1f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, -0.3f, 0.0f);
	glVertex3f(0.0f, -0.3f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(-0.7f, 0.3f, 0.0f);
	glVertex3f(-0.5f, 0.3f, 0.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.7f, 0.2f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(-0.7f, 0.1f, 0.0f);
	glVertex3f(-0.5f, 0.1f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(-0.7f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(-0.7f, -0.1f, 0.0f);
	glVertex3f(-0.5f, -0.1f, 0.0f);
	glVertex3f(-0.5f, -0.2f, 0.0f);
	glVertex3f(-0.7f, -0.2f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

	glVertex3f(-0.7f, -0.3f, 0.0f);
	glVertex3f(-0.5f, -0.3f, 0.0f);
	glVertex3f(-0.5f, -0.4f, 0.0f);
	glVertex3f(-0.7f, -0.4f, 0.0f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(0.33f, 0.09f, 1.00f);

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

				glColor3f(0.5f, 0.0f, 0.0f);//Guinda

				glVertex3f(-1.0f, -1.0f, 0.0f);
				glVertex3f(-1.0f, -0.8f, 0.0f);
				glVertex3f(-0.8f, -0.8f, 0.0f);
				glVertex3f(-0.8f, -1.0f, 0.0f);

				glEnd();

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-1.0f, -0.84f, 0.0f);
				glVertex3f(-0.8f, -0.84f, 0.0f);
				glVertex3f(-0.8f, -0.85f, 0.0f);
				glVertex3f(-1.0f, -0.85f, 0.0f);

				glEnd();

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-1.0f, -0.99f, 0.0f);
				glVertex3f(-0.8f, -0.99f, 0.0f);
				glVertex3f(-0.8f, -1.0f, 0.0f);
				glVertex3f(-1.0f, -1.0f, 0.0f);

				glEnd();

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-1.0f, -0.94f, 0.0f);
				glVertex3f(-0.8f, -0.94f, 0.0f);
				glVertex3f(-0.8f, -0.95f, 0.0f);
				glVertex3f(-1.0f, -0.95f, 0.0f);

				glEnd();

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-1.0f, -0.89f, 0.0f);
				glVertex3f(-0.8f, -0.89f, 0.0f);
				glVertex3f(-0.8f, -0.9f, 0.0f);
				glVertex3f(-1.0f, -0.9f, 0.0f);

				glEnd();

				//Verticales

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-0.95f, -0.8f, 0.0f);
				glVertex3f(-0.94f, -0.8f, 0.0f);
				glVertex3f(-0.94f, -0.84f, 0.0f);
				glVertex3f(-0.95f, -0.84f, 0.0f);

				glEnd();

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-0.85f, -0.8f, 0.0f);
				glVertex3f(-0.84f, -0.8f, 0.0f);
				glVertex3f(-0.84f, -0.84f, 0.0f);
				glVertex3f(-0.85f, -0.84f, 0.0f);

				glEnd();

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-1.0f, -0.85f, 0.0f);
				glVertex3f(-0.99f, -0.85f, 0.0f);
				glVertex3f(-0.99f, -0.89f, 0.0f);
				glVertex3f(-1.0f, -0.89f, 0.0f);

				glEnd();

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-0.9f, -0.85f, 0.0f);
				glVertex3f(-0.89f, -0.85f, 0.0f);
				glVertex3f(-0.89f, -0.89f, 0.0f);
				glVertex3f(-0.9f, -0.89f, 0.0f);

				glEnd();

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-0.95f, -0.9f, 0.0f);
				glVertex3f(-0.94f, -0.9f, 0.0f);
				glVertex3f(-0.94f, -0.94f, 0.0f);
				glVertex3f(-0.95f, -0.94f, 0.0f);

				glEnd();

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-0.85f, -0.9f, 0.0f);
				glVertex3f(-0.84f, -0.9f, 0.0f);
				glVertex3f(-0.84f, -0.94f, 0.0f);
				glVertex3f(-0.85f, -0.94f, 0.0f);

				glEnd();

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-1.0f, -0.95f, 0.0f);
				glVertex3f(-0.99f, -0.95f, 0.0f);
				glVertex3f(-0.99f, -0.99f, 0.0f);
				glVertex3f(-1.0f, -0.99f, 0.0f);

				glEnd();

				glBegin(GL_POLYGON);

				glColor3f(0.6f, 0.6f, 0.6f);//Gris

				glVertex3f(-0.9f, -0.95f, 0.0f);
				glVertex3f(-0.89f, -0.95f, 0.0f);
				glVertex3f(-0.89f, -0.99f, 0.0f);
				glVertex3f(-0.9f, -0.99f, 0.0f);

				glEnd();

				//Cuadro_1
				glBegin(GL_POLYGON);

				glColor3f(0.7f, 0.4f, 0.0f);//Cafe

				glVertex3f(-1.0f, -0.81f, 0.0f);
				glVertex3f(-0.95f, -0.81f, 0.0f);
				glVertex3f(-0.95f, -0.84f, 0.0f);
				glVertex3f(-1.0f, -0.84f, 0.0f);

				glEnd();

				//Cuadro_2
				glBegin(GL_POLYGON);

				glColor3f(0.7f, 0.4f, 0.0f);//Cafe

				glVertex3f(-0.93f, -0.81f, 0.0f);
				glVertex3f(-0.85f, -0.81f, 0.0f);
				glVertex3f(-0.85f, -0.84f, 0.0f);
				glVertex3f(-0.93f, -0.84f, 0.0f);

				glEnd();

				//Cuadro_3
				glBegin(GL_POLYGON);

				glColor3f(0.7f, 0.4f, 0.0f);//Cafe

				glVertex3f(-0.83f, -0.81f, 0.0f);
				glVertex3f(-0.80f, -0.81f, 0.0f);
				glVertex3f(-0.80f, -0.84f, 0.0f);
				glVertex3f(-0.83f, -0.84f, 0.0f);

				glEnd();

				//Cuadro_4
				glBegin(GL_POLYGON);

				glColor3f(0.7f, 0.4f, 0.0f);//Cafe

				glVertex3f(-0.98f, -0.86f, 0.0f);
				glVertex3f(-0.90f, -0.86f, 0.0f);
				glVertex3f(-0.90f, -0.89f, 0.0f);
				glVertex3f(-0.98f, -0.89f, 0.0f);

				glEnd();

				//Cuadro_5
				glBegin(GL_POLYGON);

				glColor3f(0.7f, 0.4f, 0.0f);//Cafe

				glVertex3f(-0.8f, -0.86f, 0.0f);
				glVertex3f(-0.88f, -0.86f, 0.0f);
				glVertex3f(-0.88f, -0.89f, 0.0f);
				glVertex3f(-0.8f, -0.89f, 0.0f);

				glEnd();

				//Cuadro_6
				glBegin(GL_POLYGON);

				glColor3f(0.7f, 0.4f, 0.0f);//Cafe

				glVertex3f(-1.0f, -0.91f, 0.0f);
				glVertex3f(-0.95f, -0.91f, 0.0f);
				glVertex3f(-0.95f, -0.94f, 0.0f);
				glVertex3f(-1.0f, -0.94f, 0.0f);

				glEnd();

				//Cuadro_7
				glBegin(GL_POLYGON);

				glColor3f(0.7f, 0.4f, 0.0f);//Cafe

				glVertex3f(-0.93f, -0.91f, 0.0f);
				glVertex3f(-0.85f, -0.91f, 0.0f);
				glVertex3f(-0.85f, -0.94f, 0.0f);
				glVertex3f(-0.93f, -0.94f, 0.0f);

				glEnd();

				//Cuadro_8
				glBegin(GL_POLYGON);

				glColor3f(0.7f, 0.4f, 0.0f);//Cafe

				glVertex3f(-0.83f, -0.91f, 0.0f);
				glVertex3f(-0.80f, -0.91f, 0.0f);
				glVertex3f(-0.80f, -0.94f, 0.0f);
				glVertex3f(-0.83f, -0.94f, 0.0f);

				glEnd();

				//Cuadro_9
				glBegin(GL_POLYGON);

				glColor3f(0.7f, 0.4f, 0.0f);//Cafe

				glVertex3f(-0.98f, -0.96f, 0.0f);
				glVertex3f(-0.9f, -0.96f, 0.0f);
				glVertex3f(-0.9f, -0.99f, 0.0f);
				glVertex3f(-0.98f, -0.99f, 0.0f);

				glEnd();

				//Cuadro_10
				glBegin(GL_POLYGON);

				glColor3f(0.7f, 0.4f, 0.0f);//Cafe

				glVertex3f(-0.8f, -0.96f, 0.0f);
				glVertex3f(-0.88f, -0.96f, 0.0f);
				glVertex3f(-0.88f, -0.99f, 0.0f);
				glVertex3f(-0.8f, -0.99f, 0.0f);

				glEnd();

				glPopMatrix();
			}
		}
	}
}

void crearbalas()
{
	color1 = rand() % 100;

	color2 = rand() % 100;

	color3 = rand() % 100;

	color1 = color1 / 100;

	color2 = color2 / 100;

	color3 = color3 / 100;

	glPushMatrix();
	glTranslatef(posXbala1, posYbala1, 0.0f);

	glScalef(0.1f, 0.1f, 0.0f);
	glBegin(GL_POLYGON);

	glColor3f(color1, color2, color3);

	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -0.8f, 0.0f);
	glVertex3f(-0.8f, -0.8f, 0.0f);
	glVertex3f(-0.8f, -1.0f, 0.0f);

	glEnd();
	glPopMatrix();
}
void crearbalas2()
{
	color4 = rand() % 100;

	color5 = rand() % 100;

	color6 = rand() % 100;

	color4 = color4 / 100;

	color5 = color5 / 100;

	color6 = color6 / 100;

	glPushMatrix();
	glTranslatef(posXbala2, posYbala2, 0.0f);

	glScalef(0.1f, 0.1f, 0.0f);
	glBegin(GL_POLYGON);

	glColor3f(color4, color5, color6);

	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -0.8f, 0.0f);
	glVertex3f(-0.8f, -0.8f, 0.0f);
	glVertex3f(-0.8f, -1.0f, 0.0f);

	glEnd();
	glPopMatrix();
}


void dibujar()
{
	//generarGridAleatorio();
	dibujarMapa();

	canon();
	tanque();
	crearbalas();
	canon2();
	tanque2();
	crearbalas2();



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
	window = glfwCreateWindow(1000, 1000, "Ventana", NULL, NULL);

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
		glClearColor(0, 0.0, 0, 1);
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

