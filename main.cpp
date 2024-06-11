#include <iostream>
#include <chrono>
#include <fstream>

#include "utils/solver.h"
#include "utils/test.h"

int main() {
    int threads[] = {2, 4, 6, 8, 12, 16};
    int numOfTests = 50;
    int sizes[] = {10, 100, 500, 1000, 5000, 10000};
    int range = 50;

    std::ofstream csvFile("results.csv");
    csvFile << "array_size,number_of_threads,average_sequential_time,peak_sequential_memory,average_parallel_time,peak_parallel_memory\n";

    for(auto& size : sizes) {
        std::chrono::duration<double, std::milli> totalSequentialTime(0);
        long peakSequentialMemory = 0;

        for (int i = 0; i < numOfTests; i++) {
            auto [array, target] = generateVectorAndTarget(size, range);
            auto start = std::chrono::high_resolution_clock::now();
            bool foundSequential = subsetSumSequential(array, target);
            auto end = std::chrono::high_resolution_clock::now();
            totalSequentialTime += end - start;
            long currentMemory = getPeakMemoryUsage();
            if (currentMemory > peakSequentialMemory) {
                peakSequentialMemory = currentMemory;
            }
        }

        double meanSequentialTime = totalSequentialTime.count() / numOfTests;

        for(auto& thread : threads) {
            std::chrono::duration<double, std::milli> totalParallelTime(0);
            long peakParallelMemory = 0;

            for (int i = 0; i < numOfTests; i++) {
                auto [array, target] = generateVectorAndTarget(size, range);
                auto start = std::chrono::high_resolution_clock::now();
                bool foundParallel = subsetSumParallel(array, target, thread);
                auto end = std::chrono::high_resolution_clock::now();
                totalParallelTime += end - start;
                long currentMemory = getPeakMemoryUsage();
                if (currentMemory > peakParallelMemory) {
                    peakParallelMemory = currentMemory;
                }
            }
            double meanParallelTime = totalParallelTime.count() / numOfTests;

            csvFile << size << "," << thread << ","
                    << meanSequentialTime << "," << peakSequentialMemory << ","
                    << meanParallelTime << "," << peakParallelMemory << "\n";

            std::cout << "Vetor de tamanho " << size << " e " << thread << " threads --> OK" << std::endl;
        }
    }
    csvFile.close();
    return 0;
}
