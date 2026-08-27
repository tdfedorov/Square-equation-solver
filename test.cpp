#include "math.cpp"
#include <assert.h>
#define NO_COLOR "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"


/**
Данная структура используется как аргумент в нескольких функциях с тестами
*/
struct TEST_ARGS
{
    double coefficients[3]; ///< коэффициенты
    int number_of_roots_reference; ///< требуемое количество корней
    double x1_reference, x2_reference; ///< требуемые значения корней
};

/// Минимальное значение функции new_rand
const double MIN_NEW_RAND = -1e6;

/// Максимальное значение функции new_rand
const double MAX_NEW_RAND = 1e6;

/// Количество итераций со случайными числами для квадратного уравнения
const int AMOUNT_OF_ITERATIONS_WITH_SQUARE_EQUATION = 100;


/// Количество итераций со случайными числами для линейного уравнения
const int AMOUNT_OF_ITERATIONS_WITH_LINEAR_EQUATION = 100;

/// Количество итераций со случайными числами для уравнения без корней
const int AMOUNT_OF_ITERATIONS_WITH_NO_ROOTS = 100;

/// Количество попыток генерации ненулевых чисел для функции new_rand_without_zero
const int NUMBER_OF_ATTEMPTS = 10;

/**
Данная функция запускает функции run_randomized_test, run_determined_tests и run_tests_from_file и печатает общее число ошибок
*/
void run_tests();

/**
Данная функция проводит 1 тест с известными аргументами
\param test - структура с коэффициентами и требуемыми значениями
\return Значение функции check_for_equation, преобразованное в тип int
*/
int run_one_test(TEST_ARGS test);

/**
Данная функция возвращает случайное число из диапазона от MIN_NEW_RAND до MAX_NEW_RAND
\return Случайное число типа double
*/
double new_rand();

/**
Данная функция возвращает случайное число из диапазона от MIN_NEW_RAND до MAX_NEW_RAND, без числа 0.
При исчерпании всех попыток генерации ненулевого числа будет ошибка.
\return Случайное ненулевое число типа double
*/
double new_rand_without_zero(void);

/**
Данная функция очищает буфер ввода.
*/
void clean_stdin(void);

/**
Данная функция запускает тест со значениями из файла.
\return Число ошибок.
*/
int run_tests_from_file(void);

/**
Данная функция запускает тест с известными значениями (проверяются особое случаи с нулевыми коэффициентами).
\return Число ошибок.
*/
int run_determined_tests(void);

/**
Данная функция запускает тест со случайными числами.
\return Число ошибок.
*/
int run_randomized_test(void);

/**
Данная функция печатает сообщение об ошибке, выводит коэффициенты, требуемое количество корней, требуемые значения корней, посчитанное количество корней и посчитанные значения корней.
\param test - структура вида TEST_ARGS
\param number_of_roots - полученное количество корней
\param x1, x2 - полученные значения корней
*/
void print_mistake_message(TEST_ARGS test, int number_of_roots, double x1, double x2);

/**
Данная функция сравнивает полученные значения с эталонными.
\param test - структура вида TEST_ARGS
\param number_of_roots - полученное количество корней
\param x1, x2 - полученные значения корней
\return true, если есть ошибка и вызывает print_mistake_message, иначе false и печатает "Тест пройден"
*/
bool check_for_equation(TEST_ARGS test, int number_of_roots, double x1, double x2);

/**
Данная функция позволяет сравнивать не только вещественные числа double, но и переменные со значением INFINITY и NAN.
\param x - сравниваемое число
\param x_reference - то число, с которым нужно сравнить x
\return true, если значения x и x_reference одинаковы, false в противном случае
*/
bool is_same(double x, double x_reference);

/**
Данная функция проводит 1 тест со случайными числами с ненулевым старшим коэффициентом.
\return true, при наличии ошибок, false в противном случае
*/
bool iteration_for_square_equation();

/**
Данная функция проводит 1 тест со случайными числами с нулевым старшим коэффициентом и ненулевым коэффициентом при x.
\return true, при наличии ошибок, false в противном случае
*/
bool iteration_for_linear_equation();

/**
Данная функция проводит 1 тест со случайными числами с нулевым старшим коэффициентом, нулевым коэффициентом при x и ненулевым пустым коэффициентом.
\return true, при наличии ошибок, false в противном случае
*/
bool iteration_for_equation_with_no_roots();


void run_tests()
{
    int number_of_mistakes = run_randomized_test() + run_determined_tests() + run_tests_from_file();
    printf("Число ошибок: %d\n", number_of_mistakes);
}

int run_one_test(TEST_ARGS test)
{
    double x1 = 0.0, x2 = 0.0;
    int number_of_roots = solve_equation(test.coefficients, &x1, &x2);
    return check_for_equation(test, number_of_roots, x1, x2);
}

