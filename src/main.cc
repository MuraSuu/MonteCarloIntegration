#include "MonteCarloIntegration.hh"
#include "MathFunction.hh"
#include <iostream>

class FCos : public MathFunction<double>
{
public:
    ~FCos();
    double operator()(double x);
};
FCos::~FCos() {}
double FCos::operator()(double x) {return exp(x)/x;}

int main()
{
    std::cout << "Lets go\n";

    FCos f;
    MonteCarloIntegration mci(f);
    mci.SetNumSamples(5000);
    double integral = mci.GetIntegral(-10.0, -100.0);
    std::cout << "Result: " << integral << '\n';

    mci.SetNumSamples(40000);
    integral = mci.GetIntegral(-10.0, -100.0);
    std::cout << "Result with 40'000 samples: " << integral << '\n';

    mci.SetNumSamples(100000);
    integral = mci.GetIntegral(-10.0, -100.0);
    std::cout << "Result with 100'000 samples: " << integral << '\n';
}
