//Some kind of functor... C++... bullshit... or something like that.


#ifndef MATHFUNCTION_HH
#define MATHFUNCTION_HH

#include <cmath>
#include <random>

//Abstract type.
template <typename Res>
class MathFunction
{
public:
    MathFunction() = default; //Constructor
    virtual ~MathFunction() = default; //Virtual destructor ?
    virtual Res operator()(Res value) = 0;
};

#endif


