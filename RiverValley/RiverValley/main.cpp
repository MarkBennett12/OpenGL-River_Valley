/*
 * main.cpp
 *
 *  Created on: 6 May 2013
 *      Author: mark
*/

#include <iostream>
#include <windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Mesh.h"
#include "DiamondSquare.h"

using namespace std;
using namespace Display;
using namespace Generators;

int windowPosX = 100;
int windowPosY = 100;
int windowWidth = 800;
int windowHeight = 600;

GLfloat viewTargetX;
GLfloat viewTargetY;
GLfloat viewTargetZ;

GLfloat cameraX;
GLfloat cameraY;
GLfloat cameraZ;

int terrainSize = 8;
Mesh terrain(terrainSize * terrainSize);
Parameters terrainParams;
DiamondSquare generator(&terrain, &terrainParams, terrainSize, 4);

// Initialise OpenGL
void init(const int posX, const int posY, const int width, const int height)
{
	viewTargetX = (GLfloat)generator.GetSize() / 2;
	viewTargetY = 0.0;
	viewTargetZ = (GLfloat)-(generator.GetSize() / 2);

	cameraX = (GLfloat)generator.GetSize() / 2;
	cameraY = (GLfloat)generator.GetSize() / 2;
	cameraZ = (GLfloat)generator.GetSize() * 2;

	//Simple buffer
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(posX, posY);
	glutInitWindowSize(width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutCreateWindow("Generative Landscapes");
}

GLfloat displace(GLfloat y1, GLfloat y2, GLfloat y3, GLfloat y4, int iteration)
{
	GLfloat displacement = 1.0;
	GLfloat average = 0.0;

	return displacement;
}

void reshape(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Drawing function
void draw(void)
{
	//Background colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0, (GLfloat)(generator.GetSize() * 3));
	gluLookAt(cameraX, cameraY, cameraZ, viewTargetX, viewTargetY, viewTargetZ, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);

	// Draw in wireframe
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	// Draw this red sphere so I know where we're looking
	//glColor3f(1.0, 0.0, 0.0);
	//glutSolidSphere(1, 20, 20);

	glColor3f(0.0, 1.0, 0.0);

	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(terrain.GetVertexSize(), GL_FLOAT, 0, terrain.GetVertices());

	// draw terrain
	//glDrawArrays(GL_QUADS, 0, terrain.GetVertexCount());
	glDrawElements(GL_TRIANGLES, terrain.GetIndexCount(), GL_UNSIGNED_BYTE, terrain.GetIndices());

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);

	//Draw order
	glutSwapBuffers();
	glutPostRedisplay();
	glFlush();
}

//Main program
int main(int argc, char **argv)
{
	terrainParams.baseHeight = 0.0;
	terrainParams.roughness = 1.0;
	terrainParams.roughnessDecrement = 0.1;

	glutInit(&argc, argv);
	init(windowPosX, windowPosY, windowWidth, windowHeight);

	generator.Init();
	generator.Generate();
	//terrain.SetYVal((GLfloat)generator.GetSize() / 2, (GLfloat)generator.GetSize() / 2, 1);
	//terrain.PrintMesh();

	//Call to set the drawing and reshape functions
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}
