#include "BisectionMethod.h"

BisectionMethod::BisectionMethod(Polynomial& p, double x1, double x2, double e) : AbstractMethod(p, e), x1(x1), x2(x2) {find_root();};
double BisectionMethod::find_root(){
    if(!p.is_root_in_interval(x1, x2)){
        throw std::invalid_argument("На проміжку немає коренів рівняння");
    }

    double x3 = x1;

    if(p.solve(x1) == 0){ this->result = x1; iterations.push_back(BisectionIteration(x1, p.solve(x1), x2, p.solve(x2), x3, p.solve(x3))); return x1;}
    if(p.solve(x2) == 0){this->result = x2; iterations.push_back(BisectionIteration(x1, p.solve(x1), x2, p.solve(x2), x3, p.solve(x3))); return x2;}

    while((x2 - x1) >= e){
        x3 = (x1 + x2) / 2;

        iterations.push_back(BisectionIteration(x1, p.solve(x1), x2, p.solve(x2), x3, p.solve(x3)));

        if(p.solve(x3) == 0.0){
            break;
        }
        else if((p.solve(x3) * p.solve(x1)) < 0){
            x2 = x3;
        }
        else{
            x1 = x3;
        }
    }
    this->result = x3;
    return x3;
}

std::string BisectionMethod::print_iterations(){
    std::string result;
    result += "Рівняння:\n" + p.to_str() + " = 0" + "\nКорінь лежить між " + remove_trailing_zeros(iterations[0].a) + " та " + remove_trailing_zeros(iterations[0].b) + "\nКорінь рівння = " + remove_trailing_zeros(this->result) + "\n\n";
    if(iterations.size()  == 1){ return result;}

    for(int i = 0; i< iterations.size(); i++){
        result += "Ітерація " + std::to_string(i+1) + ":\n";
        result += "x" + std::to_string(i) + "= (" + remove_trailing_zeros(iterations[i].a) + " + " + ((iterations[i].b > 0) ? remove_trailing_zeros(iterations[i].b) : "(" + remove_trailing_zeros(iterations[i].b) + ")") + ") / 2\n";
        result += "f(x" + std::to_string(i) + ") = " + "f(" + remove_trailing_zeros(iterations[i].c) + ") = " + remove_trailing_zeros(iterations[i].fc) + "\n\n";
    }
    return result;
}
