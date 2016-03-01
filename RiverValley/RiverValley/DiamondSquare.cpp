/*
 * DiamondSquare.cpp
 *
 * Implements the diamond square algorithm for procedural terrain generation.
 *  Created on: 30 Nov 2013
 *      Author: Mark Bennett
 */
#include <iostream>
#include "DiamondSquare.h"

namespace Generators
{

/*
Constructs the DiamondSquare object and provied the mesh and parameters for the algorithm

Display::TerrainMesh* mesh : The mesh to be built
Parameters* params : Parameters to control the algorithm
int size : The size of each side of the mesh
*/
DiamondSquare::DiamondSquare(Geometry::TerrainMesh* mesh, Parameters* params, int size):
		normalDistribution(0.0, 1.0),
		generator(rng, normalDistribution)
{
	// TODO Auto-generated constructor stub
	terrainSize = size;
	this->params = params;
	this->mesh = mesh;
}

DiamondSquare::~DiamondSquare()
{
	// TODO Auto-generated destructor stub
}

/*
Initialise the algorithm by creating the mesh at baseheight and raising the four corners of the mesh by a random amount 
*/
void DiamondSquare::Init()
{
	// Generate the terrain mesh at the set size and at the base height
	for(int i = 0; i < terrainSize; i++)
	{
		for(int j = 0; j < terrainSize; j++)
			mesh->AddQuad((GLfloat)j, params->baseHeight, (GLfloat)i, (GLfloat)j + 1, params->baseHeight, (GLfloat)i, (GLfloat)j + 1, params->baseHeight, (GLfloat)i + 1, (GLfloat)j, params->baseHeight, (GLfloat)i + 1);
	}

	// Lift each corner by a random amount
	// As this is the first step we don't modify the random number generated, hence 1.0 being passed to the Displace method
	mesh->SetHeightAt((GLfloat)0, (GLfloat)0, (GLfloat)fabs(Displace(1.0)));
	mesh->SetHeightAt((GLfloat)terrainSize, (GLfloat)0, (GLfloat)fabs(Displace(1.0)));
	mesh->SetHeightAt((GLfloat)terrainSize, (GLfloat)terrainSize, (GLfloat)fabs(Displace(1.0)));
	mesh->SetHeightAt((GLfloat)0, (GLfloat)terrainSize, (GLfloat)fabs(Displace(1.0)));
}

/*
Generate a random number offset from the base height and modified by the roughness parameter
This is used to control the random amount as the interations proceed
The function uses the Boost library random generator to get a standard distribution
of random numbers

parameter: double modifier - modulate the random number by multiplying it by this value
return: A random number with a standard distribution offset from the base height of modulated by the modifier parameter
*/
double DiamondSquare::Displace(double modifier)
{
	return (generator() + params->baseHeight + 1.0) * modifier;
}

/*
The square step gets the hieght of each corner of the mesh, calculates the average of those heights
and uses that average to add an offset to the random number generated. The random value is used to lift the
centre point of each side of the square

int x : the left corner of the square to process
int z: the 'top' - far corner of the square to process
int size: The size of the square to process
double roughness: scale the amount of random change
*/
void DiamondSquare::SquareStep(int x, int z, int size, double roughness)
{
	int midpoint = size / 2;
	GLfloat averageHeight = 0.0;

	// Get the average height of the endpoints of the left side of the square
	averageHeight = mesh->GetHeightAt((GLfloat)x, (GLfloat)z);
	averageHeight += mesh->GetHeightAt((GLfloat)x + size, (GLfloat)z);
	averageHeight /= 2;
	// Set a new random height to the midpoint of the square side based on the average and roughness parameter
	mesh->SetHeightAt((GLfloat)x, (GLfloat)midpoint, (GLfloat)Displace(roughness) + averageHeight);

	// The same for the top (far) side of the square
	averageHeight = mesh->GetHeightAt((GLfloat)x + size, (GLfloat)z);
	averageHeight += mesh->GetHeightAt((GLfloat)x + size, (GLfloat)z + size);
	averageHeight /= 2;
	mesh->SetHeightAt((GLfloat)x + size, (GLfloat)z + midpoint, (GLfloat)Displace(roughness) + averageHeight);

	// The same for the right side of the square
	averageHeight = mesh->GetHeightAt((GLfloat)x + size, (GLfloat)z + size);
	averageHeight += mesh->GetHeightAt((GLfloat)x, (GLfloat)z + size);
	averageHeight /= 2;
	mesh->SetHeightAt((GLfloat)x + midpoint, (GLfloat)z + size, (GLfloat)Displace(roughness) + averageHeight);

	// The same for the bottom (near) side of the square
	averageHeight = mesh->GetHeightAt((GLfloat)x, (GLfloat)z + size);
	averageHeight += mesh->GetHeightAt((GLfloat)x, (GLfloat)z);
	averageHeight /= 2;
	mesh->SetHeightAt((GLfloat)x, (GLfloat)z + midpoint, (GLfloat)Displace(roughness) + averageHeight);
}

/*
The diamond step takes the midpoint of each side of the square and uses the average height of the points to calculate
a new random height for the centre of the square

int x : the left corner of the square to process
int z: the 'top' - far corner of the square to process
int size: The size of the square to process
double roughness: scale the amount of random change
*/
void DiamondSquare::DiamondStep(int x, int z, int size, double roughness)
{
	int midpoint = size / 2;
	GLfloat averageHeight = 0.0;

	// Get the average hieght of the midpoints of each side of the square
	averageHeight = mesh->GetHeightAt((GLfloat)x, (GLfloat)z);
	averageHeight += mesh->GetHeightAt((GLfloat)x + size, (GLfloat)z);
	averageHeight += mesh->GetHeightAt((GLfloat)x + size, (GLfloat)z + size);
	averageHeight += mesh->GetHeightAt((GLfloat)x, (GLfloat)z + size);
	averageHeight /= 4;

	// Lift the centre point of the square by a random amount based on the average height and the roughness parameter
	mesh->SetHeightAt((GLfloat)midpoint, (GLfloat)midpoint, (GLfloat)Displace(roughness) + averageHeight);
}

/*
Iterates through the terrain mesh applying the diamond sqare algorithm until all the squares have been
processed
*/
void DiamondSquare::Generate()
{
	int stepSize = (int)terrainSize;

	// Starting with the whole mesh, apply the diamond square then cut the mesh in half and repeat
	// until there are no more subsquares to process
	while(stepSize > 0)
	{
		// Apply diamond square algorithm to each sub sqaure
		for(int i = 0; i < terrainSize; i += stepSize)
		{
			for(int j = 0; j < terrainSize; j += stepSize)
			{
				DiamondStep(i, j, stepSize, params->roughness);
				SquareStep(i, j, stepSize, params->roughness);
			}
		}
		// Reduce the amount of roughness as the sqaures get smaller to prevent very spiky terrain
		params->roughness *= params->roughnessDecrement;
		// cut the mesh in half
		stepSize /= 2;
	}
}

} /* namespace Generators */

