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
    int i = 0, j = 0;
    char letter;

    while (i != ROWS)
    {
        while (j != COLUMNS)
        {
            letter = (char) tolower(getch());

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

                    rows[i] += letter;

                    j++;
                    break;

                default:
                    if (letter == '\b')
                    {

                        if (i == 0 and j != 0 and j != (COLUMNS - 1))
                        {
                            cout << "\b\b" << "\033[K";
                            j--;
                            rows[i].replace(j, 1, "");
                            continue;
                        }
                        else if (i != 0 and j == 0)
                        {
                            cout << "\033[u" << "\b" << "\033[K";
                            i--;
                            j = COLUMNS - 1;
                            rows[i].replace(j, 1, "");
                            continue;
                        }
                        else
                        {
                            cout << "\b\b" << "\033[K";
                            j--;
                            rows[i].replace(j, 1, "");
                            continue;
                        }
                    }
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
    getGrid(rows);
    for (const string row : rows)
        cout << row << endl;
    system("pause");
    return 0;
}