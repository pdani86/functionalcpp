/*
#include "functionalcpp/functional_cpp.hpp"

#include <algorithm>

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
//
//void test0() {
//    using namespace functionalcpp;
//    // Sample data
//    std::vector<int> numbers = {1, -2, 3, -4, 5};
//
//    // Define the processing pipeline
//    auto pipeline = Function<std::vector<int>, std::vector<int>>(filterPositive) |
//                    square |
//                    [](const std::vector<int>& data) {
//                        print(data);
//                        return data;  // For the sake of type consistency
//                    };
//
//    // Execute the pipeline
//    pipeline(numbers);
//}


void test1() {
    using namespace functionalcpp;
    // Sample data
    std::vector<int> numbers = {1, -2, 3, -4, 5};

    auto func = Function<std::vector<int>, std::vector<int>>(filterPositive);
    print(func(numbers));
    auto func2 = func | Function<std::vector<int>, std::vector<int>>(square);
//    func2(numbers);
//    auto pipeline =  |
//                    square |
//                    [](const std::vector<int>& data) {
//                        print(data);
//                        return data;  // For the sake of type consistency
//                    };
}

int main() {
//    test0();
    test1();

	return 0;
}
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator> // Include for std::back_inserter
#include <utility>

// Define a generic function type for processing steps
template<typename In, typename Out>
using ProcessFunction = std::function<Out(In)>;

// Define a processing component that applies a function to a vector
template<typename In, typename Out>
class Processor {
private:
public:
    ProcessFunction<In, Out> processFunc;

public:
    explicit Processor(ProcessFunction<In, Out> func) : processFunc(std::move(func)) {}

    // Overload the pipe operator to chain processing steps
    template<typename NewOut>
    Processor<In, NewOut> operator|(Processor<Out, NewOut> nextProcessor) const {
        return Processor<In, NewOut>([first = this->processFunc, second = nextProcessor.processFunc](In input) {
            return second(first(input));
        });
    }

    // Apply the processing function to the data
    Out operator()(In input) const {
        return processFunc(std::move(input));
    }
};

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

int main() {
    // Sample data
    std::vector<int> numbers = {1, -2, 3, -4, 5};

    // Define the processing pipeline
    auto pipeline = Processor<std::vector<int>, std::vector<int>>(filterPositive) |
                    Processor<std::vector<int>, std::vector<int>>(square) |
                    Processor<std::vector<int>, void>(print);

    // Execute the pipeline multiple times
    pipeline(numbers);
    pipeline({6, -7, 8, -9, 10});

    return 0;
}