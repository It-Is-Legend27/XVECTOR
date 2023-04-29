#include <iostream>
#include <fstream>
#include "Xvector.hpp"
#include <string>
using namespace std;

int main()
{
    ifstream infile;
    ofstream outfile;
    infile.open("dictionary.txt");
    outfile.open("test.txt");
    string word;
    Xvector<string> words;
    while (infile >> word)
    {
        words.push_back(word);
    }

    for (auto &&i : words)
    {
        outfile << i;
        if (i != *(words.end() - 1))
            outfile << '\n';
    }

    infile.close();
}