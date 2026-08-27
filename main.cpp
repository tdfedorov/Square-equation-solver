#include "interact.cpp"

/// Слово INTERACT
const char* INTERACT = "INTERACT";

/// Слово TEST
const char* TEST = "TEST";


/**
Данная функция позволяет выбрать тип работы программы.
\param number_of_terminal_args - количество аргументов командной строки
\param word - слово из командной строки
\return 1 при вводе INTERACT, 0 при вводе TEST, иначе 2
*/
int choose_type_of_working(int number_of_terminal_args, char word[]);

/**
Данная функция позволяет выбрать тип работы программы не из командной строки.
\return true, при вводе INTERACT, false при вводе TEST
*/
bool run_not_terminal_input();


int main(int argc, char *argv[])
{
    int arg_index = 0;
    if (argc != 1)
        arg_index = 1;
    int type_of_working = choose_type_of_working(argc, argv[arg_index]);
    if (type_of_working == 1)
        run_interact();
    else if (type_of_working == 0)
        run_tests();
    else
        printf("Некорректный ввод из командной строки\n");
    printf("Работа завершена\n");
}

int choose_type_of_working(int number_of_terminal_args, char word[])
{
    if (number_of_terminal_args != 1)
    {
        if (check_word(word, INTERACT))
            return 1;
        else if (check_word(word, TEST))
            return 0;
        else
            return 2;
    }
    else
        return run_not_terminal_input();
}

bool run_not_terminal_input()
{
    char word[MAX_SIZE_OF_WORD] = {};
    printf("Данная программа позволяет вычислить корни уравнения второй степени.\n"); // уравнение вида a * x^2 + b * x + c = 0

    while (true)
    {
        printf("Если вы хотите вводить свои коэффициенты введите INTERACT, если вы хотите запустить тест введите TEST\n");
        char check = '\0';
        scanf("%99s%c", word, &check);

        if (check_word(word, INTERACT) && (check == '\n' || check == EOF))
        {
            return true;
        }
        else if (check_word(word, TEST) && (check == '\n' || check == EOF))
        {
            return false;
        }
        else
        {
            printf("Вы некорректно ввели данные, выберите только одно из двух значений\n");
            if (check != '\n' && check != EOF)
                clean_stdin();
        }
    }

}
