#pragma once
#include <vector>
#include <iostream>
#include <cassert>

template <typename T>
std::vector<std::vector<T>> add(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B);

template <typename T>
std::vector<std::vector<T>> sub(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B);

template <typename T>
std::vector<std::vector<T>> getBlock(const std::vector<std::vector<T>> &A, const int a, const int b);

template <typename T>
void writeBlock(std::vector<std::vector<T>> &A, std::vector<std::vector<T>> &B, const int a, const int b);

template <typename T>
std::vector<std::vector<T>> strassen_mm(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B);
