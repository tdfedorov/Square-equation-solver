#include "test.cpp"
#include <string.h>
#include <ctype.h>
#include <unistd.h>

/// Максимальная длина слова
const int MAX_SIZE_OF_WORD = 100;

/// Слово YES
const char* YES = "YES";

/// Слово NO
const char* NO = "NO";

/// ДЛЯ ПАСХАЛКИ
const int SIX_SEVEN = 6;

/**
Данная функция запускает цикл ввода коэффициентов.
*/
void run_interact();

/**
Данная функция записывает значения в массив coefficients
\param coefficients - коэффициенты уравнения
*/
void make_input(double coefficients[]);

/**
Данная функция запускает print_end_message и is_run_new_input.
\param number_of_square_equation_roots - количество корней уравнения
\param x1, x2 - значения корней
\return Значение функции is_run_new_input
*/
bool make_output(int number_of_square_equation_roots, double x1, double x2);

/**
Данная функция печатает определенное сообщение в зависимости от значения переменной number_of_square_equation_roots, в некоторых случаях выводятся значения корней.
\param number_of_square_equation_roots - количество корней уравнения
\param x1, x2 - значения корней
*/
void print_end_message(int number_of_square_equation_roots, double x1, double x2);

/**
Данная функция запрашивает у пользователя желание продолжить выполнение ввода.
\return true при вводе YES, false при вводе NO
*/
bool is_run_new_input();

/**
Данная функция позволяет сравнить 2 слова без учета регистра.
\param word - сравниваемое слово
\param word_reference - то слово, с которым сравнивается x
\return true, если слова одинаковы, false в противном случае
*/
bool check_word(char word[], const char* word_reference);

/**
Данная функция позволяет делать посимвольный вывод.
*/
void printf_with_delay(const char* word);


/**
Данная функция вызывает пасхалку
*/
void paskhalka();

void run_interact()
{
    double coefficients[] = {NAN, NAN, NAN}; // в массиве индекс соответствует показателю степени при x
    double x1 = NAN, x2 = NAN;
    int number_of_square_equation_roots = 0;
    bool is_continue = true;

    while (is_continue)
    {
        make_input(coefficients);
        number_of_square_equation_roots = solve_equation(coefficients, &x1, &x2);
        is_continue = make_output(number_of_square_equation_roots, x1, x2);
    }
}

void make_input(double *coefficients)
{
    int number_of_nice_coefficients = 0, number_of_attempts_to_get_pashalka = 0;
    char check = '\0';

    while (number_of_nice_coefficients != 4 || (check != '\n' && check != EOF)
    || !isfinite(*(coefficients + 2)) || !isfinite(*(coefficients + 1)) || !isfinite(*(coefficients + 0)))
    {
        printf_with_delay("Введите коэффициенты квадратного уравнения через пробел.\n");
        printf_with_delay("Коэффициенты должны быть целыми числами или десятичными дробями:\n");

        number_of_nice_coefficients = scanf("%lf %lf %lf%c",
                                            coefficients + 2, coefficients + 1, coefficients + 0, &check);
        if (number_of_nice_coefficients != 4 || (check != '\n' && check != EOF)
        || !isfinite(*(coefficients + 2)) || !isfinite(*(coefficients + 1)) || !isfinite(*(coefficients + 0)))

        {
            printf_with_delay("Некорректный ввод, повторите запрос\n");
            if (check != '\n' && check != EOF)
                clean_stdin();
            if (++number_of_attempts_to_get_pashalka < SIX_SEVEN)
                printf("До пасхалки %d некорректных вводов\n", SIX_SEVEN - number_of_attempts_to_get_pashalka);
            else if (number_of_attempts_to_get_pashalka == SIX_SEVEN)
                paskhalka();
            else
                printf("Вы уже видели пасхалку!\n");
        }
    }
}

bool make_output(int number_of_square_equation_roots, double x1, double x2)
{
    print_end_message(number_of_square_equation_roots, x1, x2);
    return is_run_new_input();
}

void print_end_message(int number_of_square_equation_roots, double x1, double x2)
{
    switch (number_of_square_equation_roots)
    {
        case NO_ROOTS:
            printf("У данного уравнения нет корней\n");
            break;
        case ONE_ROOT:
            printf("У данного линейного уравнения 1 корень, x = %.2lf\n", x1);
            break;
        case TWO_SIMILAR_ROOTS:
            printf("У данного квадратного уравнения 2 одинаковых корня, x1 = x2 = %.2lf\n", x1);
            break;
        case TWO_ROOTS:
            printf("У данного квадратного уравнения 2 корня, x1 = %.2lf, x2 = %.2lf\n", x1, x2);
            break;
        case INF_ROOTS:
            printf("У уравнения бесконечно много решений\n");
            break;
        default:
            break;
    }
}

bool is_run_new_input()
{
    char word[MAX_SIZE_OF_WORD] = {};
    int check_end_of_file = 0;
    while (true)
    {
        printf_with_delay("Для продолжения работы программы введите YES, для выхода введите NO\n");
        char check = '0';
        check_end_of_file = scanf("%s%c", word, &check);
        if (check_word(word, YES) && (check == '\n' || check == EOF))
        {
            return true;
        }
        else if ((check_word(word, NO))  && (check == '\n' || check == EOF))
        {
            return false;
        }
        else if (check_end_of_file == EOF)
        {
            return false;
        }
        else
        {
            printf_with_delay("Некорректный ввод, выберите одно из двух значений\n");
            if (check != '\n' && check != EOF)
                clean_stdin();
        }
    }
}

bool check_word(char word[], const char* word_reference)
{
    if (strlen(word) == strlen(word_reference))
    {
        for (int i = 0; i < strlen(word_reference); ++i)
        {
            if (toupper(word[i]) != word_reference[i])
                return false;
        }
        return true;
    }
    else
        return false;
}


void paskhalka()
{
    printf_with_delay("Вы дошли до пасхалки, поздравляю!\n");
    printf_with_delay("Пасхалка через: \n");
    printf("3 секунды\n");
    sleep(1);
    printf("2 секунды\n");
    sleep(1);
    printf("1 секунду\n");
    sleep(1);
    printf("\n");
    printf_with_delay("     6                77777777     \n");
    printf_with_delay("    6                       7      \n");
    printf_with_delay("   6                       7       \n");
    printf_with_delay("  6                       7        \n");
    printf_with_delay("   6666666               7         \n");
    printf_with_delay("  6       6             7          \n");
    printf_with_delay("  6       6            7           \n");
    printf_with_delay("  6       6           7            \n");
    printf_with_delay("   6666666           7             \n\n");
}

void printf_with_delay(const char* word)
{
    while (*word)
    {
        putchar(*word);
        word++;
        fflush(stdout);
        usleep(10000);
    }
}
