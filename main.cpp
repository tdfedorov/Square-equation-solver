#include "interact.cpp"
#include <getopt.h>

/// Слово INTERACT
const char* INTERACT = "INTERACT";

/// Слово TEST
const char* TEST = "TEST";

/**
Данная функция позволяет выбрать тип работы программы не из командной строки.
*/
void run_not_terminal_input();


int main(int argc, char *argv[])
{
    option long_opts[] =
    {
        {"INTERACT", 0, NULL, 'I'},
        {"TEST", 0, NULL, 'T'},
        {NULL, 0, NULL, 0}
    };
    int opt = 0;
    if ((opt = getopt_long(argc, argv, "", long_opts, NULL)) != -1)
        switch(opt)
        {
            case 'I':
                run_interact();
                break;
            case 'T':
                run_tests();
                break;
            case '?':
                printf_with_delay("Некорректный ввод опции из командной строки\n");
                break;
            default:
                break;
        }
    else
        run_not_terminal_input();
    printf_with_delay("Работа завершена\n");
}

void run_not_terminal_input()
{
    char word[MAX_SIZE_OF_WORD] = {};
    printf_with_delay("Данная программа позволяет вычислить корни уравнения второй степени.\n");

    while (true)
    {
        printf_with_delay("Если вы хотите вводить свои коэффициенты введите INTERACT, если вы хотите запустить тест введите TEST\n");
        char check = '\0';
        scanf("%99s%c", word, &check);

        if (check_word(word, INTERACT) && (check == '\n' || check == EOF))
        {
            run_interact();
            break;
        }
        else if (check_word(word, TEST) && (check == '\n' || check == EOF))
        {
            run_tests();
            break;
        }
        else
        {
            printf_with_delay("Вы некорректно ввели данные, выберите только одно из двух значений\n");
            if (check != '\n' && check != EOF)
                clean_stdin();
        }
    }
}
