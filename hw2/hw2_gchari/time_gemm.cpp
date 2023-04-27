#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>

#include "refBLAS.hpp"

float rand_float()
{
    return rand() / static_cast<float>(RAND_MAX);
}

std::vector<float> rand_vec(int size)
{
    std::vector<float> x(size, 0.0);
    for (int i = 0; i < size; i++)
    {
        x.at(i) = rand_float();
    }
    return x;
}

std::vector<std::vector<float>> rand_mat(int m, int n)
{
    std::vector<float> zrs(n, 0.0);
    std::vector<std::vector<float>> x(m, zrs);
    for (int i = 0; i < m; i++)
    {
        x.at(i) = rand_vec(n);
    }
    return x;
}

int main()
{
    std::srand(time(0));
    int ntrial = 3;
    int s_max = 1024;
    int s_min = 2;

    std::vector<double> flops_vec(s_max - s_min + 1, 0.0);
    for (int size = s_min; size <= s_max; size += 50)
    {
        double time = 0;
        for (int i = 0; i < ntrial; i++)
        {
            auto a = rand_float();
            auto b = rand_float();
            auto A = rand_mat(size, size);
            auto B = rand_mat(size, size);
            auto C = rand_mat(size, size);

            auto start = std::chrono::high_resolution_clock::now();
            gemm(a, A, B, b, C);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            time += duration.count();
        }

        // Theoretical FLOP count for gemm is m*n*(2*p-1) + 3*m*n
        double flop_count = size * size * (2 * size - 1) + 3 * size * size;
        flops_vec[size - s_min] = (flop_count / (static_cast<double>(time) / ntrial));
        std::cout << size << std::endl;
    }

    std::ofstream output_file("gemm.csv");

    for (auto x : flops_vec)
    {
        output_file << x << ",";
    }
    output_file << std::endl;

    return 0;
}