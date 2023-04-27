#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>

#include "refBLAS.hpp"

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
    int ntrial = 1000;
    int s_max = 1024;
    int s_min = 2;

    std::vector<double> flops_vec(s_max - s_min + 1, 0.0);
    for (int size = s_min; size <= s_max; size++)
    {
        double time = 0;
        for (int i = 0; i < ntrial; i++)
        {
            auto a = rand_double();
            auto x = rand_vec(size);
            auto y = rand_vec(size);

            auto start = std::chrono::high_resolution_clock::now();
            daxpy(a, x, y);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            time += duration.count();
        }

        // Theoretical FLOP count for axpy is 2*n (n multiplications and n additions)
        double flop_count = 2 * size;
        flops_vec[size - s_min] = (flop_count / (static_cast<double>(time) / ntrial));
    }

    std::ofstream output_file("daxpy.csv");

    for (auto x : flops_vec)
    {
        output_file << x << ",";
    }
    output_file << std::endl;

    return 0;
}