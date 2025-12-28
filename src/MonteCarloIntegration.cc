#include "MonteCarloIntegration.hh"
#include "MathFunction.hh"

#include <iostream>
#include <cmath>
#include <random>

namespace{
    const int DEFAULT_NUM_SAMPLES = 250;
    std::default_random_engine random_generator;
}

MonteCarloIntegration::MonteCarloIntegration(MathFunction<double>& f) : m_f(f),
    m_NumSamples(DEFAULT_NUM_SAMPLES)
{}

MonteCarloIntegration::MonteCarloIntegration(MathFunction<double>& f, int num_samples)
    : m_f(f), m_NumSamples(num_samples)
{}

MonteCarloIntegration::MonteCarloIntegration(const MonteCarloIntegration& p)
    : m_f(p.m_f),
    m_NumSamples(p.m_NumSamples)
{}

MonteCarloIntegration::~MonteCarloIntegration() {}

MonteCarloIntegration& MonteCarloIntegration::operator=(const MonteCarloIntegration& p)
{
    if(this != &p)
    {
        m_f = p.m_f;
        m_NumSamples = p.m_NumSamples;
    }
    return *this;
}

void MonteCarloIntegration::SetNumSamples(int n) {m_NumSamples = n;}

double MonteCarloIntegration::IntegralRegion(double a, double b, double min, double max)
{
    std::uniform_real_distribution<> xdist(a,b);
    std::uniform_real_distribution<> ydist(min, max);

    int points_in = 0;
    int points_out = 0;

    bool positive = max > 0;

    for(int i = 0; i < m_NumSamples; ++i)
    {
        double x = xdist(random_generator);
        double y = m_f(x);

        double ry = ydist(random_generator);

        if(positive && min <= ry && ry <= y)
        {
            points_in += 1;
        }
        else if(!positive && y <= ry && ry <= max)
        {
            points_in += 1;
        }
        else{
            points_out += 1;
        }
    }

    double per_cent_area = 0;
    if(points_in + points_out > 0)
    {
        per_cent_area = points_in/double(points_in + points_out);
    }

    if(per_cent_area > 0.0)
    {
        return (b-a)*(max - min)*per_cent_area;
    }

    return 0; 
}

double MonteCarloIntegration::GetIntegral(double a, double b)
{
    std::uniform_real_distribution<> dist(a,b);

    double max = 0;
    double min = 0;

    for(int i = 0; i < m_NumSamples; ++i)
    {
        double x = dist(random_generator);
        double y = m_f(x);

        if(y > max) max = y;
        if(y < min) min = y;
    }

    double pos_int = max > 0 ? IntegralRegion(a,b,0,max) : 0;
    double neg_int = min < 0 ? IntegralRegion(a,b,min,0) : 0;

    return pos_int - neg_int;
}
