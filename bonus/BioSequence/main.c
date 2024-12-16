#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h> 
#include "../../Random/Random/MTwistEngine.h" 

#define BASES "ACGT"
#define TARGET_SEQUENCE "AAATTTGCGTTCGATTAG" // "GATTACA"
#define SEQUENCE_LENGTH 18 // 7 
#define NUM_REPLICATIONS 1
#define CONFIDENCE_LEVEL 1.96 

char generate_random_base(CLHEP::MTwistEngine *mt_engine) {
    int index = (int)(mt_engine->flat() * 4); 
    return BASES[index];
}

void generate_random_sequence(CLHEP::MTwistEngine *mt_engine, char *sequence, int length) {
    for (int i = 0; i < length; i++) {
        sequence[i] = generate_random_base(mt_engine);
    }
    sequence[length] = '\0'; 
}

int find_target_sequence(CLHEP::MTwistEngine *mt_engine, const char *target_sequence) {
    int attempts = 0;
    char generated_sequence[SEQUENCE_LENGTH + 1];
    do {
        generate_random_sequence(mt_engine, generated_sequence, SEQUENCE_LENGTH);
        attempts++;
    } while (strcmp(generated_sequence, target_sequence) != 0);
    return attempts;
}


void run_simulation(int num_replications) {
    int attempts[NUM_REPLICATIONS];
    double mean = 0.0, std_dev = 0.0, confidence_interval_lower, confidence_interval_upper;

    #pragma omp parallel for
    for (int i = 0; i < num_replications; i++) {
        CLHEP::MTwistEngine mt_engine(i + 42); 
        attempts[i] = find_target_sequence(&mt_engine, TARGET_SEQUENCE);
        printf("Replication %d\t: Attempts  = %d\n", i + 1, attempts[i]);
    }

    for (int i = 0; i < num_replications; i++) {
        mean += attempts[i];
    }
    mean /= num_replications;


    for (int i = 0; i < num_replications; i++) {
        std_dev += pow(attempts[i] - mean, 2);
    }
    std_dev = sqrt(std_dev / num_replications);

    confidence_interval_lower = mean - (CONFIDENCE_LEVEL * std_dev / sqrt(num_replications));
    confidence_interval_upper = mean + (CONFIDENCE_LEVEL * std_dev / sqrt(num_replications));

    printf("\n=== Results ===\n");
    printf("Number of replications\t: %d\n", num_replications);
    printf("Target sequence\t %s\n", TARGET_SEQUENCE);
    printf("Sequence length\t: %d\n", SEQUENCE_LENGTH);
    printf("Mean number of attempts\t: %.2f\n", mean);
    printf("Standard deviation of attempts\t %.2f\n", std_dev);
    printf("95%% Confidence Interval for attempts: [%.2f, %.2f]\n", confidence_interval_lower, confidence_interval_upper);
}

int main() {
    printf("Starting the simulation to find the target sequence : %s\n", TARGET_SEQUENCE);
    run_simulation(NUM_REPLICATIONS);
    return 0;
}
