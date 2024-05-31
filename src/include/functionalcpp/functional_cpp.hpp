#include <functional>

namespace functionalcpp {

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

}
