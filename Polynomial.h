#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <regex>

class Polynomial {
private:

    struct Term{
        double coeff;
        int degree;

        Term(double coeff, int degree) : coeff(coeff), degree(degree) {};
    };

    std::vector<Term> terms;

    static std::vector<std::string> tokenize(const std::string& polynomial_str);

    void parse_polynomial(const std::string& polynomial_str);

    void reduse_same_degree_terms();

    void sort_terms();

    static bool validate_polynomial(const std::string&);

public:

    explicit Polynomial(const std::string& polynomial_str) {
        if(!validate_polynomial(polynomial_str)) throw std::invalid_argument("Невірно введена функція");
        else {parse_polynomial(polynomial_str); reduse_same_degree_terms(); sort_terms();}
    }

    Polynomial(const std::vector<Term> terms) : terms(terms) {};

    Polynomial deriverate();

    double solve(double x);

    bool is_root_in_interval(double& x1, double& x2);

    std::string to_str();

    std::vector<Term> get_terms() {return terms;}
};

std::string remove_trailing_zeros(double value);


#endif // POLYNOMIAL_H
