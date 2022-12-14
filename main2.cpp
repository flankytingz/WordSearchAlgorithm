#include <iostream>
#include <string>
#include <conio.h>

/*
 * Input code for backspace is 8
 * */

using namespace std;

const int ROWS = 2;
const int COLUMNS = 5;
static string rows[ROWS];
void getGrid(string rows[ROWS])
{
    int i = 0, j = 0, input;
    char letter;

    while (i != ROWS)
    {
        while (j != COLUMNS)
        {
            input = getch();
            letter = (char) tolower((char) input);

            if (input == 8)
            {
                if (j != 0 and j != (COLUMNS - 1))
                {
                    cout << "\b\b" << "\033[K";
                    continue;
                } else
                if (j == 0)
                {
                    if (i != 0)
                    {
                        cout << "\033[u" << "\b\b" << "\033[K";
                        continue;
                    }
                }
            }

            switch (letter) {
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                case 'u':
                case 'v':
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                    if (j == COLUMNS - 1)
                        cout << (char) toupper(letter);
                    else
                        cout << (char) toupper(letter) << " ";

                    j++;
                    break;

                default:
                    break;
            }

            cout << flush; // NOLINT(readability-misleading-indentation)
        }

        cout << "\033[s" << endl;

        j = 0;
        i++;
    }

}

int main()
{
    getGrid(nullptr);
    system("pause");
    return 0;
}