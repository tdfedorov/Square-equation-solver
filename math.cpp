#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

///Данная константа устанавливает точность сравнения переменных типа double.
const double ACCURACY = 1e-6;

/**
Здесь описаны константы для разных исходов решения уравнения.
Значения не всех констант соответствуют реальному количеству корней.
*/
enum NUMBER_OF_ROOTS
{
    NO_ROOTS, ///< нет корней
    ONE_ROOT, ///< один корень
    TWO_ROOTS, ///< два корня
    TWO_SIMILAR_ROOTS, ///< два одинаковых корня (значение 3)
    INF_ROOTS ///< бесконечное число корней (значение 4)
};

/**Данная функция определяет какое уравнение следует решить: квадратное или линейное
\param coefficients[] - коэффициенты уравнения (индекс в массиве соответствует степени при x)
\param *x1, *x2 - указатели на корни x1 и x2
\return Константу с количеством решений
*/
int solve_equation(double coefficients[], double *x1, double *x2);

/**
Данная функция решает линейное уравнение.
\param coefficients[] - коэффициенты уравнения (индекс в массиве соответствует степени при x)
\param *x1, *x2 - указатели на корни x1 и x2
\return Константу с количеством решений, значениям x1 и x2 присваиваются новые значения
*/
int solve_linear_equation(double coefficients[], double *x1, double *x2);

/**
Данная функция решает квадратное уравнение.
\param coefficients[] - коэффициенты уравнения (индекс в массиве соответствует степени при x)
\param *x1, *x2 - указатели на корни x1 и x2
\return Константу с количеством решений, значениям x1 и x2 присваиваются новые значения
*/
int solve_square_equation(double coefficients[], double *x1, double *x2);

/**
Данная функция восстанавливает значения коэффициента при x и пустого коэффициента с помощью 2 корней и старшего коэффициента.
\param coefficients[] - коэффициенты уравнения (индекс в массиве соответствует степени при x)
\param *x1, *x2 - указатели на корни x1 и x2
\return Константу с количеством решений, значениям coefficients[0] и coefficients[1] присваиваются новые значения
*/
int restore_coefficients(double coefficients[], double x1, double x2);

/**
Данная функция сравнивает число типа double с нулем с точностью до константы ACCURACY.
\param number - сравниваемое с 0 число
\return true если число равно 0 с точностью до ACCURACY, иначе false
*/
bool is_zero(double number);

/**
Данная функция сортирует разные корни так, чтобы x1 был меньшим, а x2 - большим корнем.
\param *x1, *x2 - указатели на корни x1 и x2
*/
void sort_roots(double *x1, double *x2);


int solve_equation(double coefficients[], double *x1, double *x2)
{
    if (is_zero(coefficients[2]))
        return solve_linear_equation(coefficients, x1, x2);
    return solve_square_equation(coefficients, x1, x2);
}

int solve_linear_equation(double coefficients[], double *x1, double *x2)
{
    if (is_zero(coefficients[1]))
    {
        if (is_zero(coefficients[0]))
        {
            *x1 = *x2 = INFINITY;
            return INF_ROOTS;
        }
        else
        {
            *x1 = *x2 = NAN;
            return NO_ROOTS;
        }
    }
    *x1 = (-coefficients[0]) / coefficients[1];
    *x2 = NAN;
    if (is_zero(*x1))
        *x1 = 0;
    return ONE_ROOT;
}

int solve_square_equation(double coefficients[], double *x1, double *x2)
{
    double discriminant = (coefficients[1] * coefficients[1]) - 4 * coefficients[2] * coefficients[0];
    if (is_zero(discriminant))
    {
        *x1 = *x2 = (-coefficients[1]) / (2 * coefficients[2]);
        if (is_zero(*x1))
            *x1 = *x2 = 0;
        return TWO_SIMILAR_ROOTS;
    }

    else if (discriminant < 0)
    {
        *x1 = *x2 = NAN;
        return NO_ROOTS;
    }
    double sqrt_discriminant = sqrt(discriminant);
    *x1 = ((-coefficients[1]) - sqrt_discriminant) / (2 * coefficients[2]);
    *x2 = ((-coefficients[1]) + sqrt_discriminant) / (2 * coefficients[2]);
    sort_roots(x1, x2);
    return TWO_ROOTS;
}

int restore_coefficients(double coefficients[], double x1, double x2)
{
    coefficients[0] = x1 * x2 * coefficients[2];
    coefficients[1] = -(x1 + x2) * coefficients[2];
    return (is_zero(x1 - x2)) ? TWO_SIMILAR_ROOTS : TWO_ROOTS;
}

bool is_zero(double number)
{
    return (fabs(number) < ACCURACY);
}

void sort_roots(double *x1, double *x2)
{
    if (*x1 > *x2)
    {
        double temp = *x2;
        *x2 = *x1;
        *x1 = temp;
    }
}
