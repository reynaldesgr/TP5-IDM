#include "MonteCarlo.h"

#include <cmath>
#include <filesystem>
#include <iostream>

#define RADIUS 1.0

double monteCarloVolume(CLHEP::MTwistEngine& mtEngine, int numPoints) {
    int inside = 0;

    for (int i = 0; i < numPoints; ++i) {
        double x = mtEngine.flat();
        double y = mtEngine.flat();
        double z = mtEngine.flat();

        if (x * x + y * y + z * z <= RADIUS * RADIUS) {
            inside++;
        }
    }

    return (inside / static_cast<double>(numPoints)) * 8.0;
}

void monteCarloSimulation(int numReplications, int numDrawsPerReplication) {
    double totalVolume = 0.0;

    for (int replication = 0; replication < numReplications; ++replication) {
        std::string filename = "status/MTwist_status_" + std::to_string(replication + 1) + ".conf";
        CLHEP::MTwistEngine mtEngine;

        mtEngine.restoreStatus(filename.c_str());

        double volume = monteCarloVolume(mtEngine, numDrawsPerReplication);
        totalVolume += volume;

        std::cout << "Replication " << replication + 1 << ": Estimated volume = " << volume << std::endl;
    }

    double averageVolume = totalVolume / numReplications;
    std::cout << "Average estimated volume after " << numReplications << " replications: " << averageVolume << std::endl;
}
