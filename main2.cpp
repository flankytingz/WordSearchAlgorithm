#include <iostream>
#include <conio.h>
#include <fstream>
#include <cmath>
#include <chrono>
#include <regex>

using namespace std;

const int ROWS = 10;
const int COLUMNS = 10;
const int DIAGONALS = 2*(ROWS + COLUMNS - 3);
char grid[ROWS][COLUMNS];
string rows[ROWS];
string rowsR[ROWS];
string columns[COLUMNS];
string columnsR[COLUMNS];
string diagonals[DIAGONALS];
string diagonalsR[DIAGONALS];

void getGrid();

void printGrid();

void buildRows();
void buildColumns();
void buildDiagonals();

void checkRows(const string& word, stringstream& ss);
void checkColumns(const string& word, stringstream& ss);
void checkDiagonals(const string& word, stringstream& ss);


int main()
{
    getGrid();

    const auto start = chrono::system_clock::now();

    buildRows();
    buildColumns();
    buildDiagonals();

    ifstream wordList = ifstream(R"(C:\Users\Flanky\CLionProjects\CS101_A3\wordlist.txt)");
    if (!wordList.is_open())
    {
        cerr << "FAILED TO OPEN WORD LIST" << endl;
        return 0;
    }

    while (!wordList.eof())
    {
        string word;
        stringstream ss;
        wordList >> word;

        checkRows(word, ss);
        checkColumns(word, ss);
        checkDiagonals(word, ss);

        if (ss.str().length() > 0)
        {
            cout << word << ":" << endl;
            cout << ss.str();
        }
    }

    const auto end = chrono::system_clock::now();
    const auto diff = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Total time taken: " << diff << endl;

    cout << "ENTER BACKSPACE TO EXIT" << endl;
    while ((char) getch() != '\b');
    return 0;
}

void checkDiagonals(const string& word, stringstream& ss)
{
    for (int i = 0; i < DIAGONALS; i++)
    {
        if (word.length() > diagonals[i].length())
        {
            return;
        }

        if (diagonals[i].find(word) != string::npos)
        {
            int pos = (int) diagonals[i].find(word);
            int length = (int) word.length() - 1;
            if (i < floor(DIAGONALS/4))
            {
                int temp = (int) floor(DIAGONALS/4) - i + 1;
                ss
                << "Found diagonally "
                << "(" << temp << ", " << pos + 1 << ")"
                << " - > "
                << "(" << temp + length << ", " << pos + length + 1 << ")"
                << endl;
            }
            else if (i < DIAGONALS/2)
            {
                int temp = i - (int) ceil(DIAGONALS/4);
                ss
                << "Found diagonally "
                << "(" << pos + 1 << ", " << temp + 1 << ")"
                << " -> "
                << "(" << pos + length + 1 << ", " << temp + length + 1 << ")"
                << endl;
            }
            else if (i < floor(3*DIAGONALS/4))
            {
                int temp = i - DIAGONALS/2 + 1;
                ss
                << "Found diagonally "
                << "(" << pos + 1 << ", " << temp + 1 << ")"
                << " -> "
                << "(" << pos + length + 1 << ", " << temp - length + 1 << ")"
                << endl;
            }
            else {
                ss
                << "Found diagonally "
                << "(" << ROWS - pos << ", " << COLUMNS - (diagonals[i].length() - pos - 1) << ")"
                << " -> "
                << "(" << ROWS - (pos + length) << ", " << COLUMNS - (diagonals[i].length() - length - pos - 1) << ")"
                << endl;
            }
        }

        if (diagonalsR[i].find(word) != string::npos)
        {
            int pos = (int) diagonalsR[i].find(word);
            int length = (int) word.length() - 1;
            if (i < floor(DIAGONALS/4))
            {
                int temp = (int) floor(DIAGONALS/4) - i + 1;
                ss
                << "Found diagonally "
                << "(" << temp + length << ", " << pos + length + 1 << ")"
                << " - > "
                << "(" << temp << ", " << pos + 1 << ")"
                << endl;
            }
            else if (i < DIAGONALS/2)
            {
                int temp = i - (int) ceil(DIAGONALS/4);
                ss
                        << "Found diagonally "
                        << "(" << pos + length + 1 << ", " << temp + length + 1 << ")"
                        << " -> "
                        << "(" << pos + 1 << ", " << temp + 1 << ")"
                        << endl;
            }
            else if (i < floor(3*DIAGONALS/4))
            {
                int temp = i - DIAGONALS/2 + 1;
                ss
                        << "Found diagonally "
                        << "(" << pos + 1 << ", " << temp + 1 << ")"
                        << " -> "
                        << "(" << pos + length + 1 << ", " << temp - length + 1 << ")"
                        << endl;
            }
            else {
                ss
                        << "Found diagonally "
                        << "(" << COLUMNS - (diagonalsR[i].length() - pos - 1) << ", " << ROWS - pos << ")"
                        << " -> "
                        << "(" << COLUMNS - (diagonalsR[i].length() - length - pos - 1) << ", " << ROWS - (pos + length) << ")"
                        << endl;
            }
        }
    }
}

