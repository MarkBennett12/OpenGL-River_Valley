/*
 * TerrainGenerator.cpp
 *
 *  Created on: 30 Nov 2013
 *      Author: mark
 */

#include "TerrainGenerator.h"

namespace Generators
{

TerrainGenerator::TerrainGenerator()
{
	// TODO Auto-generated constructor stub

}

TerrainGenerator::~TerrainGenerator()
{
	// TODO Auto-generated destructor stub
}

int TerrainGenerator::GetSize()
{
	return terrainSize;
}


// Initialise a terrain tile
// Generate landscape using mid-point displacement
/*
void generate(GLfloat x1, GLfloat z1, GLfloat x2, GLfloat z2, GLfloat x3, GLfloat z3, GLfloat x4, GLfloat z4, GLfloat height, int iterations, vector<GLfloat> &vertices)
{
	GLfloat newCentreHeight = displace(height, height, height, height, iterations);

	// Quad 1
	// Vertex 1
	vertices.push_back(x1); // x
	vertices.push_back(height); // y
	vertices.push_back(z1); // z

	// Vertex 2
	vertices.push_back((x1 + x2) / 2); // x
	vertices.push_back(height); // y
	vertices.push_back(z2); // z

	// Vertex 3
	vertices.push_back((x1 + x3) / 2); // x
	vertices.push_back(newCentreHeight); // y
	vertices.push_back((z2 + z3) / 2); // z

	// Vertex 5
	vertices.push_back(x4); // x
	vertices.push_back(height); // y
	vertices.push_back((z2 + z4) / 2); // z

	numVertices += 4;

	// Quad 2
	// Vertex 1
	vertices.push_back((x1 + x2) / 2); // x
	vertices.push_back(height); // y
	vertices.push_back(z1); // z

	// Vertex 2
	vertices.push_back(x2); // x
	vertices.push_back(height); // y
	vertices.push_back(z2); // z

	// Vertex 3
	vertices.push_back(x3); // x
	vertices.push_back(height); // y
	vertices.push_back((z2 + z3) / 2); // z

	// Vertex 5
	vertices.push_back((x2 + x4) / 2); // x
	vertices.push_back(newCentreHeight); // y
	vertices.push_back((z2 + z4) / 2); // z

	numVertices += 4;

	// Quad 3
	// Vertex 1
	vertices.push_back((x1 + x2) / 2); // x
	vertices.push_back(newCentreHeight); // y
	vertices.push_back((z1 + z3) / 2); // z

	// Vertex 2
	vertices.push_back(x2); // x
	vertices.push_back(height); // y
	vertices.push_back((z2 + z3) / 2); // z

	// Vertex 3
	vertices.push_back(x3); // x
	vertices.push_back(height); // y
	vertices.push_back(z3); // z

	// Vertex 5
	vertices.push_back((x3 + x4) / 2); // x
	vertices.push_back(height); // y
	vertices.push_back(z4); // z

	numVertices += 4;

	// Quad 4
	// Vertex 1
	vertices.push_back(x1); // x
	vertices.push_back(height); // y
	vertices.push_back((z1 + z3) / 2); // z

	// Vertex 2
	vertices.push_back((x1 + x2) / 2); // x
	vertices.push_back(newCentreHeight); // y
	vertices.push_back((z2 + z3) / 2); // z

	// Vertex 3
	vertices.push_back((x1 + x3) / 2); // x
	vertices.push_back(height); // y
	vertices.push_back(z3); // z

	// Vertex 5
	vertices.push_back((x1 + x4) / 2); // x
	vertices.push_back(height); // y
	vertices.push_back(z4); // z

	numVertices += 4;

	if(iterations > 1)
	{
		generate(x1, z1, (x1 + x2) / 2, z2, (x1 + x2) / 2, (z2 + z3) / 2, x4, (z2 + z4) / 2, height, iterations - 1, vertices);
		generate((x1 + x2) / 2, z1, x2, z2, x3, (z2 + z3) / 2, (x2 + x4) / 2, (z2 + z4) / 2, height, iterations - 1, vertices);
		generate((x1 + x2) / 2, (z1 + z3) / 2, x2, (z2 + z3) / 2, x3, z3, (x3 + x4) / 2, z4, height, iterations - 1, vertices);
		generate(x1, (z1 + z3) / 2, (x1 + x2) / 2, (z2 + z3) / 2, (x1 + x3) / 2, z3, (x1 + x4) / 2, z4, height, iterations - 1, vertices);
	}
}
*/

} /* namespace Generators */
