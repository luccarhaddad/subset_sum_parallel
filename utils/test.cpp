//
// Created by Lucca Haddad on 10/06/24.
//

#include "test.h"

long getPeakMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

std::pair<std::vector<int>, int> generateVectorAndTarget(int size, int range) {
    std::vector<int> result(size);
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(-range, range);

    int subsetSize = std::uniform_int_distribution<int>(1, size)(generator);

    std::vector<int> subsetPositions(subsetSize);
    for (int i = 0; i < subsetSize; ++i) {
        subsetPositions[i] = std::uniform_int_distribution<int>(0, size - 1)(generator);
    }

    int target = 0;
    for (int i = 0; i < size; ++i) {
        result[i] = distribution(generator);
        if (std::find(subsetPositions.begin(), subsetPositions.end(), i) != subsetPositions.end()) {
            target += result[i];
        }
    }
    return {result, target};
}
