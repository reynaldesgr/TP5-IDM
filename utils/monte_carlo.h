#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "../Random/Random/MTwistEngine.h"
#include "common.h"

#include <string>

#define NUM_POINTS 3000000000

/** restores a saved generator status and estimates the volume of a sphere using Monte Carlo simulation. */
double monteCarloVolume(CLHEP::MTwistEngine& mtEngine, long numPoints = NUM_POINTS);

/** runs a Monte Carlo simulation for multiple replications. */
void monteCarloSimulation(int numReplications, long numDrawsPerReplication);

#endif // MONTECARLO_H
