#include "strassen.hpp"

template <typename T>
std::vector<std::vector<T>> add(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B)
{
    auto m = A.size();
    auto n = A[0].size();

    auto mb = B.size();
    auto nb = B[0].size();

    assert(m == mb && n == nb);

    std::vector<std::vector<T>> C(m, std::vector<T>(n, 1));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

template <typename T>
std::vector<std::vector<T>> sub(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B)
{
    auto m = A.size();
    auto n = A[0].size();

    auto mb = B.size();
    auto nb = B[0].size();

    assert(m == mb && n == nb);

    std::vector<std::vector<T>> C(m, std::vector<T>(n, 1));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

template <typename T>
std::vector<std::vector<T>> getBlock(const std::vector<std::vector<T>> &A, const int a, const int b)
{
    auto m = A.size();
    auto n = A[0].size();
    assert(m == n);
    std::vector<std::vector<T>> C(m / 2, std::vector<T>(n / 2, 1));
    for (int i = a * (m / 2); i < (a + 1) * (m / 2); i++)
    {
        for (int j = b * (n / 2); j < (b + 1) * (n / 2); j++)
        {
            C[i % (m / 2)][j % (n / 2)] = A[i][j];
        }
    }
    return C;
}

template <typename T>
void writeBlock(std::vector<std::vector<T>> &A, std::vector<std::vector<T>> &B, const int a, const int b)
{
    auto m = A.size();
    auto n = A[0].size();
    assert(m == n);
    for (int i = a * (m / 2); i < (a + 1) * (m / 2); i++)
    {
        for (int j = b * (n / 2); j < (b + 1) * (n / 2); j++)
        {
            A[i][j] = B[i % (m / 2)][j % (n / 2)];
        }
    }
}

template <typename T>
std::vector<std::vector<T>> strassen_mm(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B)
{
    auto m = A.size();
    auto n = A[0].size();
    assert(m == n);
    std::vector<std::vector<T>> C(m, std::vector<T>(n, 1));
    if (m == 2)
    {
        auto m1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
        auto m2 = (A[1][0] + A[1][1]) * (B[0][0]);
        auto m3 = (A[0][0]) * (B[0][1] - B[1][1]);
        auto m4 = (A[1][1]) * (B[1][0] - B[0][0]);
        auto m5 = (A[0][0] + A[0][1]) * (B[1][1]);
        auto m6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
        auto m7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
        C[0][0] = m1 + m4 - m5 + m7;
        C[1][0] = m2 + m4;
        C[0][1] = m3 + m5;
        C[1][1] = m1 - m2 + m3 + m6;
    }
    else
    {
        auto a00 = getBlock(A, 0, 0);
        auto a10 = getBlock(A, 1, 0);
        auto a01 = getBlock(A, 0, 1);
        auto a11 = getBlock(A, 1, 1);

        auto b00 = getBlock(B, 0, 0);
        auto b10 = getBlock(B, 1, 0);
        auto b01 = getBlock(B, 0, 1);
        auto b11 = getBlock(B, 1, 1);

        auto m1 = strassen_mm(add(a00, a11), add(b00, b11));
        auto m2 = strassen_mm(add(a10, a11), b00);
        auto m3 = strassen_mm(a00, sub(b01, b11));
        auto m4 = strassen_mm(a11, sub(b10, b00));
        auto m5 = strassen_mm(add(a00, a01), b11);
        auto m6 = strassen_mm(sub(a10, a00), add(b00, b01));
        auto m7 = strassen_mm(sub(a01, a11), add(b10, b11));

        auto c00 = add(add(m1, m4),sub(m7, m5));
        auto c01 = add(m3, m5);
        auto c10 = add(m2, m4);
        auto c11 = add(sub(m1, m2), add(m3, m6));

        writeBlock(C, c00, 0, 0);
        writeBlock(C, c01, 0, 1);
        writeBlock(C, c10, 1, 0);
        writeBlock(C, c11, 1, 1);
    }
    return C;
}

template std::vector<std::vector<int>> add(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B);
template std::vector<std::vector<float>> add(const std::vector<std::vector<float>> &A, const std::vector<std::vector<float>> &B);
template std::vector<std::vector<double>> add(const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B);

template std::vector<std::vector<int>> sub(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B);
template std::vector<std::vector<float>> sub(const std::vector<std::vector<float>> &A, const std::vector<std::vector<float>> &B);
template std::vector<std::vector<double>> sub(const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B);

template std::vector<std::vector<int>> getBlock(const std::vector<std::vector<int>> &A, const int a, const int b);
template std::vector<std::vector<float>> getBlock(const std::vector<std::vector<float>> &A, const int a, const int b);
template std::vector<std::vector<double>> getBlock(const std::vector<std::vector<double>> &A, const int a, const int b);

template void writeBlock(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, const int a, const int b);
template void writeBlock(std::vector<std::vector<float>> &A, std::vector<std::vector<float>> &B, const int a, const int b);
template void writeBlock(std::vector<std::vector<double>> &A, std::vector<std::vector<double>> &B, const int a, const int b);

template std::vector<std::vector<int>> strassen_mm(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B);
template std::vector<std::vector<float>> strassen_mm(const std::vector<std::vector<float>> &A, const std::vector<std::vector<float>> &B);
template std::vector<std::vector<double>> strassen_mm(const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B);
