#include "SecantMethod.h"
#include <QDebug>

SecantMethod::SecantMethod(Polynomial& p, double x1, double x2, double e) : AbstractMethod(p, e), x1(x1), x2(x2) {find_root();}
double SecantMethod::find_root() {
    if(!p.is_root_in_interval(x1, x2)){
        throw std::invalid_argument("На проміжку немає коренів рівняння");
    }

    if(p.solve(x1) == 0){ this->result = x1; iterations.push_back(SecantIteration(x1, p.solve(x1), x2, p.solve(x2), x1, p.solve(x1))); return x1;}
    if(p.solve(x2) == 0){this->result = x2; iterations.push_back(SecantIteration(x1, p.solve(x1), x2, p.solve(x2), x2, p.solve(x2))); return x2;}

    double x3 = x2 - p.solve(x2) * (x2 - x1) / (p.solve(x2) - p.solve(x1));
    qDebug() << "x3 = " << x3;
    while(fabs(x3 - x2) > e){
        qDebug () << "1 ";
        iterations.push_back(SecantIteration(x1, p.solve(x1), x2, p.solve(x2), x3, p.solve(x3)));
        qDebug () << "x1 =" << x1 << "x2 =" << x2 << "x3 =" << x3;

        x1 = x2;
        x2 = x3;
        x3 = x2 - p.solve(x2) * (x2 - x1) / (p.solve(x2) - p.solve(x1));
    }
    this->result = x3;
    return x3;
}

std::string SecantMethod::print_iterations()
{
    std::string result;
    result += "Рівняння:\n" + p.to_str() + " = 0" + "\nКорінь лежить між " + remove_trailing_zeros(iterations[0].x1) + " та " + remove_trailing_zeros(iterations[0].x2) + "\nКорінь рівння = " + remove_trailing_zeros(this->result) + "\n\n";
    if(iterations.size()  == 1){ return result;}

    for(int i = 0; i< iterations.size(); i++){
        result += "Ітерація " + std::to_string(i+1) + ":\n";
        result += "x" + std::to_string(i) + " = " + remove_trailing_zeros(iterations[i].x1) + " та x" + std::to_string(i+1) + " = " + remove_trailing_zeros(iterations[i].x2) + "\n";
        result += "f(x" +  std::to_string(i) + ") = " + "f(" + remove_trailing_zeros(iterations[i].x1) + ") = " + remove_trailing_zeros(iterations[i].fx1) + " та f(x" +  std::to_string(i+1) + ") = f(" + remove_trailing_zeros(iterations[i].x2) + ") = " + remove_trailing_zeros(iterations[i].fx2) + "\n";
        result += "x" + std::to_string(i+2) + " = x" + std::to_string(i) + " - f(x" + std::to_string(i) + ") * " "((x" + std::to_string(i+1) + " - x" + std::to_string(i) + ") / (f(x" + std::to_string(i+1) + ") - f(x" + std::to_string(i) + "))" + "\n";
        result += "x" + std::to_string(i+2) + " = " + remove_trailing_zeros(iterations[i].x1) + " - " + (((iterations[i].fx1) > 0) ? remove_trailing_zeros(iterations[i].fx1) : "(" + remove_trailing_zeros(iterations[i].fx1) + ")") + " * ((" + remove_trailing_zeros(iterations[i].x2) + " - " + (((iterations[i].x1 > 0) ? remove_trailing_zeros(iterations[i].x1) : "(" + remove_trailing_zeros(iterations[i].x1) + ")")) + ") / (" + remove_trailing_zeros(iterations[i].fx2) + " - " + (((iterations[i].fx1 > 0) ? remove_trailing_zeros(iterations[i].fx1) : "(" + remove_trailing_zeros(iterations[i].fx1) + ")")) + "))\n";
        result += "x" + std::to_string(i+2) + " = " + remove_trailing_zeros(iterations[i].x3) + "\n";
        result += "f(x" + std::to_string(i+2) + ") = f(" + remove_trailing_zeros(iterations[i].x3) + ") = " + remove_trailing_zeros(iterations[i].fx3) + "\n\n";
    }
    return result;
}
