#include "Random/Random/MTwistEngine.h"

#include <cmath>
#include <ctime>
#include <filesystem> 
#include <iostream>
#include <vector>

#define NUMBER_DRAWS 2000000000
#define RADIUS 1.0

int statusMT() {
    CLHEP::MTwistEngine mtEngine;

    mtEngine.saveStatus();

    std::cout << "First 10 generated numbers:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << mtEngine.flat() << std::endl;
    }

    std::cout << "Generator state saved to 'MTwist.conf'.\n";
    mtEngine.restoreStatus(); 

    std::cout << "Generator restored.\n";
    std::cout << "\nRestored generator, first 10 generated numbers:\n";

    for (int i = 0; i < 10; ++i) {
        std::cout << mtEngine.flat() << std::endl;
    }

    return 0;
}

void generateAndSaveStatus(int numStatus, const int numDraws = NUMBER_DRAWS) {
    std::string directory = "status";
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directory(directory);
    }
    CLHEP::MTwistEngine mtEngine;

    for (int statusIndex = 0; statusIndex < numStatus; ++statusIndex) {
        for (int i = 0; i < numDraws; ++i) {
            mtEngine.flat();
        }
        std::string filename = directory + "/MTwist_status_" + std::to_string(statusIndex + 1) + ".conf";
        
        mtEngine.saveStatus(filename.c_str());
        std::cout << "État généré et sauvegardé dans le fichier : " << filename << std::endl;
    }
}


/** MONTE CARLO **/
double monteCarloVolume(int numPoints) {
    int inside = 0;
    
    for (int i = 0; i < numPoints; ++i) {

        double x = rand() / (RAND_MAX + 1.0);
        double y = rand() / (RAND_MAX + 1.0);
        double z = rand() / (RAND_MAX + 1.0);

        if (x*x + y*y + z*z <= RADIUS * RADIUS) {
            inside++;
        }
    }
    
    return (inside / static_cast<double>(numPoints)) * 8.0; 
}

void monteCarloSimulation(int numReplications, const int numDrawsPerReplication) {
    double totalVolume = 0.0;

    for (int replication = 0; replication < numReplications; ++replication) {
        std::string filename = "status/MTwist_status_" + std::to_string(replication + 1) + ".conf";
        CLHEP::MTwistEngine mtEngine;
        mtEngine.restoreStatus(filename.c_str());

        double volume = monteCarloVolume(numDrawsPerReplication);
        totalVolume += volume;

        std::cout << "Replication " << replication + 1 << ": Estimated volume = " << volume << std::endl;
    }

    double averageVolume = totalVolume / numReplications;
    std::cout << "Average estimated volume after " << numReplications << " replications: " << averageVolume << std::endl;
}

int main()
{
    statusMT();

    int numStatus = 10;
    // generateAndSaveStatus(numStatus);

    /** MONTE CARLO **/
    int numReplications = 10;
    int numDrawsPerReplication = NUMBER_DRAWS;

    clock_t start = clock();
    monteCarloSimulation(numReplications, numDrawsPerReplication);
    clock_t end = clock();

    double timeSpent = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Total time for " << numReplications << " replicates: " << timeSpent << " seconds." << std::endl;
}