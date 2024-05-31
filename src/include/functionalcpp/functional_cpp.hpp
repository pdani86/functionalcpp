#include <functional>

#include <iostream> // TODO: remove

namespace functionalcpp {

    template<typename IN, typename OUT>
    class Function {
    public:
        using ProcessFunction = std::function<OUT(IN)>;

        explicit Function(Function<IN,OUT>::ProcessFunction func) : _processFunc(std::move(func)) {}

        // Overload the pipe operator to chain processing steps
        template<typename NewOut>
        Function<IN, NewOut> operator|(typename Function<OUT, NewOut>::ProcessFunction nextFunc) const {
            return Function<IN, NewOut>([this, nextFunc](IN input) {
                return nextFunc(_processFunc(input));
            });
        }

        // Apply the processing function to the data
        OUT operator()(IN input) const {
            return _processFunc(input);
        }

    private:
        ProcessFunction _processFunc{};
    };

}
