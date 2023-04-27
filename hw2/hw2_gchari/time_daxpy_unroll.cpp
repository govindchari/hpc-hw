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
    std::vector<size_t> block_sizes = {1, 2, 4, 8, 16, 32, 64};
    std::vector<double> flops_vec(7, 0.0);
    auto a = rand_double();
    auto x = rand_vec(2048);
    size_t ntrial = 1000;

    for (size_t i = 0; i < block_sizes.size(); i++)
    {
        double time = 0;
        for (size_t j = 0; j < ntrial; j++)
        {
            auto y = rand_vec(2048);

            auto start = std::chrono::high_resolution_clock::now();
            daxpy_unroll(a, x, y, block_sizes[i]);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            time += duration.count();
        }
        flops_vec[i] = (4096 / (static_cast<double>(time) / ntrial));
    }

    std::ofstream output_file("daxpy_unroll.csv");

    for (auto x : flops_vec)
    {
        output_file << x << ",";
    }
    output_file << std::endl;

    return 0;
}