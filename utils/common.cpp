#include "common.h"

#include <iostream>

void progress(long current, long total)
{
    int     width = 70; ///< width of the progress bar
    float   progress = static_cast<float>(current) / total; ///< current progress as a fraction
    int     position = static_cast<int>(width * progress); ///< position of the progress indicator

    std::cout << "[";
    for (int i = 0; i < width; ++i) {
        if (i < position) std::cout << "=";
        else if (i == position) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}
