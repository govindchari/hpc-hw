#include <iostream>
#include <cassert>

#include "refBLAS.hpp"

int main()
{

    // Test daxpy
    double ad = 2;
    std::vector<double> xd = {1, 2};
    std::vector<double> yd = {3, 4};
    std::vector<double> exp_daxpy = {5, 8};
    daxpy(ad, xd, yd);
    assert(yd == exp_daxpy);

    // Test daxpy_unroll
    std::vector<double> xu = {1, 2, 3, 4, 5, 6, 7, 8, 1};
    std::vector<double> yu = {9, 10, 11, 12, 13, 14, 15, 16, 1};
    std::vector<double> exp_daxpy_unroll = {11, 14, 17, 20, 23, 26, 29, 32, 3};
    daxpy_unroll(ad, xu, yu, 8);
    assert(yu == exp_daxpy_unroll);

    // Test dgemv
    double bd = 3;
    yd = {3, 4};
    std::vector<std::vector<double>> Ad = {{1, 2}, {3, 4}};
    std::vector<double> exp_dgemv = {19, 34};
    dgemv(ad, Ad, xd, bd, yd);
    assert(yd == exp_dgemv);

    // Test dgemm
    std::vector<std::vector<double>> Bd = {{5, 6}, {7, 8}};
    std::vector<std::vector<double>> Cd = {{9, 10}, {11, 12}};
    std::vector<std::vector<double>> exp_dgemm = {{65, 74}, {119, 136}};
    dgemm(ad, Ad, Bd, bd, Cd);
    assert(Cd == exp_dgemm);

    // Test axpy
    float af = 2;
    std::vector<float> xf = {1, 2};
    std::vector<float> yf = {3, 4};
    std::vector<float> exp_axpy = {5, 8};
    axpy(af, xf, yf);
    assert(yf == exp_axpy);

    // Test gemv
    float bf = 3;
    yf = {3, 4};
    std::vector<std::vector<float>> Af = {{1, 2}, {3, 4}};
    std::vector<float> exp_gemv = {19, 34};
    gemv(af, Af, xf, bf, yf);
    assert(yf == exp_gemv);

    // Test gemm
    std::vector<std::vector<float>> Bf = {{5, 6}, {7, 8}};
    std::vector<std::vector<float>> Cf = {{9, 10}, {11, 12}};
    std::vector<std::vector<float>> exp_gemm = {{65, 74}, {119, 136}};
    gemm(af, Af, Bf, bf, Cf);
    assert(Cf == exp_gemm);
}