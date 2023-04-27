#include <iostream>
#include <cmath>

int main()
{
    int j = 0;
    while (!(1.0f - (1.0f + 1.0f / static_cast<float>(std::pow(2, j))) == 0))
    {
        j++;
    }
    std::cout << "Single Precision macheps is: " << 1.0f / std::pow(2, j) << std::endl;

    int k = 0;
    while (!(1.0 - (1.0 + 1.0 / std::pow(2, k)) == 0))
    {
        k++;
    }
    std::cout << "Double Precision macheps is: " << 1.0 / std::pow(2, k) << std::endl;

    return 0;
}