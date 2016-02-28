/*
 * Mesh.cpp
 *
 *  Created on: 30 Nov 2013
 *      Author: mark
 */
#include <iostream>
#include "Mesh.h"

namespace Display
{

Mesh::Mesh():
	vertexSize(3)
{
	// TODO Auto-generated constructor stub
}

Mesh::Mesh(int size):
	vertexSize(3)
{
	// TODO Auto-generated constructor stub
	vertices.reserve(size * vertexSize);
}

Mesh::~Mesh()
{
	// TODO Auto-generated destructor stub
}

int Mesh::GetVertexIndex(int verticesIndex)
{
	if(verticesIndex > 0)
		return verticesIndex / vertexSize;
	else
		return 0;
}

int Mesh::GetVertexSize()
{
	return vertexSize;
}

int Mesh::GetVertexCount()
{
	return vertices.size();
}

int Mesh::GetIndexCount()
{
	return indices.size();
}

GLfloat* Mesh::GetVertices()
{
	return vertices.data();
}

GLubyte* Mesh::GetIndices()
{
	return indices.data();
}

int Mesh::FindExistingVertex(GLfloat x, GLfloat y, GLfloat z)
{
	for(std::vector<GLfloat>::iterator i = vertices.begin(); i != vertices.end(); i+=vertexSize)
		if(i + 2 != vertices.end() && *i == x && *(i + 1) == y && *(i + 2) == z)
			return GetVertexIndex(std::distance(vertices.begin(), i));
	return -1;
}

void Mesh::AddVertex(GLfloat x, GLfloat y, GLfloat z)
{
	//std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
	int vertexIndex = FindExistingVertex(x, y, z);
	//std::cout << "vertex index = " << vertexIndex << std::endl << std::endl;
	if(vertexIndex != -1)
		indices.push_back(vertexIndex);
	else
	{
		indices.push_back(GetVertexIndex(vertices.size()));

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
	}
	//std::cout << "vertices size = " << vertices.size() << std::endl;
}

void Mesh::AddQuad(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4)
{
	// Triangle 1
	AddVertex(x1, y1, z1);
	AddVertex(x2, y2, z2);
	AddVertex(x3, y3, z3);

	// Triangle 2
	AddVertex(x1, y1, z1);
	AddVertex(x3, y3, z3);
	AddVertex(x4, y4, z4);
}

void Mesh::SetYVal(const GLfloat x, const GLfloat z, GLfloat newY)
{
		for(std::vector<GLfloat>::iterator i = vertices.begin(); i != vertices.end(); i+=vertexSize)
		if(i + 2 != vertices.end() && *i == x && *(i + 2) == z)
			*(i + 1) = newY;
}

GLfloat Mesh::GetYVal(const GLfloat x, const GLfloat z)
{
	for(std::vector<GLfloat>::iterator i = vertices.begin(); i != vertices.end(); i+=vertexSize)
	if(i + 2 != vertices.end() && *i == x && *(i + 2) == z)
		return *(i + 1);
	return 0.0;
}

void Mesh::PrintMesh()
{
	/*
	std::cout << "vertices size = " << vertices.size() << std::endl;
	for(std::vector<GLfloat>::iterator i = vertices.begin(); i != vertices.end(); i+=vertexSize)
		std::cout << "x = " << *i << ", z = " << *(i + 2) << " : ";
	std::cout << std::endl;
	*/

	std::cout << "indices size = " << indices.size() << std::endl;
	for(std::vector<GLubyte>::iterator i = indices.begin(); i != indices.end(); i++)
	{
		GLfloat X = vertices[(*i) * vertexSize];
		GLfloat Z = vertices[(*i) * vertexSize + 2];
		std::cout << "index[" << std::distance(indices.begin(), i) << "] = " << X << ", " << Z << std::endl;
	}
}

} /* namespace Display */
