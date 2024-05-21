#include "InputValidator.h"

InputValidator::InputValidator(const QString& polynomialInput, const QString& x1Input, const QString& x2Input, const QString& x0Input, const QString& eInput, int methodIndex)
    : polynomialInput(polynomialInput), x1Input(x1Input), x2Input(x2Input), x0Input(x0Input), eInput(eInput), methodIndex(methodIndex)
{
    isInputEmpty();
    validateInput();
}

void InputValidator::isInputEmpty()
{
    /*if (methodIndex != 1)
    {
        if (eInput.isEmpty() || x1Input.isEmpty() || x2Input.isEmpty() || polynomialInput.isEmpty())
        {
            throw std::invalid_argument("Всі поля повинні бути заповнені");
        }
    }
    else
    {
        if (eInput.isEmpty() || x0Input.isEmpty() || polynomialInput.isEmpty())
        {
            throw std::invalid_argument("Всі поля повинні бути заповнені");
        }
    }*/
    if(methodIndex != 1){
        if(polynomialInput.isEmpty()){
            throw std::invalid_argument("Введіть функцію");
        }
        else{
            if((!eInput.isEmpty() || !x1Input.isEmpty() || !x2Input.isEmpty()) && (eInput.isEmpty() || x1Input.isEmpty() || x2Input.isEmpty())){
                throw std::invalid_argument("Всі поля повинні бути заповнені");
            }
        }
    }
    else{
        if(polynomialInput.isEmpty()){
            throw std::invalid_argument("Введіть функцію");
        }
        if ((!eInput.isEmpty() || !x0Input.isEmpty()) && (eInput.isEmpty() || x0Input.isEmpty()))
        {
            throw std::invalid_argument("Всі поля повинні бути заповнені");
        }
    }
}

void InputValidator::validateInput()
{
    try
    {
        std::stod(polynomialInput.toStdString());
        throw std::invalid_argument("Функція не повинна бути числом");
    }
    catch (std::invalid_argument&)
    {
    }

    double x1 = x1Input.toDouble();
    double x2 = x2Input.toDouble();
    double x0 = x0Input.toDouble();
    double e = eInput.toDouble();

    if (methodIndex != 1)
    {
        if ((x1 >= x2) && (!x1Input.isEmpty() && !x2Input.isEmpty()))
        {
            throw std::invalid_argument("x1 повинен бути меншим ніж x2");
        }
        //if (std::abs(x1) > 100 || std::abs(x2) > 100)
        if(x2 - x1 > 200)
        {
            throw std::invalid_argument("Проміжое перевищує максимально дозволений (200)");
        }
    }

    /*if (e == 0)
    {
        throw std::invalid_argument("Точність не повинна дорівнювати 0");
    }*/
    /*if (e < 0.00000001)
    {
        throw std::invalid_argument("Максимальна точність - 8 знаків");
    }*/
}
