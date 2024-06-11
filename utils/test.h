//
// Created by Lucca Haddad on 10/06/24.
//

#ifndef TEST_H
#define TEST_H

#include <sys/resource.h>
#include <random>

long getPeakMemoryUsage();
std::pair<std::vector<int>, int> generateVectorAndTarget(int size, int range);

#endif //TEST_H
