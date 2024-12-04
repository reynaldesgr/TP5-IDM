#ifndef RANDOMUTILS_H
#define RANDOMUTILS_H

#include "../Random/Random/MTwistEngine.h"

#include <filesystem>
#include <iostream>
#include <string>

#define NUMBER_DRAWS 2000000000

// Function to test and display the first generated numbers
int statusMT();

// Function to generate and save multiple states of the generator
void generateAndSaveStatus(int numStatus, const int numDraws = NUMBER_DRAWS);

#endif // RANDOMUTILS_H
