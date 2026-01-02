#include <iostream>
#include <cmath>
#include <vector>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

//Calculate the mean i.e the integral.
double MCIntegral(const std::vector<double>& y_sample)
{
    double sum = 0.0;
    double N = static_cast<double>(y_sample.size());

    for(double yi : y_sample)
    { 
        sum += yi;
    }

    return sum/N;
}

//Calculate the sample variance of the data. Used for the ConfInterval function.
double VarEstimate(const std::vector<double>& y_sample, double mean)
{
    double N = static_cast<double>(y_sample.size());
    double sum = 0.0;

    for(double yi : y_sample)
    {
        sum += (yi - mean)*(yi- mean);
    }
    return sum/(N-1);
}

std::pair<double, double> ConfInterval(double mean, double S_sq, std::size_t N, double alpha)
{
    double t_r = gsl_cdf_tdist_Q(1 - alpha/2, N - 1);
    double t_l = - t_r;

    return std::make_pair<double, double>(mean + t_l*std::sqrt(S_sq/N), mean + t_r*std::sqrt(S_sq/N));
}

int main()
{
    gsl_rng_env_setup();
    const gsl_rng_type* T = gsl_rng_default;
    gsl_rng* r = gsl_rng_alloc(T);
    std::vector<double> y_sample;

    for(int i = 0; i < 10000; ++i)
    {
        double k = gsl_ran_flat(r, 0.0, 1.0);
        y_sample.push_back(std::cos(k));
    }
    
    double mean = MCIntegral(y_sample);
    double var = VarEstimate(y_sample, mean);
    std::cout << "Integral estimate: " << mean << '\n' << "Var.: " << var << '\n'; 

    auto p = ConfInterval(mean, var, y_sample.size(), 0.05);
    std::cout << "[" <<p.first << ", " << p.second << "] \n";

    gsl_rng_free(r);
}
