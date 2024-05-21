#include "newthonmethod.h"

NewthonMethod::NewthonMethod(Polynomial& p, double x0, double e) : AbstractMethod(p, e), deriv_p(p.deriverate()), x0(x0) {find_root();}

double NewthonMethod::find_root() {

    double x1 = x0 - p.solve(x0) / deriv_p.solve(x0);

    while(fabs(x1 - x0) >= e && iterations.size() < 75){
        iterations.push_back(NewthonIteration(x0, x1, p.solve(x0), deriv_p.solve(x0)));

        x0 = x1;
        x1 = x0 - p.solve(x0) / deriv_p.solve(x0);
    }
    result = x1;
    return x1;
}

std::string NewthonMethod::print_iterations()
{
    std::string result;
    result += "Рівняння:\n" + p.to_str() + " = 0\n";

    if (!std::isfinite(this->result)) {
        result += "Корінь рівняння є недійсним або мінус безкінечністю\n\n";
    }
    else if((iterations.size() == 75)){
        result += "\nКорінь рівняння не знайдено за 75 операцій\n";
    }
    else {
        result += "Корінь рівняння = " + remove_trailing_zeros(this->result) + "\n\n";
    }

    for(int i = 0; i< iterations.size(); i++){
        result += "Ітерація " + std::to_string(i+1) + ":\n";
        result += "f(x" + std::to_string(i) + ") = f(" + remove_trailing_zeros(iterations[i].x0) + ") = " + remove_trailing_zeros(iterations[i].fx) + "\n";
        result += "f'(x" + std::to_string(i) + ") = f'(" + remove_trailing_zeros(iterations[i].x0) + ") = " + remove_trailing_zeros(iterations[i].fx_det) + "\n";
        result += "x" + std::to_string(i+1) + " = x" + std::to_string(i) + " - f(x" + std::to_string(i) + ") / f'(x" + std::to_string(i) + ") = ";
        result += remove_trailing_zeros(iterations[i].x0) + " - (" + remove_trailing_zeros(iterations[i].fx) + " / " + ((iterations[i].fx_det > 0) ? (remove_trailing_zeros(iterations[i].fx_det)) : ("(" + remove_trailing_zeros(iterations[i].fx_det) + ")")) + ") = " + remove_trailing_zeros(iterations[i].x1) + "\n\n";
    }
    return result;
}
