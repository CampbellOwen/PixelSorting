#include <random>
#include <iostream>

int main()
{
    std::random_device rd;
    auto eng = std::mt19937(rd());
    std::uniform_int_distribution<> distr(0, 10000);
    std::cout << distr(eng) << std::endl;
}