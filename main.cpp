#include "interact.cpp"

/// Слово INTERACT
const char* INTERACT = "INTERACT";

/// Слово TEST
const char* TEST = "TEST";

/**
Здесь описаны константы для разных видов работы программы.
*/
enum TYPES_OF_WORKING
{
    INPUT_INTERACT, ///< константа для работы в режиме INTERACT
    INPUT_TEST, ///< константа для работы в режиме TEST
    INPUT_ERROR ///< константа, используемая при некорректном вводе из командной строки
};

/**
Данная функция позволяет выбрать тип работы программы.
\param number_of_terminal_args - количество аргументов командной строки
\param word - слово из командной строки
\return INPUT_INTERACT при вводе INTERACT, INPUT_TEST при вводе TEST, иначе INPUT_ERROR
*/
int choose_type_of_working(int number_of_terminal_args, char word[]);

/**
Данная функция позволяет выбрать тип работы программы не из командной строки.
\return INPUT_INTERACT при вводе INTERACT, INPUT_TEST при вводе TEST
*/
int run_not_terminal_input();


int main(int argc, char *argv[])
{
    int arg_index = 0;
    if (argc != 1)
        arg_index = 1;
    int type_of_working = choose_type_of_working(argc, argv[arg_index]);
    if (type_of_working == INPUT_INTERACT)
        run_interact();
    else if (type_of_working == INPUT_TEST)
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
            return INPUT_INTERACT;
        else if (check_word(word, TEST))
            return INPUT_TEST;
        else
            return INPUT_ERROR;
    }
    else
        return run_not_terminal_input();
}

int run_not_terminal_input()
{
    char word[MAX_SIZE_OF_WORD] = {};
    printf("Данная программа позволяет вычислить корни уравнения второй степени.\n");

    while (true)
    {
        printf("Если вы хотите вводить свои коэффициенты введите INTERACT, если вы хотите запустить тест введите TEST\n");
        char check = '\0';
        scanf("%99s%c", word, &check);

        if (check_word(word, INTERACT) && (check == '\n' || check == EOF))
        {
            return INPUT_INTERACT;
        }
        else if (check_word(word, TEST) && (check == '\n' || check == EOF))
        {
            return INPUT_TEST;
        }
        else
        {
            printf("Вы некорректно ввели данные, выберите только одно из двух значений\n");
            if (check != '\n' && check != EOF)
                clean_stdin();
        }
    }

}
