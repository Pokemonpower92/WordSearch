#include "WordSearch.hpp"
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// Constructors.
WordSearch::WordSearch()
{
    this->size = 0;
    this->words = {};
}

WordSearch::WordSearch(size_t size, std::vector<std::string> words)
{
    int maxWordSize = 0;

    // See if the largest word will fit in the grid.
    for (size_t i = 0; i < words.size(); i++) {
        if (words[i].size() > maxWordSize) {
            maxWordSize = words[i].size();
        }
    }

    if (maxWordSize > size) {
        throw invalid_argument("Grid not large enough.");
    }

    this->size = size;
    this->words = words;
    this->makeMaps();
}

// Helpers
// Make the mapes for availible words
// and indecies.
void WordSearch::makeMaps()
{
    size_t index;

    // wordMap.
    for (size_t i = 0; i < this->words.size(); i++) {
        this->wordMap.insert(make_pair(i, this->words[i]));
    }

    // indexMap
    for (size_t i = 0; i < this->size; i++) {
        for (size_t j = 0; j < this->size; j++) {
            index = i * size + j;
            this->indexMap.insert(make_pair(index, NULL));
        }
    }
}

void WordSearch::printMaps()
{
    size_t i, j;

    cout << "Words:" << endl;
    for (auto mit = this->wordMap.begin(); mit != this->wordMap.end(); mit++) {
        printf("\tNumber: %ld, ", mit->first);
        printf("\tWord: %2s\n", mit->second.c_str());
    }

    cout << "Free indices: " << endl;
    for (auto mit = this->indexMap.begin(); mit != this->indexMap.end(); mit++) {
        j = mit->first % this->size;
        i = (mit->first - j) / this->size;

        printf("\t%ld, %ld\n", i, j);
    }
}

// Accessors
size_t WordSearch::getSize() const
{
    return this->size;
}

std::vector<std::string> WordSearch::getWords() const
{
    return this->words;
}

std::vector<std::string> WordSearch::getGrid() const
{
    return this->grid;
}

// Makes the grid. Throws something on failures.
void WordSearch::makeGrid()
{
}