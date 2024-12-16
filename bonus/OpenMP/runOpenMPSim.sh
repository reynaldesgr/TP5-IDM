#!/bin/bash

# Shell script to run multiple  monte carlo simulations in 1D, 2D, and 3D

# Name of the simulation executable file
EXECUTABLE="./MTNeutron"

# Check if the executable file exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "The executable file $EXECUTABLE does not exist. Please make sure it is compiled and available."
    exit 1
fi

# Temporary benchmark file
BENCHMARK_FILE="benchmark_data.csv"

# Initialize the benchmark data file (CSV format for easy parsing in Python)
echo "Neutrons,Dimension,Execution_Time" > $BENCHMARK_FILE

# Simulation parameters
NEUTRON_COUNTS=(100 500 10000 50000 1000000 5000000) # Number of neutrons to simulate
DIMENSIONS=(1 2 3) # Simulation dimensions

# Loop through each dimension (1D, 2D, 3D)
for dimension in "${DIMENSIONS[@]}"; do
    for total_neutrons in "${NEUTRON_COUNTS[@]}"; do
        echo "Running simulation for $total_neutrons neutrons in $dimension-D..."
        
        # Measure start time
        start_time=$(date +%s.%N)
        
        # Execute the simulation
        $EXECUTABLE $total_neutrons $dimension > /dev/null 2>&1
        
        # Measure end time
        end_time=$(date +%s.%N)
        
        # Calculate the execution time
        execution_time=$(echo "$end_time - $start_time" | bc)
        
        # Log the result in the CSV file
        echo "$total_neutrons,$dimension,$execution_time" >> $BENCHMARK_FILE
        
        echo "Simulation for $total_neutrons neutrons in $dimension-D completed in $execution_time seconds."
    done
done

echo "=== Benchmark completed (data saved in $BENCHMARK_FILE) ==="