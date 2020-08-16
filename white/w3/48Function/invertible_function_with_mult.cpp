#include <iostream>
#include <vector>

class Function {
    struct FunctionPart {
        char operation;
        double value;

        double Apply(double v) const {
            switch (operation) {
                case '+':
                    return v + value;
                case '-':
                    return v - value;
                case '*':
                    return v * value;
                case '/':
                    return v / value;
            }
            return 0;
        }
        void Invert() {
            if (operation == '+' || operation == '-')
                operation = "+-"[operation == '+'];
            else if (operation == '*' || operation == '/')
                operation = "*/"[operation == '*'];
        }
    };

    std::vector<FunctionPart> parts;
public:
    void AddPart(char op, double value) {
        parts.push_back({op, value});
    }
    double Apply(double value) const {
        for (const auto &p : parts)
            value = p.Apply(value);
        return value;
    }
    void Invert() {
        for (auto &p : parts)
            p.Invert();
        std::reverse(begin(parts), end(parts));
    }
};

Function MakeWeightFunction(const Params& params, const Image& image) {
    Function function;
    function.AddPart('*', params.a);
    function.AddPart('-', image.freshness * params.b);
    function.AddPart('+', image.rating * params.c);
    return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
    Function function = MakeWeightFunction(params, image);
    return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params, const Image& image, double weight) {
    Function function = MakeWeightFunction(params, image);
    function.Invert();
    return function.Apply(weight);
}
