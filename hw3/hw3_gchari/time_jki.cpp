#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>

#include "mm_jki.hpp"

double rand_double()
{
    return rand() / static_cast<double>(RAND_MAX);
}

std::vector<double> rand_vec(int size)
{
    std::vector<double> x(size, 0.0);
    for (int i = 0; i < size; i++)
    {
        x.at(i) = rand_double();
    }
    return x;
}

int main()
{
    std::srand(time(0));
    int ntrial = 3;
    int s_max = 512;
    int s_min = 2;

    std::vector<double> flops_vec(s_max - s_min + 1, 0.0);
    for (int size = s_min; size <= s_max; size++)
    {
        long double time = 0;
        for (int i = 0; i < ntrial; i++)
        {
            auto a = rand_double();
            auto b = rand_double();
            auto A = rand_vec(size * size);
            auto B = rand_vec(size * size);
            auto C = rand_vec(size * size);

            auto start = std::chrono::high_resolution_clock::now();
            mm_jki(a, A, B, b, C, size, size, size);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            time += duration.count();
        }
        // Theoretical FLOP count for gemm is m * (2n - 1) + 2 * m
        double flop_count = size * size * (2 * size - 1) + 3 * size * size;
        flops_vec[size - s_min] = (flop_count / (static_cast<double>(time) / ntrial));
        std::cout << size << std::endl;
    }

    std::ofstream output_file("data/time_jki.csv");

    for (auto x : flops_vec)
    {
        output_file << x << ",";
    }
    output_file << std::endl;

    return 0;
}