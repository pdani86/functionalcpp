#include "functionalcpp/functional_cpp.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator> // Include for std::back_inserter
#include <utility>

// Define some example processing functions
std::vector<int> filterPositive(const std::vector<int>& data) {
    std::vector<int> result;
    std::copy_if(data.begin(), data.end(), std::back_inserter(result), [](int x) { return x > 0; });
    return result;
}

std::vector<int> square(const std::vector<int>& data) {
    std::vector<int> result(data.size());
    std::transform(data.begin(), data.end(), result.begin(), [](int x) { return x * x; });
    return result;
}

void print(const std::vector<int>& data) {
    std::cout << "Result: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}


void test0() {
    using namespace functionalcpp;
    std::vector<int> numbers = {1, -2, 3, -4, 5};
    auto pipeline = Processor<std::vector<int>, std::vector<int>>(filterPositive) |
                    Processor<std::vector<int>, std::vector<int>>(square) |
                    Processor<std::vector<int>, void>(print);
    pipeline(numbers);
    pipeline({6, -7, 8, -9, 10});
}

void test1() {
    using namespace functionalcpp;
    std::vector<int> numbers = {1, -2, 3, -4, 5};
    auto filter = Processor<std::vector<int>, std::vector<int>>(filterPositive);
    auto square_er = Processor<std::vector<int>, std::vector<int>>(square);
    auto printer = Processor<std::vector<int>, void>(print);
    auto pipeline = filter | square_er | printer ;
    pipeline(numbers);
    pipeline({6, -7, 8, -9, 10});
}

int main() {
    test0();
    test1();

    return 0;
}