int run_determined_tests(void)
{
    int number_of_mistakes = 0;
    TEST_ARGS determined_tests[] =
    {
        {{0, 0, 0}, INF_ROOTS, INFINITY, INFINITY},
        {{1, 0, 0}, NO_ROOTS, NAN, NAN},
        {{0, 1, 0}, ONE_ROOT, 0, NAN},
        {{0, 0, 1}, TWO_SIMILAR_ROOTS, 0, 0},
        {{-1, 0, 1}, TWO_ROOTS, -1, 1},
        {{0, 1, 1}, TWO_ROOTS, -1, 0},
        {{4, 4, 1}, TWO_SIMILAR_ROOTS, -2, -2},
        {{-6, 5, 1}, TWO_ROOTS, -6, 1},
    };
    printf("Тест с определенными аргументами:\n");
    int size = sizeof(determined_tests) / sizeof(TEST_ARGS);

    for (int i = 0; i < size; ++i)
    {
        assert(0 <= i && i < size);
        number_of_mistakes += run_one_test(determined_tests[i]);
    }

    return number_of_mistakes;
}

int run_tests_from_file()
{
    int mistakes = 0;
    FILE *args = fopen("args.txt", "r");
    TEST_ARGS test = {};
    printf("Тест из файла\n");
    for (int i = 0; i < 8; ++i)
    {
        fscanf(args, "%lf %lf %lf %d %lf %lf", &test.coefficients[0], &test.coefficients[1], &test.coefficients[2],
        &test.number_of_roots_reference, &test.x1_reference, &test.x2_reference);
        mistakes += run_one_test(test);
    }
    fclose(args);
    return mistakes;
}

void print_mistake_message(TEST_ARGS test, int number_of_roots, double x1, double x2)
{
    printf(RED "Тест не пройден: a = %lf, b = %lf, c = %lf\n",
                                 test.coefficients[2], test.coefficients[1], test.coefficients[0]);
    printf(GREEN "Требуемое значение: %d корней, x1 = %lf, x2 = %lf\n",
                                 test.number_of_roots_reference, test.x1_reference, test.x2_reference);
    printf(RED "Получено:           %d корней, x1 = %lf, x2 = %lf\n", number_of_roots, x1, x2);
    printf(NO_COLOR);
}

void clean_stdin(void)
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
}

double new_rand()
{
    return rand() * ((MAX_NEW_RAND - MIN_NEW_RAND) / RAND_MAX) + MIN_NEW_RAND;
}

double new_rand_without_zero(void)
{
    for (int i = 0; i < NUMBER_OF_ATTEMPTS; ++i)
    {
        double rand_value = new_rand();
        if (rand_value != 0)
            return rand_value;
    }
    assert(false && "Превышено число попыток генерации случайных чисел");
}

bool check_for_equation(TEST_ARGS test, int number_of_roots, double x1, double x2)
{
    if (!is_same(x1, test.x1_reference) || !is_same(x2, test.x2_reference) || number_of_roots != test.number_of_roots_reference)
    {
        print_mistake_message(test, number_of_roots,  x1, x2);
        return true;
    }
    printf(GREEN "Тест пройден\n" NO_COLOR);
    return false;
}

bool is_same(double x, double x_reference) //подумай как уменьшить колво ифов
{
    if (isfinite(x_reference))
    {
        if (isfinite(x) && is_zero(x - x_reference))
            return true;
        return false;
    }
    else if (isnan(x_reference))
    {
        if (isnan(x))
            return true;
        return false;
    }
    if (isinf(x))
        return true;
    return false;
}

int run_randomized_test()
{
    int mistakes = 0, i = 0;
    printf("Тест со случайными числами:\n");

    for (i = 0; i < AMOUNT_OF_ITERATIONS_WITH_SQUARE_EQUATION; ++i)
        mistakes += iteration_for_square_equation();

    for (i = 0; i < AMOUNT_OF_ITERATIONS_WITH_LINEAR_EQUATION; ++i)
        mistakes += iteration_for_linear_equation();

    for (i = 0; i < AMOUNT_OF_ITERATIONS_WITH_NO_ROOTS; ++i)
        mistakes += iteration_for_equation_with_no_roots();

    return mistakes;
}

bool iteration_for_square_equation()
{
    TEST_ARGS test = {};
    double x1, x2 = 0.0;
    test.x1_reference = new_rand();
    test.x2_reference = new_rand();
    sort_roots(&test.x1_reference, &test.x2_reference);
    test.coefficients[2] = new_rand_without_zero();
    test.number_of_roots_reference = restore_coefficients(test.coefficients, test.x1_reference, test.x2_reference);
    return check_for_equation(test, solve_equation(test.coefficients, &x1, &x2), x1, x2);
}

bool iteration_for_linear_equation()
{
    TEST_ARGS test = {};
    double x1, x2 = 0.0;
    test.coefficients[0] = new_rand();
    test.coefficients[1] = new_rand_without_zero();
    test.coefficients[2] = 0.0;
    test.x1_reference = (-test.coefficients[0]) / test.coefficients[1];
    test.x2_reference = NAN;
    test.number_of_roots_reference = ONE_ROOT;
    return check_for_equation(test, solve_equation(test.coefficients, &x1, &x2), x1, x2);
}

bool iteration_for_equation_with_no_roots()
{
    TEST_ARGS test = {};
    double x1, x2 = 0.0;
    test.coefficients[0] = new_rand_without_zero();
    test.coefficients[1] = 0.0;
    test.coefficients[2] = 0.0;
    test.x1_reference = test.x2_reference = NAN;
    test.number_of_roots_reference = NO_ROOTS;
    return check_for_equation(test, solve_equation(test.coefficients, &x1, &x2), x1, x2);
}

