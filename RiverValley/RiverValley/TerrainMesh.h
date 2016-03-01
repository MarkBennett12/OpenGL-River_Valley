/*
 * Mesh.h
 *
 *  Created on: 30 Nov 2013
 *      Author: mark
 */
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

#ifndef MESH_H_
#define MESH_H_

namespace Geometry
{

class TerrainMesh
{
private:
	std::vector<GLfloat> vertices;
	std::vector<GLubyte> indices;
	const int vertexSize;

	int GetVertexIndex(int verticesIndex);
	int GetVertexIndex(GLfloat x, GLfloat y, GLfloat z);

public:
	TerrainMesh();
	TerrainMesh(int size);
	virtual ~TerrainMesh();
	int GetVertexSize();
	GLfloat* GetVertices();
	GLubyte* GetIndices();
	int GetVertexCount();
	int GetIndexCount();
	void AddVertex(GLfloat x, GLfloat y, GLfloat z);
	void AddQuad(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4);
	void SetHeightAt(const GLfloat x, const GLfloat z, GLfloat newY);
	GLfloat GetHeightAt(const GLfloat x, const GLfloat z);
	void PrintMesh();
};

} /* namespace Display */
#endif /* MESH_H_ */
