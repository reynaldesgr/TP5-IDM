#!/bin/bash

num_points=3000000000
status_file_prefix="status-"

mkdir -p results

overall_start_time=$(date +%s%3N)

# run 10 replications in parallel
for i in {1..10}
do
    start_time=$(date "+%Y-%m-%d %H:%M:%S.%3N")
    
    echo "[Script PID: $$] [Replication $i] Starting replication at $start_time" >> replication_log.txt

    status_file="../status/${status_file_prefix}${i}.conf"
    
    if [ ! -f "$status_file" ]; then
        echo "[Script PID: $$] [Replication $i] Error: Status file $status_file does not exist!" >> replication_log.txt
        continue
    fi

    ./../tp5b $status_file $num_points > "results/output_replication_$i.txt" &
    
    background_pid=$!
    
    echo "[Script PID: $$] [Replication $i] Background job started with PID: $background_pid at $start_time" >> replication_log.txt
done

wait

completion_time=$(date "+%Y-%m-%d %H:%M:%S.%3N")
overall_end_time=$(date +%s%3N)

total_time_ms=$((overall_end_time - overall_start_time))
total_time_seconds=$(echo "scale=3; $total_time_ms / 1000" | bc)

echo "[Script PID: $$]  *** All simulations completed at $completion_time ***" >> replication_log.txt
echo "[Script PID: $$]  *** Total time taken: $total_time_seconds seconds ***" >> replication_log.txt

total_volume=0
count=0
volumes=()

for i in {1..10}
do
    output_file="results/output_replication_$i.txt"
    
    if [ -f "$output_file" ]; then
        estimated_volume=$(grep "Volume:" "$output_file" | awk -F ':' '{print $2}' | xargs)
        if [ -n "$estimated_volume" ]; then
            total_volume=$(echo "$total_volume + $estimated_volume" | bc)
            count=$((count + 1))
            volumes+=($estimated_volume)
        fi
    fi
done

if [ $count -gt 0 ]; then
    average_volume=$(echo "scale=10; $total_volume / $count" | bc)

    sum_of_squares=0
    for volume in "${volumes[@]}"
    do
        difference=$(echo "scale=10; $volume - $average_volume" | bc)
        square=$(echo "scale=10; $difference * $difference" | bc)
        sum_of_squares=$(echo "scale=10; $sum_of_squares + $square" | bc)
    done
    
    variance=$(echo "scale=10; $sum_of_squares / $count" | bc)
    std_deviation=$(echo "scale=10; sqrt($variance)" | bc)
    
    z_value=1.96 # 
    margin_of_error=$(echo "scale=10; $z_value * $std_deviation / sqrt($count)" | bc)
    lower_bound=$(echo "scale=10; $average_volume - $margin_of_error" | bc)
    upper_bound=$(echo "scale=10; $average_volume + $margin_of_error" | bc)
    
    echo "Average estimated volume after $count replications: $average_volume" >> replication_log.txt
    echo "Variance of estimated volumes: $variance" >> replication_log.txt
    echo "Standard deviation of estimated volumes: $std_deviation" >> replication_log.txt
    echo "95% confidence interval for estimated volume: [$lower_bound, $upper_bound]" >> replication_log.txt
    
    echo "Average estimated volume after $count replications: $average_volume"
    echo "Variance of estimated volumes: $variance"
    echo "Standard deviation of estimated volumes: $std_deviation"
    echo "95% confidence interval for estimated volume: [$lower_bound, $upper_bound]"
else
    echo "No valid estimated volumes found in the results."
    echo "No valid estimated volumes found in the results." >> replication_log.txt
fi

echo "All simulations completed. Total time taken: $total_time_seconds seconds."