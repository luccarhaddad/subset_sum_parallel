//
// Created by Lucca Haddad on 10/06/24.
//

#include "solver.h"

bool subsetSumSequential(const std::vector<int>& array, int target) {
    int n = array.size();
    unsigned int numberOfSubsets = 1 << n;

    for(unsigned int i = 0; i < numberOfSubsets; i++) {
        int sum = 0;
        for(int j = 0; j < n; j++) {
            if(i & (1 << j))
                sum += array[j];
        }
        if(sum == target) return true;
    }
    return false;
}

void findSubset(const std::vector<int>& array, unsigned int start, unsigned int end, int target, std::atomic<bool>& found) {
    int n = array.size();
    for(unsigned int i  = start; i < end && !found.load(); i++) {
        int sum = 0;
        for(int j = 0; j < n; j++) {
            if(i & (1 << j))
                sum += array[j];
        }
        if(sum == target) {
            found.store(true);
            return;
        }
    }
}

bool subsetSumParallel(const std::vector<int>& array, int target, int numberOfThreads) {
    int n = array.size();
    unsigned int numberOfSubsets = 1 << n;
    std::vector<std::thread> threads;
    std::atomic<bool> found(false);

    unsigned int segmentSize = numberOfSubsets / numberOfThreads;
    for(int i = 0; i < numberOfThreads; i++) {
        unsigned int start = i * segmentSize;
        unsigned int end = (i == numberOfThreads - 1) ? numberOfSubsets : start + segmentSize;
        threads.emplace_back(findSubset, std::cref(array), start, end, target, std::ref(found));
    }

    for(auto& thread : threads) {
        thread.join();
    }

    return found.load();
}