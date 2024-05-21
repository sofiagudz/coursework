#ifndef NEWTHONMETHOD_H
#define NEWTHONMETHOD_H
#include "abstractmethod.h"

class NewthonMethod : public AbstractMethod
{
    struct NewthonIteration{
        double x0;
        double x1;
        double fx;
        double fx_det;

        NewthonIteration(double x0, double x1, double fx, double fx_det) : x0(x0), x1(x1), fx(fx), fx_det(fx_det) {};
    };

    Polynomial deriv_p;

    std::vector<NewthonIteration> iterations;

    double x0;

    double find_root() override;

public:
    NewthonMethod(Polynomial&, double, double);

    std::string print_iterations() override;
};

#endif // NEWTHONMETHOD_H
