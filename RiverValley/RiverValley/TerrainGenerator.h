/*
 * TerrainGenerator.h
 *
 *  Created on: 30 Nov 2013
 *      Author: mark
 */
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include "Mesh.h"

#ifndef TERRAINGENERATOR_H_
#define TERRAINGENERATOR_H_

namespace Generators
{

struct Parameters
{
	GLfloat baseHeight;
	double roughness;
	double roughnessDecrement;
};

class TerrainGenerator
{
protected:
	int terrainSize;
	Parameters* params;
	Display::Mesh* mesh;

public:
	TerrainGenerator();
	virtual ~TerrainGenerator();
	virtual void Init() = 0;
	int GetSize();
	virtual void Generate() = 0;
};

} /* namespace Generators */
#endif /* TERRAINGENERATOR_H_ */
