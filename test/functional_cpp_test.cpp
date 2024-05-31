#include "functionalcpp/functional_cpp.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator> // Include for std::back_inserter
#include <utility>

#include <queue>

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

class MinusOne {
public:
    MinusOne() = default;

    std::vector<int> operator()(std::vector<int> in) {
        std::vector<int> out = std::move(in);
        std::transform(out.begin(), out.end(), out.begin(), [](int num) {return num - 1;});
        return out;
    }
private:
//    std::unique_ptr<int> _no_copy;
};


struct Sum {
    int operator()(std::vector<int> in) {
        return std::accumulate(in.begin(), in.end(), 0);
    }
};


std::vector<int> scalar_to_vec(int in) {
    return {in};
}


/*
void test0() {
    using namespace functionalcpp;
    std::vector<int> numbers = {1, -2, 3, -4, 5};
    auto pipeline = Processor<std::vector<int>, std::vector<int>>(filterPositive) |
                    Processor<std::vector<int>, std::vector<int>>(square) |
                    Processor<std::vector<int>, void>(print);
    pipeline(numbers);
    pipeline({6, -7, 8, -9, 10});
}
*/

struct Queue {
    std::deque<int> _queue;
};

struct QueueWrapper {
    QueueWrapper() {
        _pQueue = std::make_shared<Queue>();
    }

    std::vector<int> operator()(std::vector<int> in) {
        std::for_each(in.begin(), in.end(),[&_queue=_pQueue->_queue] (auto val) mutable {_queue.push_back(val);});
        return std::move(in);
    }

    void print() {
        auto& _queue = _pQueue->_queue;
        std::for_each(_queue.begin(), _queue.end(), [](int val) {std::cout << val << ", ";});
        std::cout << std::endl;
    }
    std::shared_ptr<Queue> _pQueue;
};


void test1() {
    using namespace functionalcpp;
    using IntVec = std::vector<int>;
    IntVec numbers = {1, -2, 3, -4, 5};
    using ProcIntVec = Processor<IntVec, IntVec>;
    auto summer = Processor<IntVec, int>(Sum());
    auto filter = ProcIntVec(filterPositive);
    auto square_er = ProcIntVec(square);
    auto printer = Processor<std::vector<int>, void>(print);
    auto minusOne = ProcIntVec(MinusOne());

    auto queue = QueueWrapper();
    auto queueProc = ProcIntVec(queue);

    auto pipeline = filter | square_er | minusOne | queueProc;
    auto pipelineWithPrint = pipeline | printer;
    auto pipelineWithSumAndPrint = pipeline | summer | Processor<int, IntVec>(scalar_to_vec) | printer;

    pipelineWithPrint(numbers);
    pipelineWithSumAndPrint(numbers);
    queue.print();
    pipelineWithPrint({6, -7, 8, -9, 10});
    pipelineWithSumAndPrint({6, -7, 8, -9, 10});
    queue.print();
}

int main() {
//    test0();
    test1();

    return 0;
}