void checkColumns(const string& word, stringstream& ss)
{
    if (word.length() > ROWS)
    {
        return;
    }

    for (int i = 0; i < COLUMNS; i++)
    {
        if (columns[i].find(word) != string::npos)
        {
            ss
            << "Found in column "
            << "(" << columns[i].find(word) + 1 << ", " << i + 1 << ")"
            << " -> "
            << "(" << columns[i].find(word) + word.length() << ", " << i + 1 << ")"
            << endl;
        }
        if (columnsR[i].find(word) != string::npos)
        {
            ss
            << "Found reversed in column "
            << "(" << ROWS - (columns[i].find(word) + 1) << ", " << i + 1 << ")"
            << " -> "
            << "(" << ROWS - (columns[i].find(word) + word.length()) << ", " << i + 1 << ")"
            << endl;
        }
    }
}

void checkRows(const string& word, stringstream& ss)
{
    if (word.length() > COLUMNS)
    {
        return;
    }

    for (int i = 0; i < ROWS; i++)
    {
        if (rows[i].find(word) != string::npos)
        {
            ss
            << "Found in row "
            << "(" << i + 1 << ", " << rows[i].find(word) + 1 << ")"
            << " -> "
            << "(" << i + 1 << ", " << rows[i].find(word) + word.length() << ")"
            << endl;
        }
        if (rowsR[i].find(word) != string::npos)
        {
            ss
            << "Found reversed in row "
            << "(" << i + 1 << ", " << COLUMNS - (rowsR[i].find(word)) << ")"
            << " -> "
            << "(" << i + 1 << ", " << COLUMNS - (rowsR[i].find(word) + word.length() - 1) << ")"
            << endl;
        }
    }
}

void buildDiagonals() {
    for (int i = 0; i < floor(DIAGONALS/4); i++)
    {
        for (int j = ROWS - (i + 2), k = 0; j < ROWS and k < COLUMNS; j++, k++)
        {
            diagonals[i] += grid[j][k];
        }
    }
    for (int i = ceil(DIAGONALS/4); i < DIAGONALS/2; i++)
    {
        for (int j = 0, k = i - (int) floor(DIAGONALS/4); j < ROWS and k < COLUMNS; j++, k++)
        {
            diagonals[i] += grid[j][k];
        }
    }
    for (int i = DIAGONALS/2; i < ceil(3*DIAGONALS/4); i++)
    {
        for (int j = i - (DIAGONALS/2 - 1), k = 0; j >= 0 and k < COLUMNS; j--, k++)
        {
            diagonals[i] += grid[j][k];
        }
    }
    for (int i = ceil(3*DIAGONALS/4); i < DIAGONALS; i++)
    {
        for (int j = ROWS - 1, k = i - (int) floor(3*DIAGONALS/4); j >= 0 and k < COLUMNS; j--, k++)
        {
            diagonals[i] += grid[j][k];
        }
    }

    for (int i = 0; i < DIAGONALS; i++)
    {
        for (int j = (int) diagonals[i].length() - 1; j >= 0; j--)
        {
            diagonalsR[i] += diagonals[i].substr(j,1);
        }
    }
}

void buildColumns()
{
    for (int i = 0; i < COLUMNS; i++)
    {
        for (int j = 0; j < ROWS; j++) // NOLINT(modernize-loop-convert)
        {
            columns[i] += grid[j][i];
        }
        for (int j = ROWS - 1; j >= 0; j--)
        {
            columnsR[i] += grid[j][i];
        }
    }
}

void buildRows() {
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            rows[i] += grid[i][j];
        }
        for (int j = COLUMNS - 1; j >= 0; j--)
        {
            rowsR[i] += grid[i][j];
        }
    }
}

void printGrid() {
    for (auto & i : grid)
    {
        for (char j : i)
            cout << j;
        cout << endl;
    }
}

void getGrid() {
    cout << "Please enter your grid of size " << ROWS << "-" << COLUMNS << ":" << endl;
    for (auto & i : grid)
    {
        for (char & j : i)
        {
            while (true)
            {
                char temp = (char) tolower(getch());
                if (regex_match(string{temp},regex("[a-z||A-Z]")))
                {
                    j = temp;
                    cout << (char) toupper(temp) << " ";
                    break;
                }
            }
        }

        cout << endl;
    }
}
