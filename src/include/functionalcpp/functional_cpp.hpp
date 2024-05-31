
namespace functionalcpp {

    template<typename CURRENT_FUNCTION, typename NEXT_FUNCTION>
    class Function {
    public:
        explicit Function(const CURRENT_FUNCTION& curFunc) : _curFunc(&curFunc) { }
        explicit Function(const CURRENT_FUNCTION& curFunc, const NEXT_FUNCTION& nextFunc) : _curFunc(&curFunc), _nextFunc(&nextFunc) { }

        Function<CURRENT_FUNCTION, NEXT_FUNCTION> operator|(const NEXT_FUNCTION& nextFunc) {
            Function<CURRENT_FUNCTION, NEXT_FUNCTION> function(_curFunc, _nextFunc);
            return function;
        }

        void operator()() {

        }

    private:
        const CURRENT_FUNCTION* _curFunc{};
        const NEXT_FUNCTION* _nextFunc{};
    };

}
