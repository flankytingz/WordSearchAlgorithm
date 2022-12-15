#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <sstream>

/*
 * Input code for backspace is 8
 * */

using namespace std;

void printLine()
{
    cout << "\t\t------------" << endl << flush;
}
void printWord(const string& word, const int where)
{
    switch (where)
    {
        case 0:
            cout << word << " found horizontally";
            break;
        case 1:
            cout << word << " found reverse horizontally";
            break;
        case 2:
            cout << word << " found vertically";
            break;
        case 3:
            cout << word << " found reverse vertically";
            break;
        case 4:
            cout << word << " found diagonally";
            break;
        default:
            break;
    }
    cout << endl;
}

void getGrid(string rows[], const int ROWS, const int COLUMNS)
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

                        if (i != 0 and j == 0)
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
    int ROWS;
    int COLUMNS;
    int DIAGONALS;
    stringstream ss;

    printLine();

    while (true)
    {
        string temp;
        cout << "Enter grid size (format: 5x2):" << endl;
        getline(cin, temp);
        if (temp.length() >= 3 and temp.find('x') != string::npos)
        {
            ROWS = stoi(temp.substr(temp.find('x') + 1));
            COLUMNS = stoi(temp.substr(0,temp.find('x')));
            DIAGONALS = ROWS + COLUMNS - 3;
            break;
        }
    }

    string rows[ROWS];

    printLine();
    cout << "Enter grid of size " << ROWS << "x" << COLUMNS << ":" << endl;

    getGrid(rows, ROWS, COLUMNS);

    printLine();
    cout << "This is the grid you have input:" << endl;

    cout << "    ";
    for (int i = 0; i < COLUMNS; i++)
        cout << i << "   ";
    cout << endl;

    for (int i = 0; i < ROWS; i++)
    {
        cout << i << "   ";
        for (int j = 0; j < COLUMNS; j++)
            cout << rows[i].substr(j,1) << "   ";
        cout << endl;
    }

    string columns[COLUMNS];

    for (int i = 0; i < COLUMNS; i++)
        for (int j = 0; j < ROWS; j++)
            columns[i] += rows[j].substr(i,1);

    string diagonalsOne[DIAGONALS];

    for (int i = 0; i < ROWS - 1; i++)
    {
        for (int j = (ROWS - 2) - i, k = 0; j < ROWS and k < COLUMNS; j++, k++)
        {
            diagonalsOne[i] += rows[j].substr(k, 1);
        }
    }
    for (int i = ROWS - 1; i < DIAGONALS; i++)
    {
        for (int j = i - ROWS + 2, k = 0; j < COLUMNS and k < ROWS; j++, k++)
        {
            diagonalsOne[i] += columns[j].substr(k,1);
        }
    }

    string diagonalsTwo[DIAGONALS];

    for (int i = 0; i < COLUMNS - 1; i++)
    {
        for (int j = i + 1, k = 0; j >= 0 and k < ROWS; j--, k++)
        {
            diagonalsTwo[i] += columns[j].substr(k,1);
        }
    }
    for (int i = COLUMNS - 1; i < DIAGONALS; i++)
    {
        for (int j = i - COLUMNS + 1, k = COLUMNS; j < ROWS and k >= 0; j++, k--)
        {
            diagonalsTwo[i] += rows[j].substr(k,1);
        }
    }

    string rowsR[ROWS];
    string columnsR[COLUMNS];
    string diagonalsOneR[DIAGONALS];
    string diagonalsTwoR[DIAGONALS];

    for (int i = 0; i < ROWS; i++)
        for (int j = (int) rows[i].length() - 1; j >= 0; j--)
            rowsR[i] += rows[i].substr(j, 1);

    for (int i = 0; i < COLUMNS; i++)
        for (int j = (int) columns[i].length() - 1; j >= 0; j--)
            columnsR[i] += columns[i].substr(j, 1);

    for (int i = 0; i < DIAGONALS; i++)
        for (int j = (int) diagonalsOne[i].length() - 1; j >= 0; j--)
            diagonalsOneR[i] += diagonalsOne[i].substr(j, 1);

    for (int i = 0; i < DIAGONALS; i++)
        for (int j = (int) diagonalsTwo[i].length() - 1; j >= 0; j--)
            diagonalsTwoR[i] += diagonalsTwo[i].substr(j, 1);


    ifstream wordList;
    wordList.open(R"(C:\Users\Flanky\CLionProjects\CS101_A3\wordlist.txt)");

    string word;

    if (wordList.is_open())
        while (!wordList.eof())
        {
            wordList >> word;

            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < rows[i].length(); j++)
                {
                    unsigned long long int pos = rows[i].find(word, j);

                    if (pos != string::npos)
                    {
                        printWord(word,0);
                        j = (int) pos + (int) word.length() - 1;
                    }
                }

                for (int j = 0; j < rowsR[i].length(); j++)
                {
                    unsigned long long int pos = rowsR[i].find(word, j);

                    if (pos != string::npos)
                    {
                        printWord(word,1);
                        j = (int) pos + (int) word.length() - 1;
                    }
                }
            }

            for (int i = 0; i < COLUMNS; i++)
            {
                for (int j = 0; j < columns[i].length(); j++)
                {
                    unsigned long long int pos = columns[i].find(word, j);

                    if (pos != string::npos)
                    {
                        printWord(word,2);
                        j = (int) pos + (int) word.length() - 1;
                    }
                }
                for (int j = 0; j < columnsR[i].length(); j++)
                {
                    unsigned long long int pos = columnsR[i].find(word, j);

                    if (pos != string::npos)
                    {
                        printWord(word,3);
                        j = (int) pos + (int) word.length() - 1;
                    }
                }
            }

            for (int i = 0; i < DIAGONALS; i++)
            {
                for (int j = 0; j < diagonalsOne[i].length(); j++)
                {
                    unsigned long long int pos = diagonalsOne[i].find(word, j);

                    if (pos != string::npos)
                    {
                        printWord(word,4);
                        j = (int) pos + (int) word.length() - 1;
                    }
                }
                for (int j = 0; j < diagonalsOneR[i].length(); j++)
                {
                    unsigned long long int pos = diagonalsOneR[i].find(word, j);

                    if (pos != string::npos)
                    {
                        printWord(word,4);
                        j = (int) pos + (int) word.length() - 1;
                    }
                }

                for (int j = 0; j < diagonalsTwo[i].length(); j++)
                {
                    unsigned long long int pos = diagonalsTwo[i].find(word, j);

                    if (pos != string::npos)
                    {
                        printWord(word,4);
                        j = (int) pos + (int) word.length() - 1;
                    }
                }
                for (int j = 0; j < diagonalsTwoR[i].length(); j++)
                {
                    unsigned long long int pos = diagonalsTwoR[i].find(word, j);

                    if (pos != string::npos)
                    {
                        printWord(word,4);
                        j = (int) pos + (int) word.length() - 1;
                    }
                }
            }
        }

    printLine();
    system("pause");
    return 0;
}