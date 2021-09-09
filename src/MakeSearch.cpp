#include "WordSearch.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void usage()
{
    printf("Usage: ./bin/MakeSearch size {words on stdin}\n");
}

size_t checkSize(int argc, char** argv)
{
    size_t size;

    if (argc != 2) {
        usage();
        throw invalid_argument("Bad size specification");
    }

    if (!sscanf(argv[1], "%zu", &size)) {
        throw invalid_argument("Rows not a non-negative integer");
    }

    return size;
}

vector<string> readWords()
{
    vector<string> ret;
    string word;

    while (cin >> word) {
        ret.push_back(word);
    }

    return ret;
}

int main(int argc, char** argv)
{
    size_t size;
    vector<string> words = readWords();
    WordSearch ws;

    try {
        size = checkSize(argc, argv);
        ws = WordSearch(size, words);

        cout << "Size: ";
        cout << ws.getSize() << endl;

        words = ws.getWords();
        cout << "Words: " << endl;
        for (int i = 0; i != words.size(); i++) {
            cout << "\t" << words[i] << endl;
        }

    } catch (invalid_argument& err) {
        cout << "Invalid arguments specified." << endl;
        cout << err.what() << endl;
        usage();
        return -1;
    }

    return 0;
}