#include <ncurses.h>

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
    initscr();
    noecho();
    int c;
    int max_lenght = 0;
    int current_length = 0;
    int *last_word = new int[200];
    int *current_word = new int[200];
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
                qn = n % 80;
                kn = n / 80;
                arr[n] = c;
            }
            if (c == 127 && n != -1)
            {
                arr[n] = -1;
                move(kn, qn);
                echochar(' ');
                move(kn, qn);
                n--;
                qn = n % 80;
                kn = n / 80;
            }
        }
    }
    echochar(c);
    echochar('\n');

    //clearing all whitespaces at the end;
    int nCurrent = n;
    while (arr[nCurrent - 1] == 32)
    {
        nCurrent--;
    }
    n = nCurrent;

    arr[++n] = '.';
    size_t last_word_lenght;

    for (size_t i = 0; i < n; i++)
    {
        if (arr[i] == 32)
        {
            if (j > max_lenght)
            {
                max_lenght = j;
            }
            last_word_lenght = j;
            j = 0;
        }
        else
        {
            last_word[j] = arr[i];
            j++;
        }
    }
    if (j > max_lenght)
    {
        max_lenght = j;
    }

//    printw("%d", last_word_lenght);

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

    endwin();
    return 0;
}