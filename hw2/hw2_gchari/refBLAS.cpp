#include "refBLAS.hpp"

void daxpy(double a, const std::vector<double> &x, std::vector<double> &y)
{
    size_t xs = x.size();
    size_t ys = y.size();
    if (xs != ys)
        throw std::invalid_argument("Dimension Mismatch");
    for (size_t i = 0; i < xs; i++)
    {
        y[i] += a * x[i];
    }
}

void daxpy_unroll(double a, const std::vector<double> &x, std::vector<double> &y, int block_size)
{
    size_t xs = x.size();
    size_t ys = y.size();
    if (xs != ys)
        throw std::invalid_argument("Dimension Mismatch");

    if (block_size < 4)
    {
        daxpy(a, x, y);
    }
    else
    {

        size_t i = 0;
        size_t j = 0;
        for (i = 0; i < xs / block_size; i++)
        {
            for (j = 0; j < block_size / 4; j++)
            {
                y[i * block_size + 4 * j] += a * x[i * block_size + 4 * j];
                y[i * block_size + 4 * j + 1] += a * x[i * block_size + 4 * j + 1];
                y[i * block_size + 4 * j + 2] += a * x[i * block_size + 4 * j + 2];
                y[i * block_size + 4 * j + 3] += a * x[i * block_size + 4 * j + 3];
            }
        }
        for (size_t k = (i - 1) * block_size + 4 * (j); k < xs; k++)
        {
            y[k] += a * x[k];
        }
    }
}

void dgemv(double a, const std::vector<std::vector<double>> &A, const std::vector<double> &x, double b, std::vector<double> &y)
{
    size_t m = A.size();
    size_t n = A[0].size();
    size_t xs = x.size();
    size_t ys = y.size();

    if (n != xs || m != ys)
        throw std::invalid_argument("Dimension Mismatch");
    for (size_t i = 0; i < m; i++)
    {
        double accum = 0;
        for (size_t j = 0; j < n; j++)
        {
            accum += A[i][j] * x[j];
        }
        y[i] = a * accum + b * y[i];
    }
}

void dgemm(double a, const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B, double b, std::vector<std::vector<double>> &C)
{
    size_t m = A.size();
    size_t p = A[0].size();
    size_t Brow = B.size();
    size_t n = B[0].size();

    size_t Crow = C.size();
    size_t Ccol = C[0].size();

    if (m != Ccol || p != Brow || n != Ccol)
        throw std::invalid_argument("Dimension Mismatch");
    double accum = 0;
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            accum = 0.0;
            for (size_t k = 0; k < p; k++)
            {
                accum += A[i][k] * B[k][j];
            }
            C[i][j] = a * accum + b * C[i][j];
        }
    }
}
