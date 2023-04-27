#include "hw3_p1_header.hpp"
#include <iostream>
#include <cassert>

// Tests Correctness of all permuted loops
int main()
{
    std::vector<double> A = {1, 2, 3, 4};
    std::vector<double> B = {5, 6, 7, 8};
    std::vector<double> C = {9, 10, 11, 12};
    std::vector<double> expres = {50, 64, 64, 82};
    double a = 1;
    double b = 3;

    mm_ijk(a, A, B, b, C, 2, 2, 2);
    assert(C == expres);

    C = {9, 10, 11, 12};

    mm_ikj(a, A, B, b, C, 2, 2, 2);
    assert(C == expres);

    C = {9, 10, 11, 12};

    mm_jik(a, A, B, b, C, 2, 2, 2);
    assert(C == expres);

    C = {9, 10, 11, 12};

    mm_kij(a, A, B, b, C, 2, 2, 2);
    assert(C == expres);

    C = {9, 10, 11, 12};

    mm_jki(a, A, B, b, C, 2, 2, 2);
    assert(C == expres);

    C = {9, 10, 11, 12};

    mm_kji(a, A, B, b, C, 2, 2, 2);
    assert(C == expres);

    // for (auto x : C)
    // {
    //     std::cout << x << std::endl;
    // }
}