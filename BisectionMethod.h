#ifndef BISEVTIONMETHOD_H
#define BISEVTIONMETHOD_H

#include "abstractmethod.h"

class BisectionMethod : AbstractMethod
{
    struct BisectionIteration{
        double a;
        double fa;
        double b;
        double fb;
        double c;
        double fc;
        BisectionIteration(double a, double fa, double b, double fb, double c, double fc) : a(a), fa(fa), b(b), fb(fb), c(c), fc(fc) {};
    };

    std::vector<BisectionIteration> iterations;

    double x1, x2;

    double find_root() override;

public:
    BisectionMethod(Polynomial&, double, double, double);

    std::string print_iterations() override;
};

#endif // BISEVTIONMETHOD_H

