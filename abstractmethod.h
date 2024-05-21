#ifndef ABSTRACTMETHOD_H
#define ABSTRACTMETHOD_H

#include "Polynomial.h"

class AbstractMethod {
protected:
    Polynomial& p;
    double e, result;

    virtual double find_root() = 0;
public:
    AbstractMethod(Polynomial& p, double e);
    virtual ~AbstractMethod() {}

    virtual std::string print_iterations() = 0;

    virtual double get_result() {return result;};
};

#endif // ABSTRACTMETHOD_H
