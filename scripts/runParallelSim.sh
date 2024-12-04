#!/bin/bash

# Check if the correct number of arguments is passed
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <num_points>"
    exit 1
fi

# Get the number of points from the argument
num_points=$1

# Define the status file prefix
status_file_prefix="MTwist_status"

# Create the 'results' directory if it doesn't already exist
mkdir -p results

# Run the 10 replications in parallel
for i in {1..10}
do
    # Capture the current date and time in a detailed format (including milliseconds)
    start_time=$(date "+%Y-%m-%d %H:%M:%S.%3N")
    
    # Log the start of the replication with thread (PID) info
    echo "[Script PID: $$] [Replication $i] Starting replication at $start_time" >> replication_log.txt

    # Define the status file for replication i
    status_file="../status/${status_file_prefix}_${i}.conf"
    
    # Check if the status file exists
    if [ ! -f "$status_file" ]; then
        echo "[Script PID: $$] [Replication $i] Error: Status file $status_file does not exist!" >> replication_log.txt
        continue
    fi
    
    # Run the replication in the background and redirect output to the appropriate file
    ./../tp5b $status_file $num_points > "results/output_replication_$i.txt" &
    
    # Capture the PID of the background process
    background_pid=$!
    
    # Log that the replication has started and include the background PID
    echo "[Script PID: $$] [Replication $i] Background job started with PID: $background_pid at $start_time" >> replication_log.txt
done

# Wait for all background tasks to finish and log when they finish
wait

# Capture the completion time of the entire script
completion_time=$(date "+%Y-%m-%d %H:%M:%S.%3N")
echo "[Script PID: $$] All simulations completed at $completion_time" >> replication_log.txt
