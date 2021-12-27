#include <ncurses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

bool isWordSuit(int *last_word, const int last_word_length, int *current_word, const int current_word_length, const int max_len)
{
    if (current_word_length != max_len)
    {
        return false;
    }
    if (last_word_length != current_word_length)
    {
        return true;
    }
    if (current_word_length == last_word_length && current_word_length == max_len)
    {
        for (size_t i = 0; i < last_word_length; i++)
        {
            if (last_word[i] != current_word[i])
            {
                return true;
            }
        }
    }
    return false;
}
int main()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int size_of_console = w.ws_col;
    initscr();
    noecho();
    int c;
    int max_lenght = 0;
    int current_length = 0;
    int *last_word = new int[200];
    int *current_word = new int[200];
    int last_word_lenght;
    int n = -1;
    int *arr = new int[400];
    int kn = 0, qn = 0;
    int j = 0;
    while ((c = getch()) != '.')
    {
        if ((c > 96 && c < 123) || (c == 127) || (c == 32))
        {
            if (c > 96 && c < 123 || (c == 32))
            {
                echochar(c);
                n++;
                qn = n % size_of_console;
                kn = n / size_of_console;
                arr[n] = c;
            }
            if (c == 127 && n != -1)
            {
                arr[n] = -1;
                move(kn, qn);
                echochar(' ');
                move(kn, qn);
                n--;
                qn = n % size_of_console;
                kn = n / size_of_console;
            }
        }
    }
    echochar(c);
    echochar('\n');

    n++;

    //clearing all whitespaces at the end;
    int nCurrent = n;
    while (arr[nCurrent - 1] == 32)
    {
        nCurrent--;
    }
    n = nCurrent;

    n++;
    arr[n - 1] = '.';
    int z = 0;

    for (z = n - 2; z >= 0; z--)
    {
        if (arr[z] == ' ')
        {
            break;
        }
        if (arr[z] != ' ')
        {
            last_word_lenght++;
        }
        else
        {
            break;
        }
    }
    int qq = 0;
    for (int i = z + 1; i < n - 1; i++)
    {
        last_word[qq] = arr[i];
        qq++;
    }

    for (size_t i = 0; i < n - last_word_lenght; i++)
    {
        if (arr[i] == 32)
        {
            if (j > max_lenght)
            {
                max_lenght = j;
            }
            j = 0;
        }
        else
        {
            j++;
        }
    }
    if (j > max_lenght)
    {
        max_lenght = j;
    }
    if (max_lenght < last_word_lenght)
    {
        max_lenght = last_word_lenght;
    }

    j = 0;

    for (size_t i = 0; i < n - last_word_lenght; i++)
    {
        if (arr[i] == 32)
        {
            if (isWordSuit(last_word, last_word_lenght, current_word, j, max_lenght))
            {
                for (size_t q = 0; q < j; q++)
                {
                    echochar(current_word[q]);
                }
                echochar(' ');
            }
            j = 0;
        }
        else
        {
            current_word[j] = arr[i];
            j++;
        }
    }

    while (getch() != 'q')
    {
    }
    delete[] arr;
    delete[] last_word;
    delete[] current_word;

    endwin();
    return 0;
}