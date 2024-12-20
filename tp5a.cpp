#include "utils/status.h" 
#include "utils/monte_carlo.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

// Q1., Q2., Q3., Q4.
int main()
{
    statusMT();

    int numStatus = 10;
    // Uncomment the next line to generate and save multiple states
    // generateAndSaveStatus(numStatus);

    int numReplications         = numStatus;
    long numDrawsPerReplication = NUMBER_DRAWS;

    auto start = std::chrono::high_resolution_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::cout << "\n === Performing Monte Carlo Simulation ===" << std::endl;
    std::cout << "\n** Start task at: " << std::put_time(std::localtime(&start_time), "%Y-%m-%d %H:%M:%S") << std::endl;

    monteCarloSimulation(numReplications, numDrawsPerReplication);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time used : " << elapsed.count() << " seconds" << std::endl;
}
