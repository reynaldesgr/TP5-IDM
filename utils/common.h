#ifndef COMMON_UTILITY_H
#define COMMON_UTILITY_H

/**
 * @brief displays a progress bar to track the completion of a process.
 * 
 * @details shows a progress bar indicating the progress
 * of a task in the format `[====>   ] 50%`.
 *
 * @param current current progress count.
 * @param total total number of steps for the process.
 */
void progress(long current, long total);

#endif // COMMON_UTILITY_H