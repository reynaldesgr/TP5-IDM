#include "RandomMT.h"

#include <filesystem>
#include <iostream>
#include <string>

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

void generateAndSaveStatus(int numStatus, const int numDraws) {
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
