#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <QString>

class InputValidator
{
public:
    InputValidator(const QString& polynomialInput, const QString& x1Input, const QString& x2Input, const QString& x0Input, const QString& eInput, int methodIndex);

private:
    void isInputEmpty();
    void validateInput();
    bool is_empty;

private:
    QString polynomialInput;
    QString x1Input;
    QString x2Input;
    QString x0Input;
    QString eInput;
    int methodIndex;
};

#endif // INPUTVALIDATOR_H
