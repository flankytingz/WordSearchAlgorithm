#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
/*
 * References
 * https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
 * https://en.cppreference.com/w/cpp/20
 * */

const auto ROWS = 5;
const auto COLUMNS = 5;

// Getting the rows
void getRows(std::string rows[ROWS])
{
    std::cout << "Enter the rows of text: " << std::endl;

    // Iterating over rows
    for (int i = 0; i < ROWS; i++)
    {
        bool lastKeyIsBackspace = false;
        // Iterating over the columns
        for (int j = 0; j < COLUMNS; j++)
        {

            // Prints the spacing automatically so all user has to do is enter the words

            int input = getch();

            // Handling backspace for new line
            if (input == 8 and j == 0 and i > 0)
            {
                // Moving to saved cursor position, moving cursor back twice, then clearing the line
                std::cout << "\033[u" << "\b\b" << "\033[K" << std::flush;

                // moving row back
                i--;
                // moving to last word and -1 to cancel out addition
                j = COLUMNS - 2;

                continue;
            }

            // Handling backspace after backspace
            if (lastKeyIsBackspace and input == 8 and j > 0)
            {
                // Moving cursor back twice then clearing the line
                std::cout << "\b\b" << "\033[K" << std::flush;

                // Decreases J by 2 because we need to go back two iterations, one for backspace, one for previous letter
                j -= 2;

                lastKeyIsBackspace = true;

                rows[i].replace(rows[i].length()-1,1,"");
                continue;
            }

            // Handling backspace
            if (input == 8 and j > 0)
            {
                // Moving cursor back twice then clearing the line
                std::cout << "\b\b" << "\033[K" << std::flush;

                // Decreases J by 2 because we need to go back two iterations, one for backspace, one for previous letter
                j -= 2;

                lastKeyIsBackspace = true;

                rows[i].replace(rows[i].length()-1,1,"");
                continue;
            }

            char letter = (char) tolower(input);

            // Skips non-alphabetical entries
            switch (letter)
            {
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
                    std::cout << (char) toupper(letter) << " " << std::flush;
                    rows[i] += letter;

                    lastKeyIsBackspace = false;

                    break;

                default:
                    // Ignores this input

                    lastKeyIsBackspace = false;

                    j--;
                    break;
            }

        }
        std::cout << "\033[s" << std::endl << std::flush;
    }
}

void printGrid(std::string rows[], const int mode)
{
    switch (mode)
    {
        case 0:
            for (int i = 0; i < ROWS; i++)
            {
                std::string temp = rows[i];

                for (char j : temp)
                    std::cout << (char) toupper(j) << " ";

                std::cout << std::endl;
            }
            break;
        case 1:
            for (int i = 0; i < ROWS; i++)
                std::cout << rows[i] << std::endl;
            break;
        default:
            break;
    }
}

void printCoords(const std::string& word, const int x, const int y, const int mode)
{

    switch (mode)
    {
        case 0:
            std::cout << word << " from (" << x << ", " << y << ") till (" << x + (int) word.length() - 1 << ", " << y << ")" << std::endl;
            break;
        case 1:
            std::cout << word << " from (" << x << ", " << y << ") till (" << x << ", " << y + (int) word.length() - 1 << ")" << std::endl;
            break;
        default:
            break;
    }
}

int main() {
    std::string rows[ROWS];
    std::string columns[COLUMNS];
    std::cout << "Hello, World!" << std::endl;

    getRows(rows);

    // filling column arrays
    for (int i = 0; i < COLUMNS; i++)
    {
        std::string temp;

        for (int j = 0; j < ROWS; j++)
        {
            temp += rows[j].substr(i, 1);
        }

        columns[i] = temp;
    }

    std::ifstream wordList;

    wordList.open(R"(C:\Users\Flanky\CLionProjects\CS101_A3\wordlist.txt)");

    std::string word;

    if (wordList.is_open())
    {

        // Iterating for each word
        while (!wordList.eof())
        {
            wordList >> word;

            // Iterating over rows
            for (int i = 0; i < ROWS; i++)
            {
                // Finds all the occurrences of a word horizontally
                for (int j = 0; j < rows[i].length(); j++)
                {
                    // Starts finding the word from the point in the string
                    unsigned long long int pos = rows[i].find(word, j);

                    // Checks if string is found, if not found pos = npos.
                    if (pos != std::string::npos)
                    {
                        // Prints the co-ordinates
                        printCoords(word,(int) pos + 1,i+1,0);
                        // Moving search to after the word
                        j = (int) pos + (int) word.length() - 1;
                    }
                }
            }

            // Iterating over columns
            for (int i = 0; i < COLUMNS; i++)
            {

                // Finding substrings
                for (int j = 0; j < columns[i].length(); j++)
                {
                    // Starts finding the word from the point in the string
                    unsigned long long int pos = columns[i].find(word, j);

                    // Checks if string is found, if not found pos = npos.
                    if (pos != std::string::npos)
                    {
                        // Prints the co-ordinates
                        printCoords(word, i + 1, (int) pos + 1, 1);

                        // Moving search to after the word
                        j = (int) pos + (int) word.length() - 1;
                    }
                }
            }
        }

        wordList.close();
    }
    else
        std::cout << "Unable to open file" << std::endl;

    // Pauses the terminal
    getch();

    return 0;
}