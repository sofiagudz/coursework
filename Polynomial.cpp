#include "Polynomial.h"

using namespace std;


void Polynomial::parse_polynomial(const std::string& polynomial_str) {
    vector<string> tokens = tokenize(polynomial_str);
    double coeff = 0;
    int degree = 0;
    bool sign = true;

    for(int i = 0; i < tokens.size(); i++){
        string token = tokens[i];
        if(token == "+"){
            sign = true;
        }
        else if(token == "-"){
            sign = false;
        }
        else if(token == "x"){
            coeff = sign ? 1 : -1;
            degree = 1;
        }
        else if(token == "^"){
            degree = stoi(tokens[i+1]);
            i++;
        }
        else{
            coeff = stod(token);
            if(!sign) coeff = -coeff;
            if(token.find('x') != string::npos){
                degree = 1;
            }
            else{
                degree = 0;
            }
        }
        if(i == tokens.size() - 1 || tokens[i+1] == "+" || tokens[i+1] == "-"){
            if(coeff != 0) {
                Term t(coeff, degree);
                terms.push_back(t);
            }
            else{
                coeff = 0;
                degree = 0;
            }
        }
    }
}

std::vector<std::string> Polynomial::tokenize(const std::string& polynomial_str) {
    std::vector<std::string> tokens;
    std::string token;

    for (char c : polynomial_str) {
        if (c == ' ' || c == '^' || c == '+' || c == '-') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            if (c != ' ') {
                tokens.emplace_back(1, c);
            }
        } else {
            token += c;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

double Polynomial::solve(const double x){
    double result = 0.0;
    for(Term term : terms){
        result += term.coeff * pow(x, term.degree);
    }
    return result;
}

Polynomial Polynomial::deriverate(){
    vector<Term> deriv_terms;

    for(Term term : terms){
        if(term.degree != 0){
            deriv_terms.push_back(Term((term.coeff * term.degree), term.degree - 1));
        }
    }
    return {deriv_terms};
}

bool Polynomial::is_root_in_interval(double& x1, double& x2){
    double x0 = x2;
    x2 = x1 + 1;

    while(x1 <= x0){
        if((solve(x1) * solve(x2)) < 0 || solve(x1) == 0){
            return true;
        }
        x1++;
        x2++;
    }
    return false;
}

std::string remove_trailing_zeros(double value) {
    if (value == 0.0) {
        return "0";
    }

    std::ostringstream oss;
    oss << std::fixed << value;
    std::string str = oss.str();

    if (str.find('.') != std::string::npos) {
        str.erase(str.find_last_not_of('0') + 1, std::string::npos);

        if (str.back() == '.')
            str.pop_back();
    }

    return str;
}

std::string Polynomial::to_str() {
    std::string result;

    for(const Term& term : terms){
        result += (term.coeff > 0) ? " + " : " - ";

        if(fabs(term.coeff) != 1){
            result += remove_trailing_zeros(fabs(term.coeff));
        }

        if(term.degree != 0){
            result += "x";
            if(term.degree != 1){
                result += "^" + std::to_string(term.degree);
            }
        }
        if(fabs(term.coeff) == 1 && term.degree == 0){
            result += "1";
        }
    }
    if(result[1] == '+') result.erase(0, 3);
    else result.erase(0, 1);

    return result;
}

void Polynomial::reduse_same_degree_terms() {
    std::vector<Term> reducedTerms;
    std::vector<int> degrees;

    for (const Term& term : terms) {
        if (std::find(degrees.begin(), degrees.end(), term.degree) == degrees.end()) {
            degrees.push_back(term.degree);
            reducedTerms.push_back(term);
        } else {
            for (Term& reducedTerm : reducedTerms) {
                if (reducedTerm.degree == term.degree) {
                    reducedTerm.coeff += term.coeff;
                    break;
                }
            }
        }
    }

    bool isZeroPolynomial = true;
    for (const Term& term : reducedTerms) {
        if (term.coeff != 0) {
            isZeroPolynomial = false;
            break;
        }
    }

    if (isZeroPolynomial) {
        throw std::invalid_argument("Поліном є нульовим");
    }
}

void Polynomial::sort_terms() {
    std::sort(terms.begin(), terms.end(), [](const Term& a, const Term& b) {
        return a.degree > b.degree;
    });
}

bool Polynomial::validate_polynomial(const std::string& expression) {
    std::regex pattern("^[+-]?\\s*(([0-9]*\\.?[0-9]+)?x(\\^[0-9]+)?|([0-9]*\\.?[0-9]+)?)(\\s*[+-]\\s*(([0-9]*\\.?[0-9]+)?x(\\^[0-9]+)?|([0-9]*\\.?[0-9]+)?))*\\s*$");

    return std::regex_match(expression, pattern);
}
