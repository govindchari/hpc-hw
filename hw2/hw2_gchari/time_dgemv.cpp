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

std::vector<std::vector<double>> rand_mat(int m, int n)
{
    std::vector<double> zrs(n, 0.0);
    std::vector<std::vector<double>> x(m, zrs);
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
    for (int size = s_min; size <= s_max; size++)
    {
        double time = 0;
        for (int i = 0; i < ntrial; i++)
        {
            auto a = rand_double();
            auto b = rand_double();
            auto A = rand_mat(size, size);
            auto x = rand_vec(size);
            auto y = rand_vec(size);

            auto start = std::chrono::high_resolution_clock::now();
            dgemv(a, A, x, b, y);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            time += duration.count();
        }

        // Theoretical FLOP count for dgemv is m * (2n - 1) + 2 * m
        double flop_count = size * (2 * size - 1) + 3 * size;
        flops_vec[size - s_min] = (flop_count / (static_cast<double>(time) / ntrial));
        std::cout << size << std::endl;
    }

    std::ofstream output_file("dgemv.csv");

    for (auto x : flops_vec)
    {
        output_file << x << ",";
    }
    output_file << std::endl;

    return 0;
}