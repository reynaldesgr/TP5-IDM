#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "../Random/Random/MTwistEngine.h"

#include <string>

/** Restores a saved generator status and estimates the volume of a sphere using Monte Carlo simulation. */
double monteCarloVolume(CLHEP::MTwistEngine& mtEngine, int numPoints);

/** Runs a Monte Carlo simulation for multiple replications. */
void monteCarloSimulation(int numReplications, int numDrawsPerReplication);

#endif // MONTECARLO_H
