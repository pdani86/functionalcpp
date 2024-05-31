#include <functional>

#include <iostream> // TODO: remove

namespace functionalcpp {

    template<typename IN, typename OUT>
    class Function {
    public:
        using ProcessFunction = std::function<OUT(IN&)>;

        explicit Function(Function<IN,OUT>::ProcessFunction func) : _processFunc(std::move(func)) {}

        // Overload the pipe operator to chain processing steps
        template<typename NewOut>
        Function<IN, NewOut> operator|(typename Function<OUT, NewOut>::ProcessFunction nextFunc) const {
            return Function<IN, NewOut>([this, nextFunc](IN input) {
                return nextFunc(processFunc(input));
            });
        }

        // Apply the processing function to the data
        OUT operator()(IN& input) const {
            return processFunc(input);
        }

    private:
        ProcessFunction _processFunc{};
    };
/*
    class FunctionExample : public Function<std::function<void()>, std::function<void()>> {
    public:
        FunctionExample() = default;

        void operator()(int x) {
            std::cout << x << std::endl;

        }
        void process(int x) {
            std::cout << x << std::endl;

        }
    private:

    };
    */

}
