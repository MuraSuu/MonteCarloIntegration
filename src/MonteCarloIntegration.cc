#include <cstdio>
#include <random>
#include <string>
#include <iostream>

#include "exprtk.hpp"

namespace {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>   expression_t;
    typedef exprtk::parser<double>       parser_t;
    typedef exprtk::parser_error::type   err_t;
}

template<typename T>
struct rand0 final : public exprtk::ifunction<T>
{
    using exprtk::ifunction<T>::operator();

    std::random_device rd; //Distribuição não-deterministica e uniforme de inteiros 
    std::mt19937 gen;
    std::uniform_real_distribution<> d;

    //Nenhum argumento necessario dado que vou usar uma.
    //distribuição uniforme Unif(0,1).
    rand0() : exprtk::ifunction<T>(0), gen(rd()) 
    {
        d = std::uniform_real_distribution<> (0.0, 1.0);
    }

    inline T operator()() override
    {
        return d(gen);
    }
};


int main()
{
    double x = 0.0;
    double S = 0.0;
    symbol_table_t symbol_table;
    symbol_table.add_constants();

    expression_t expression;
    
    std::string user_func;

    std::printf("Ver 1.0\n");
    std::printf("Will only work for single variable functions with \'x\' symbol\n");
    std::printf("f(x) = ");
    std::getline(std::cin, user_func);
    
    std::printf("Now choose the integration limits.\n");
    std::string lower_limit;
    std::printf("a >> ");
    std::getline(std::cin, lower_limit);
    std::string upper_limit;
    std::printf("b >> ");
    std::getline(std::cin, upper_limit);
    std::string num_samples;
    std::printf("Now the number of samples\nN >> ");
    std::getline(std::cin, num_samples);

    //Casting from string to double.
    double b = std::stod(upper_limit);
    double a = std::stod(lower_limit);
    int N = std::stoi(num_samples);

    parser_t parser;

    rand0<double> rand01;
    
    std::printf("Integration from a:%.4f to b: %.4f with %d samples\n", a, b, N);
    symbol_table.add_variable("x", x);

    expression.register_symbol_table(symbol_table);
 
    if(!parser.compile(user_func, expression))
    {
        std::printf("Error: %s\n", 
                parser.error().c_str());
        return -1;
    }

    for(int i = 0; i < N; ++i)
    {
        x = a+rand01()*(b-a);
        S += expression.value();
    }

    std::printf("Integral=: %.5f\n", S/N*(b-a));

    return 0;
}
