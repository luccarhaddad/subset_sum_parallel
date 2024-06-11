//
// Created by Lucca Haddad on 10/06/24.
//

#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <thread>
#include <atomic>

bool subsetSumSequential(const std::vector<int>& array, int target);
void findSubset(const std::vector<int>& array, unsigned int start, unsigned int end, int target, std::atomic<bool>& found);
bool subsetSumParallel(const std::vector<int>& array, int target, int numberOfThreads);

#endif //SOLVER_H
