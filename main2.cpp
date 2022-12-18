#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>

using namespace std;

const int ROWS = 5;
const int COLUMNS = 5;
char grid[ROWS][COLUMNS];
string rows[ROWS];
string rowsR[ROWS];
string columns[COLUMNS];
string columnsR[COLUMNS];

void getGrid();

void printGrid();

void buildColumns();
void buildRows();

void checkRows(const string& word, stringstream& ss);
void checkColumns(const string& word, stringstream& ss);

int main()
{
    getGrid();
    printGrid();
    buildRows();
    buildColumns();

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

        if (word.length() > COLUMNS)
        {
            continue;
        }

        checkRows(word, ss);
        checkColumns(word, ss);

        if (ss.str().length() > 0)
        {
            cout << word << ":" << endl;
            cout << ss.str();
        }
    }

    cout << "ENTER BACKSPACE TO EXIT" << endl;
    while ((char) getch() != '\b');
    return 0;
}

void checkColumns(const string& word, stringstream& ss) {
    for (int i = 0; i < COLUMNS; i++)
    {
        if (columns[i].find(word) != string::npos)
        {
            ss
            << "Found in column " << i + 1 << " "
            << "(" << columns[i].find(word) + 1 << ", " << i + 1 << ")"
            << " -> "
            << "(" << columns[i].find(word) + word.length() << ", " << i + 1 << ")"
            << endl;
        }
        if (columnsR[i].find(word) != string::npos)
        {
            ss
            << "Found reversed in column " << i + 1 << " "
            << "(" << ROWS - (columns[i].find(word) + 1) << ", " << i + 1 << ")"
            << " -> "
            << "(" << ROWS - (columns[i].find(word) + word.length()) << ", " << i + 1 << ")"
            << endl;
        }
    }
}

void checkRows(const string& word, stringstream& ss) {
    for (int i = 0; i < ROWS; i++)
    {
        if (rows[i].find(word) != string::npos)
        {
            ss
            << "Found in row " << i + 1 << " "
            << "(" << i + 1 << ", " << rows[i].find(word) + 1 << ")"
            << " -> "
            << "(" << i + 1 << ", " << rows[i].find(word) + word.length() << ")"
            << endl;
        }
        if (rowsR[i].find(word) != string::npos)
        {
            ss
            << "Found reversed in row " << i + 1 << " "
            << "(" << i + 1 << ", " << COLUMNS - (rowsR[i].find(word)) << ")"
            << " -> "
            << "(" << i + 1 << ", " << COLUMNS - (rowsR[i].find(word) + word.length() - 1) << ")"
            << endl;
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
            j = (char) getch();
            cout << j << " ";
        }

        cout << endl;
    }
}
