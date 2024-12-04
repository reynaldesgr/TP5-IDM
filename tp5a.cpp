#include "utils/RandomMT.h" 
#include "methods/MonteCarlo.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

int main()
{
    statusMT();

    int numStatus = 10;
    // Uncomment the next line to generate and save multiple states
    generateAndSaveStatus(numStatus);

    /** MONTE CARLO **/
    int numReplications = 10;
    int numDrawsPerReplication = NUMBER_DRAWS;

    clock_t start = clock();
    monteCarloSimulation(numReplications, numDrawsPerReplication);
    clock_t end = clock();

    double timeSpent = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Total time for " << numReplications << " replications: " << timeSpent << " seconds." << std::endl;
}
