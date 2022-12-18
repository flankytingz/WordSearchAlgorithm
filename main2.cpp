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

void getGrid();

void printGrid();

void buildRows();

void checkRows(const string& word, stringstream& ss);

int main()
{
    getGrid();
    printGrid();
    buildRows();

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

void checkRows(const string& word, stringstream& ss) {
    for (int i = 0; i < ROWS; i++)
    {
        if (rows[i].find(word) != string::npos)
        {
            ss << "Found in row " << i + 1 << endl;
        }
        if (rowsR[i].find(word) != string::npos)
        {
            ss << "Found reversed in row " << i + 1 << endl;
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
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = COLUMNS - 1; j >= 0; j--)
        {
            rowsR[i] += grid[i][j];
        }
    }
}

template <size_t size_x, size_t size_y>
void printGrid(string grid[size_x][size_y]) {
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
