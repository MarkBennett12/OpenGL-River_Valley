/*
 * DiamondSquare.cpp
 *
 *  Created on: 30 Nov 2013
 *      Author: mark
 */
#include <iostream>
#include "DiamondSquare.h"

namespace Generators
{

DiamondSquare::DiamondSquare(Display::Mesh* mesh, Parameters* params, int size, int iterations):
		nd(0.0, 1.0),
		generator(rng, nd)
{
	// TODO Auto-generated constructor stub
	terrainSize = size;
	numIterations = iterations;
	this->params = params;
	this->mesh = mesh;
}

DiamondSquare::~DiamondSquare()
{
	// TODO Auto-generated destructor stub
}

void DiamondSquare::Init()
{
	for(int i = 0; i < terrainSize; i++)
	{
		for(int j = 0; j < terrainSize; j++)
			mesh->AddQuad((GLfloat)j, params->baseHeight, (GLfloat)i, (GLfloat)j + 1, params->baseHeight, (GLfloat)i, (GLfloat)j + 1, params->baseHeight, (GLfloat)i + 1, (GLfloat)j, params->baseHeight, (GLfloat)i + 1);
	}

	mesh->SetYVal((GLfloat)0, (GLfloat)0, (GLfloat)fabs(Displace(1.0)));
	mesh->SetYVal((GLfloat)terrainSize, (GLfloat)0, (GLfloat)fabs(Displace(1.0)));
	mesh->SetYVal((GLfloat)terrainSize, (GLfloat)terrainSize, (GLfloat)fabs(Displace(1.0)));
	mesh->SetYVal((GLfloat)0, (GLfloat)terrainSize, (GLfloat)fabs(Displace(1.0)));
}

double DiamondSquare::Displace(double mod)
{
	return (generator() + params->baseHeight + 1.0) * mod;
}

void DiamondSquare::SquareStep(int x, int z, int size, double r)
{
	int midpoint = size / 2;
	GLfloat av = 0.0;

	av += mesh->GetYVal((GLfloat)x, (GLfloat)z);
	av += mesh->GetYVal((GLfloat)x + size, (GLfloat)z);
	av /= 2;
	mesh->SetYVal((GLfloat)x, (GLfloat)midpoint, (GLfloat)Displace(r) + av);

	av = mesh->GetYVal((GLfloat)x + size, (GLfloat)z);
	av += mesh->GetYVal((GLfloat)x + size, (GLfloat)z + size);
	av /= 2;
	mesh->SetYVal((GLfloat)x + size, (GLfloat)z + midpoint, (GLfloat)Displace(r) + av);

	av = mesh->GetYVal((GLfloat)x + size, (GLfloat)z + size);
	av += mesh->GetYVal((GLfloat)x, (GLfloat)z + size);
	av /= 2;
	mesh->SetYVal((GLfloat)x + midpoint, (GLfloat)z + size, (GLfloat)Displace(r) + av);

	av = mesh->GetYVal((GLfloat)x, (GLfloat)z + size);
	av += mesh->GetYVal((GLfloat)x, (GLfloat)z);
	av /= 2;
	mesh->SetYVal((GLfloat)x, (GLfloat)z + midpoint, (GLfloat)Displace(r) + av);
}

void DiamondSquare::DiamondStep(int x, int z, int size, double r)
{
	int midpoint = size / 2;
	GLfloat av = 0.0;

	av += mesh->GetYVal((GLfloat)x, (GLfloat)z);
	av += mesh->GetYVal((GLfloat)x + size, (GLfloat)z);
	av += mesh->GetYVal((GLfloat)x + size, (GLfloat)z + size);
	av += mesh->GetYVal((GLfloat)x, (GLfloat)z + size);
	av /= 4;

	mesh->SetYVal((GLfloat)midpoint, (GLfloat)midpoint, (GLfloat)Displace(r) + av);
}

void DiamondSquare::Generate()
{
	int stepSize = (int)terrainSize;

	while(stepSize > 0)
	{
		for(int i = 0; i < terrainSize; i += stepSize)
		{
			for(int j = 0; j < terrainSize; j += stepSize)
			{
				DiamondStep(i, j, stepSize, params->roughness);
				SquareStep(i, j, stepSize, params->roughness);
			}
		}
		params->roughness *= params->roughnessDecrement;
		stepSize /= 2;
	}
}

} /* namespace Generators */

