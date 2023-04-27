#pragma once
#include <vector>
#include <stdexcept>

template<typename T>
void mm_ikj(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n);