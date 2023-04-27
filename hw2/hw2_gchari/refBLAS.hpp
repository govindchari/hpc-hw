#pragma once

#include <iostream>
#include <vector>

void daxpy(double a, const std::vector<double> &x, std::vector<double> &y);
void daxpy_unroll(double a, const std::vector<double> &x, std::vector<double> &y, int block_size);
void dgemv(double a, const std::vector<std::vector<double>> &A, const std::vector<double> &x, double b, std::vector<double> &y);
void dgemm(double a, const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B, double b, std::vector<std::vector<double>> &C);

template <typename T>
void axpy(T a, const std::vector<T> &x, std::vector<T> &y)
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

template <typename T>
void gemv(T a, const std::vector<std::vector<T>> &A, const std::vector<T> &x, T b, std::vector<T> &y)
{
    size_t m = A.size();
    size_t n = A[0].size();
    size_t xs = x.size();
    size_t ys = y.size();

    if (n != xs || m != ys)
        throw std::invalid_argument("Dimension Mismatch");
    for (size_t i = 0; i < m; i++)
    {
        T accum = 0;
        for (size_t j = 0; j < n; j++)
        {
            accum += A[i][j] * x[j];
        }
        y[i] = a * accum + b * y[i];
    }
}

template <typename T>
void gemm(T a, const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, T b, std::vector<std::vector<T>> &C)
{
    size_t m = A.size();
    size_t p = A[0].size();
    size_t Brow = B.size();
    size_t n = B[0].size();

    size_t Crow = C.size();
    size_t Ccol = C[0].size();

    if (m != Ccol || p != Brow || n != Ccol)
        throw std::invalid_argument("Dimension Mismatch");
    T accum = 0;
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
