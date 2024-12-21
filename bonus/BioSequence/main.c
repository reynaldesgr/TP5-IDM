#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include "../../Random/Random/MTwistEngine.h"

#define BASES "ACGT"
#define TARGET_SEQUENCE "AAATTTGCGTTCGATTAG"
#define SEQUENCE_LENGTH 18
#define NUM_REPLICATIONS 40
#define CONFIDENCE_LEVEL 1.96

char base(CLHEP::MTwistEngine *mt_engine) {
    int index = (int)(mt_engine->flat() * 4);
    return BASES[index];
}

void sequence(CLHEP::MTwistEngine *mt_engine, char *sequence, int length) {
    for (int i = 0; i < length; i++) {
        sequence[i] = base(mt_engine);
    }
    sequence[length] = '\0';
}

int find_sequence(CLHEP::MTwistEngine *mt_engine, const char *target_sequence, int sequence_length) {
    int attempts = 0;
    char generated_sequence[sequence_length + 1];
    do {
        sequence(mt_engine, generated_sequence, sequence_length);
        attempts++;
    } while (strcmp(generated_sequence, target_sequence) != 0);
    return attempts;
}

void calculate(CLHEP::MTwistEngine *mt_engine, const char *target_sequence) {
    int full_length = strlen(target_sequence);
    for (int length = 1; length <= full_length; length++) {
        char sub_target[length + 1];
        strncpy(sub_target, target_sequence, length);
        sub_target[length] = '\0';

        int attempts = find_sequence(mt_engine, sub_target, length);
        double probability = pow(0.25, length);

        printf("sub-sequence: %s\n", sub_target);
        printf("* attempts: %d\n", attempts);
        printf("* probability (theorical): %.10f\n", probability);
        printf("===============================\n");
    }
}

int main() {
    printf("\n** Target sequence: %s\n", TARGET_SEQUENCE);

    // Initialize random engine and analyze sub-sequences
    CLHEP::MTwistEngine mt_engine(42);
    calculate(&mt_engine, TARGET_SEQUENCE);

    return 0;
}
