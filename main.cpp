#include <ncurses.h>
bool isWordSuit(int *last_wotd, const int &last_word_length, int *current_word, const int &current_word_length, const int &max_len)
{
    if (current_word_length != max_len)
    {
        return false;
    }

    if (last_word_length != current_word_length)
    {
        return true;
    }
    for (size_t i = 0; i < last_word_length; i++)
    {
        if (last_wotd[i] != current_word[i])
        {
            return true;
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
    int *last_word = new int[100];
    int *max_lenght_words_positions = new int[10];
    int max_lenght_words_count = 0;
    int *current_word = new int[100];
    int n = -1;
    int *arr = new int[1000];
    int kn = 0;
    int qn = 0;
    while ((c = getch()) != '.')
    {
        // printw("%d", c);
        if ((c > 96 && c < 123) || (c == 127) || (c == 32))
        {
            if (c > 96 && c < 123 || (c == 32))
            {
                echochar(c);
                n++;
                qn=n%80;
                kn = n/80;
                arr[n] = c;
            }
            if (c == 127)
            {
                if (n != -1)
                {
                    arr[n] = -1;
                    move(kn, qn);
                    echochar(' ');
                    move(kn, qn);
                    n--;
                    qn=n%80;
                    kn = n/80;
                }
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
    // for (size_t i = 0; i < n; i++)
    // {
    //     printw("%d ",arr[i]);
    // }
    arr[++n] = '.';

    int j = 0;
    //нахождение максимальной длинны слова.
    //запись последнего слова
    for (size_t i = 0; i < n; i++)
    {
        if (arr[i] == 32)
        {
            if (current_length > max_lenght)
            {
                max_lenght = current_length;
            }
            j = 0;
            current_length = 0;
        }
        else
        {
            last_word[j] = arr[i];
            j++;
            current_length++;
        }
    }
    if (current_length > max_lenght)
    {
        max_lenght = current_length;
    }

    j = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (arr[i] == 32)
        {
            if (isWordSuit(last_word, max_lenght, current_word, j, max_lenght))
            {
                for (size_t q = 0; q < j; q++)
                {
                    echochar(current_word[q]);
                }
                echochar(' ');
            }
            j = 0;
            current_length = 0;
        }
        else
        {
            current_word[j] = arr[i];
            j++;
            current_length++;
        }
    }
    if (isWordSuit(last_word, max_lenght, current_word, j, max_lenght))
    {
        for (size_t q = 0; q < j; q++)
        {
            echochar(current_word[q]);
        }
        echochar(' ');
    }

    // for (size_t i = 0; i < j; i++)
    // {
    //     echochar(last_word[i]);
    // }

    // printw("%d", max_lenght);

    while (getch() != 'q')
    {
    }

    endwin();
    return 0;
}