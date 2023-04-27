#include "mm_ijk.hpp"

template <typename T>
void mm_ijk(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n)
{
    if (A.size() != m * p || B.size() != n * p || C.size() != m * n)
    {
        throw std::invalid_argument("Incorrect Dimension");
    }
    double accum = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            accum = 0;
            for (int k = 0; k < p; k++)
            {
                accum += A[i + k * p] * B[k + j * n];
            }
            C[i + j * m] = a * accum + b * C[i + j * m];
        }
    }
}

template void mm_ijk<double>(double a, const std::vector<double> &A, const std::vector<double> &B, double b, std::vector<double> &C, int m, int p, int n);
template void mm_ijk<float>(float a, const std::vector<float> &A, const std::vector<float> &B, float b, std::vector<float> &C, int m, int p, int n);
template void mm_ijk<int>(int a, const std::vector<int> &A, const std::vector<int> &B, int b, std::vector<int> &C, int m, int p, int n);