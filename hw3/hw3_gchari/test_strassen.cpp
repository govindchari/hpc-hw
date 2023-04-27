#include <iostream>
#include <vector>
#include "strassen.hpp"
using namespace std;

void print(const std::vector<std::vector<double>> A)
{
    for (auto x : A)
    {
        for (auto y : x)
        {
            std::cout << y << " ";
        }
        std::cout << "" << std::endl;
    }
}

int main()
{
    vector<vector<double>> X = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    vector<vector<double>> Y = {{2, 3, 4, 5}, {6, 7, 8, 9}, {10, 11, 12, 13}, {14, 15, 16, 17}};
    vector<vector<double>> exp = {{100, 110, 120, 130}, {228, 254, 280, 306}, {356, 398, 440, 482}, {484, 542, 600, 658}};

    auto c = strassen_mm(X, Y);

    assert(c == exp);
}