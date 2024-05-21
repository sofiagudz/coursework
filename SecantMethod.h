#ifndef SECANTMETHOD_H
#define SECANTMETHOD_H
#include "abstractmethod.h"

class SecantMethod : AbstractMethod
{
    struct SecantIteration
    {
        double x1;
        double fx1;
        double x2;
        double fx2;
        double x3;
        double fx3;

        SecantIteration(double x1, double fx1, double x2, double fx2, double x3, double fx3) : x1(x1), fx1(fx1), x2(x2), fx2(fx2), x3(x3), fx3(fx3) {};
    };

    double x1, x2;

    std::vector<SecantIteration> iterations;

    double find_root() override;

public:
    SecantMethod(Polynomial&, double, double, double);

    std::string print_iterations() override;
};

#endif // SECANTMETHOD_H
