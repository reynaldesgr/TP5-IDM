#ifndef RANDOMUTILS_H
#define RANDOMUTILS_H

#include "../Random/Random/MTwistEngine.h"
#include "common.h"

#include <filesystem>
#include <iostream>
#include <string>

#define NUMBER_DRAWS 3000000000

// function to test and display the first generated numbers
int statusMT();

// function to generate and save multiple states of the generator
void generateAndSaveStatus(int numStatus, const long numDraws = NUMBER_DRAWS);

#endif // RANDOMUTILS_H
