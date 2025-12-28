#ifndef MONTECARLOINTEGRATION_H
#define MONTECARLOINTEGRATION_H

template <class T>
class MathFunction; //But why ? 

class MonteCarloIntegration
{
public:
    MonteCarloIntegration(MathFunction<double> &f); //Copy constructor.
    MonteCarloIntegration(MathFunction<double> &f, int num_samples); //Another copy constructor.
    MonteCarloIntegration(const MonteCarloIntegration& p);
    ~MonteCarloIntegration(); //Destructor.
    MonteCarloIntegration &operator=(const MonteCarloIntegration &p); // Why & ?

    void SetNumSamples(int n);
    double GetIntegral(double a, double b);
    double IntegralRegion(double a, double b, double min, double max);
private:
    MathFunction<double> &m_f;
    int m_NumSamples; //But why m_ ?
};

#endif


