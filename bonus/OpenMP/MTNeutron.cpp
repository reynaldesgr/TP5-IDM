#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>  

#define LAMBDA 1.0     
#define RADIUS 10.0     
#define MAX_STEPS 10000  

double random_step() {
    return -LAMBDA * log((double)rand() / RAND_MAX);
}

void simulate_neutron(int dimension, int *escaped, int *absorbed) {
    double x = 0.0, y = 0.0, z = 0.0;  
    int steps = 0;

    while (steps < MAX_STEPS) {
        steps++;

        double step_length = random_step();

        if (dimension == 1) {
            x += (rand() % 2 ? 1 : -1) * step_length; 
        } else if (dimension == 2) {
            double angle = ((double)rand() / RAND_MAX) * 2 * M_PI; 
            x += step_length * cos(angle);
            y += step_length * sin(angle);
        } else if (dimension == 3) {
            double theta = ((double)rand() / RAND_MAX) * 2 * M_PI;
            double phi = acos(1 - 2 * ((double)rand() / RAND_MAX)); 
            x += step_length * sin(phi) * cos(theta);
            y += step_length * sin(phi) * sin(theta);
            z += step_length * cos(phi);
        }

        double distance = sqrt(x * x + y * y + z * z);
        if (distance > RADIUS) {
            #pragma omp atomic
            (*escaped)++;
            return;
        }

        if (((double)rand() / RAND_MAX) < 0.1) {
            #pragma omp atomic
            (*absorbed)++;
            return;
        }
    }
}

int main(int argc, char *argv[]) {
    if ( argc != 3) {
        printf( "Usage: ./{executable_file} {total_neutrons} {dimension}...\n" );
        exit( 0 );
    }
    
    int total_neutrons = atoi(argv[1]);
    int dimension      = atoi(argv[2]);

    int escaped  = 0;
    int absorbed = 0;

    srand(time(NULL));

    #pragma omp parallel for 
    for (int i = 0; i < total_neutrons; i++) {
        int local_escaped = 0;
        int local_absorbed = 0;
        simulate_neutron(dimension, &local_escaped, &local_absorbed);

        #pragma omp atomic
        escaped += local_escaped;

        #pragma omp atomic
        absorbed += local_absorbed;
    }

    printf("Total neutrons: \t%d\n", total_neutrons);
    printf("* escaped : \t%d\n", escaped);
    printf("* absorbed: \t%d\n", absorbed);

    return 0;
}
