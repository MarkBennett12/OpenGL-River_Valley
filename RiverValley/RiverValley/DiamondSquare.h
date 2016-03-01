/*
 * DiamondSquare.h
 *
 *  Created on: 30 Nov 2013
 *      Author: mark
 */

#ifndef DIAMONDSQUARE_H_
#define DIAMONDSQUARE_H_

#include <cmath>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include "TerrainGenerator.h"

namespace Generators
{

/*
struct DSParameters:Parameters
{
};
*/

class DiamondSquare: public Generators::TerrainGenerator
{
private:
	// Boost library random number generator
	boost::mt19937 rng;
	boost::normal_distribution<> normalDistribution;
	boost::variate_generator <boost::mt19937&, boost::normal_distribution<> > generator;

	double Displace(double modifier);
	void SquareStep(int x, int z, int size, double roughness);
	void DiamondStep(int x, int z, int size, double roughness);

public:
	DiamondSquare(Geometry::TerrainMesh* mesh, Parameters* params, int size);
	virtual ~DiamondSquare();
	void Init();
	void Generate();
};

} /* namespace Generators */
#endif /* DIAMONDSQUARE_H_ */
