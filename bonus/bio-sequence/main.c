#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include "../../Random/Random/MTwistEngine.h"

#define BASES "ACGT" ///< nucleotide bases to generate random sequence
#define TARGET_SEQUENCE "AAATTTGCGTTCGATTAG" ///< target sequence to match using Monte Carlo
#define SEQUENCE_LENGTH 18 ///< length of the target sequence
#define NUM_REPLICATIONS 40 ///< number of replications to run for confidence interval
#define CONFIDENCE_LEVEL 1.96 ///< z-score for 95% confidence interval

/**
 * @brief generates a random base ('A', 'C', 'G', or 'T') using the Mersenne Twister random engine.
 * 
 * generates a random number between 0 and 1 using the `flat` method of the `MTwistEngine`,
 * and maps it to one of the four nucleotide bases ('A', 'C', 'G', or 'T').
 *
 * @param mt_engine Mersenne Twister random engine to generate random numbers.
 * @return A random base from the set {'A', 'C', 'G', 'T'}.
 */
char base(CLHEP::MTwistEngine *mt_engine) {
    int index = (int)(mt_engine->flat() * 4); 
    return BASES[index]; 
}

/**
 * @brief Generates a random nucleotide sequence of specified length.
 * 
 * This function generates a sequence of nucleotides by calling the `base` function repeatedly.
 *
 * @param mt_engine Mersenne Twister random engine to generate random numbers.
 * @param sequence pointer to the character array where the generated sequence will be stored.
 * @param length length of the sequence to generate.
 */
void sequence(CLHEP::MTwistEngine *mt_engine, char *sequence, int length) {
    for (int i = 0; i < length; i++) {
        sequence[i] = base(mt_engine);  
    }
    sequence[length] = '\0'; 
}

/**
 * @brief finds the target sequence by generating random sequences and counting the number of attempts.
 * 
 * generates random sequences using the `sequence` function until it matches the target sequence.
 *
 * @param mt_engine Mersenne Twister random engine to generate random sequences.
 * @param target_sequence sequence we are trying to match.
 * @param sequence_length length of the target sequence.
 * @return  number of attempts taken to generate the target sequence.
 */
int find_sequence(CLHEP::MTwistEngine *mt_engine, const char *target_sequence, int sequence_length) {
    int attempts = 0; 
    char generated_sequence[sequence_length + 1];  
    do {
        sequence(mt_engine, generated_sequence, sequence_length); 
        attempts++; 
    } while (strcmp(generated_sequence, target_sequence) != 0);  
    return attempts;  
}

/**
 * @brief Calculates the number of attempts needed to generate each sub-sequence across multiple replications.
 *
 * @param mt_engine Mersenne Twister random engine to be used in each replication.
 * @param target_sequence target sequence to generate sub-sequences from.
 */
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
        printf("* probability (theoretical): %.10f\n", probability);
        printf("===============================\n");
    }
}

/**
 * @brief executes the sequence generation and statistical calculations.
 */
int main() {
    printf("\n** Target sequence: %s\n", TARGET_SEQUENCE);  
    
    CLHEP::MTwistEngine mt_engine;
   
    calculate(&mt_engine, TARGET_SEQUENCE); 

    return 0;  
}
