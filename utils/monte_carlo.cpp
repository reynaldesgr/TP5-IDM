#include "monte_carlo.h"
#include "common.h"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <CLHEP/Random/MTwistEngine.h>

#define RADIUS 1.0 ///< radius of the sphere

/**
 * @brief estimates the volume of a sphere using the Monte Carlo method.
 * 
 * uses the Monte Carlo method to estimate the volume of a sphere
 * by randomly generating points inside a cube and checking if they fall within
 * the sphere.
 *
 * @param mtEngine Mersenne Twister random engine used to generate random points.
 * @param numPoints number of random points to generate for the estimation.
 * @return estimated volume of the sphere based on the random points.
 */
double mvolume(CLHEP::MTwistEngine& mtEngine, long numPoints) {
    int inside = 0;

    printf("\n Estimating volume by Monte Carlo method... \n");
    
    for (long i = 0; i < numPoints; ++i) {
        double x = mtEngine.flat();
        double y = mtEngine.flat();
        double z = mtEngine.flat();

        if (x * x + y * y + z * z <= RADIUS * RADIUS) {
            inside++;
        }
        
        if ((i + 1) % (numPoints / 100) == 0) progress(i + 1, numPoints);
    }

    return (inside / static_cast<double>(numPoints)) * 8.0;
}

/**
 * @brief runs the Monte Carlo simulation for multiple replications.
 * 
 * performs a Monte Carlo simulation for a given number of replications
 * and draws per replication.
 *
 * @param numReplications number of replications to run the simulation.
 * @param numDrawsPerReplication number of points to generate in each replication for volume estimation.
 */
void mcsimulation(int numReplications, long numDrawsPerReplication) {
    double totalVolume = 0.0;
    std::vector<double> volumes;

    std::cout << "\n Num. replications : " << numReplications << "/ Num. draws per replication : " << numReplications << numDrawsPerReplication << std::endl;

    for (int replication = 0; replication < numReplications; ++replication) {
        std::string filename = "status/status-" + std::to_string(replication + 1) + ".conf";
        CLHEP::MTwistEngine mtEngine;

        mtEngine.restoreStatus(filename.c_str());

        double volume = mvolume(mtEngine, numDrawsPerReplication);
        totalVolume += volume;
        volumes.push_back(volume); 

        std::cout << "\n Replication " << replication + 1 << ": Estimated volume = " << volume << std::endl;
    }

    double averageVolume = totalVolume / numReplications;

    double sumSquaredDiffs = 0.0;
    for (double volume : volumes) {
        sumSquaredDiffs += std::pow(volume - averageVolume, 2);
    }
    double variance = sumSquaredDiffs / (numReplications - 1);
    double stdDeviation = std::sqrt(variance);

    double t_value = 2.262; // Student's t-value for a 95% confidence interval (n = 10 - 1 = 9 degrees of freedom)
    double marginOfError = t_value * (stdDeviation / std::sqrt(numReplications));
    double lowerBound = averageVolume - marginOfError;
    double upperBound = averageVolume + marginOfError;

    std::cout << "\n >> Average estimated volume after " << numReplications << " replications: " << averageVolume << std::endl;
    std::cout << " >> Standard deviation: " << stdDeviation << std::endl;
    std::cout << " >> Variance: " << variance << std::endl;
    std::cout << " >> 95% Confidence interval: [" << lowerBound << ", " << upperBound << "]" << std::endl;
}
