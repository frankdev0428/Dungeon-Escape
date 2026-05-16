#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>

// Shared HP/progress bar used by UI and Room
inline void printBar(int current, int max, int width = 10) {
    int filled = (max > 0) ? (current * width / max) : 0;
    if (filled > width) filled = width;
    std::cout << "[";
    for (int i = 0; i < width; i++)
        std::cout << (i < filled ? "\xe2\x96\x88" : "\xe2\x96\x91");
    std::cout << "] " << current << "/" << max;
}

#endif
