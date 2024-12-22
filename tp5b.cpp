#include "Random/Random/MTwistEngine.h"
#include "utils/monte_carlo.h"

#include <cmath>
#include <iostream>
#include <string>
#include <filesystem>

// Q5.
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "[USAGE]: " << argv[0] << " <status_file> <num_points>" << std::endl;
        return 1;
    }

    std::string statusFile = argv[1];

    if (!std::filesystem::exists(statusFile)) {
        std::cerr << "Error: Status file " << statusFile << " does not exist." << std::endl;
        return 1;
    }

    CLHEP::MTwistEngine mtEngine;
    mtEngine.restoreStatus(statusFile.c_str());

    double estimatedVolume = mvolume(mtEngine);
    
    std::cout << "Volume: " << estimatedVolume << std::endl;
    return 0;
}
