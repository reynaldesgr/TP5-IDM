/**
 * @file status.cpp
 * @brief manages the generation and storage of random engine statuses.
 *
 * provides tools to track progress, generate multiple random engine 
 * statuses and store them for later use. 
 *
 * @details
 * - saves random generator states to files in the "status" directory.
 * - restores saved random generator states.
 *
 * @author SEGERIE Reynalde
 */

#include "status.h"

#include <filesystem>
#include <iostream>
#include <string>

/**
 * @brief saving and restoring the state of the random generator.
 *
 * generates 10 random numbers, saves the state of the generator, 
 * restores it, and generates another 10 random numbers to demonstrate the restoration process.
 *
 * @return int exit status.
 */
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

/**
 * @brief generates and saves multiple random generator statuses.
 *
 * generates multiple random generator states, saving each state as a separate file
 * in the "status" directory. Each draw is tracked using a progress bar to visualize progress.
 *
 * @param numStatus number of generator states to create.
 * @param numDraws number of random draws to generate for each status.
 */
void generateAndSaveStatus(int numStatus, long numDraws) {

    printf("\n ==== Saving generator status ==== \n");
    printf("Num. status : %d, Num. draws : %ld \n", numStatus, numDraws);

    std::string directory = "status";

    std::string name;
    std::string filename;

    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directory(directory);
    }

    CLHEP::MTwistEngine mtEngine;

    for (int statusIndex = 0; statusIndex < numStatus; ++statusIndex) {
        for (long i = 0; i < numDraws; ++i) {
            mtEngine.flat();
            if ((i + 1) % (numDraws / 100) == 0) progress(i + 1, numDraws);
        }

        name = "status-" + std::to_string(statusIndex + 1) + ".conf";
        filename = directory + "/" + name;

        mtEngine.saveStatus(filename.c_str());
        
        std::cout << "\n" << name << " saved." << std::endl;
    }
}