#!/bin/bash

EXECUTABLE="./MTNeutron"

if [ ! -f "$EXECUTABLE" ]; then
    echo "The executable file $EXECUTABLE does not exist. Please make sure it is compiled and available."
    exit 1
fi

BENCHMARK_FILE="benchmark_data.csv"

echo "Neutrons,Dimension,Execution_Time" > $BENCHMARK_FILE

NEUTRON_COUNTS=(100 500 10000 50000 1000000 5000000) 
DIMENSIONS=(1 2 3)

for dimension in "${DIMENSIONS[@]}"; do
    for total_neutrons in "${NEUTRON_COUNTS[@]}"; do
        echo "Running simulation for $total_neutrons neutrons in $dimension-D..."
        
        start_time=$(date +%s.%N)
        $EXECUTABLE $total_neutrons $dimension > /dev/null 2>&1
        end_time=$(date +%s.%N)
        
        execution_time=$(echo "$end_time - $start_time" | bc)
        
        echo "$total_neutrons,$dimension,$execution_time" >> $BENCHMARK_FILE
        
        echo "Simulation for $total_neutrons neutrons in $dimension-D completed in $execution_time seconds."
    done
done

echo "=== Benchmark completed (data saved in $BENCHMARK_FILE) ==="