#include "mm_ikj.hpp"

template <typename T>
void mm_ikj(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n)
{
    if (A.size() != m * p || B.size() != n * p || C.size() != m * n)
    {
        throw std::invalid_argument("Incorrect Dimension");
    }
    for (int i = 0; i < m * n; i++)
    {
        C[i] *= b;
    }
    double r = 0;
    for (int i = 0; i < m; i++)
    {
        for (int k = 0; k < p; k++)
        {
            r = A[i + k * m];
            for (int j = 0; j < n; j++)
            {
                C[i + j * m] += a * A[i + k * m] * B[k + j * p];
            }
        }
    }
}

template void mm_ikj<double>(double a, const std::vector<double> &A, const std::vector<double> &B, double b, std::vector<double> &C, int m, int p, int n);
template void mm_ikj<float>(float a, const std::vector<float> &A, const std::vector<float> &B, float b, std::vector<float> &C, int m, int p, int n);
template void mm_ikj<int>(int a, const std::vector<int> &A, const std::vector<int> &B, int b, std::vector<int> &C, int m, int p, int n);