#include "Random/Random/MTwistEngine.h"
#include "methods/MonteCarlo.h"

#include <cmath>
#include <iostream>
#include <string>
#include <filesystem>


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "[USAGE]: " << argv[0] << " <status_file> <num_points>" << std::endl;
        return 1;
    }

    std::string statusFile = argv[1];
    int numPoints = std::stoi(argv[2]);

    if (!std::filesystem::exists(statusFile)) {
        std::cerr << "Error: Status file " << statusFile << " does not exist." << std::endl;
        return 1;
    }

    CLHEP::MTwistEngine mtEngine;
    mtEngine.restoreStatus(statusFile.c_str());

    double estimatedVolume = monteCarloVolume(mtEngine, numPoints);

    std::cout << "Estimated volume: " << estimatedVolume << std::endl;
    return 0;
}
