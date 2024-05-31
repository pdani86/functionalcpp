
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

int main() {
    using namespace functionalcpp;
    // Sample data
    std::vector<int> numbers = {1, -2, 3, -4, 5};

    // Define the processing pipeline
    auto pipeline = Function<std::vector<int>, std::vector<int>>(filterPositive) |
                    square |
                    [](const std::vector<int>& data) {
                        print(data);
                        return data;  // For the sake of type consistency
                    };

    // Execute the pipeline
    pipeline(numbers);
	return 0;
}