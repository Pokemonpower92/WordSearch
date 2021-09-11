#include "WordSearch.hpp"
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include <vector>

using namespace std;

// ########### Constructors.
WordSearch::WordSearch()
{
    this->size = 0;
    this->words = {};
}

WordSearch::WordSearch(size_t size, std::vector<std::string> words)
{
    int maxWordSize = 0;

    srand(time(NULL));

    // See if the largest word will fit in the grid.
    for (size_t i = 0; i < words.size(); i++)
    {
        if (words[i].size() > maxWordSize)
        {
            maxWordSize = words[i].size();
        }
    }

    if (maxWordSize > size)
    {
        throw invalid_argument("Grid not large enough.");
    }

    this->size = size;
    this->words = words;

    // Initialize the wordMap and the grid.
    for (size_t i = 0; i < this->words.size(); i++)
    {
        this->wordMap.insert(make_pair(this->words[i], NULL));
    }

    this->grid.resize(this->size, string(this->size, '-'));
    this->makeVacancies();
}

// ########### Helpers

// Make the map for the availible starting indices
// for word. If there were no vacancies this method returns
// false.
bool WordSearch::findVacancies(const string &word)
{
    int counter = 0;

    this->startingPlaces.clear();

    for (size_t i = 0; i < this->size; i++)
    {
        for (size_t j = 0; j < this->size; j++)
        {
            if (this->vacancies[i][j] || grid[i][j] == word[0])
            {
                this->startingPlaces.push_back(make_pair(i, j));
            }
        }
    }

    return this->startingPlaces.size() != 0;
}

// Can a word fit in the grid with starting spot index with the given oreintation.
bool WordSearch::fitWord(pair<size_t, size_t> index, char orient, const string &word)
{
    size_t row = index.first;
    size_t col = index.second;
    bool flag = false;

    switch (orient)
    {
    case 'v':
        // If there's enough room in general.
        if ((this->size - row) < word.size())
            break;

        // See if all the spaces are either vacant or match the word.
        for (size_t i = row; i < row + word.size(); i++)
        {
            if (!this->vacancies[i][col] && this->grid[i][col] != word[i - row])
            {
                flag = true;
            }
        }

        if (flag)
            break;

        // Place the word.
        for (size_t i = row; i < row + word.size(); i++)
        {
            this->grid[i][col] = word[i - row];
            this->vacancies[i][col] = 0;
        }

        return true;
    case 'h':
        // If there's enough room in general.
        if ((this->size - col) < word.size())
            break;

        // See if all the spaces are either vacant or match the word.
        for (size_t i = col; i < col + word.size(); i++)
        {
            if (!this->vacancies[row][i] && this->grid[row][i] != word[i - col])
            {
                flag = true;
            }
        }

        if (flag)
            break;

        // Place the word.
        for (size_t i = col; i < col + word.size(); i++)
        {
            this->grid[row][i] = word[i - col];
            this->vacancies[row][i] = 0;
        }

        return true;
    case 'd':
        // If there's enough room in general.
        if ((this->size - col) < word.size() || (this->size - row) < word.size())
            break;

        // See if all the spaces are either vacant or match the word.
        size_t j = row;
        for (size_t i = col; i < col + word.size(); i++)
        {
            if (!this->vacancies[j][i] && this->grid[j][i] != word[i - col])
            {
                flag = true;
            }
            j++;
        }

        if (flag)
            break;

        // Place the word.
        j = row;
        for (size_t i = col; i < col + word.size(); i++)
        {
            this->grid[j][i] = word[i - col];
            this->vacancies[j][i] = 0;
            j++;
        }

        return true;
    }

    return false;
}

// Try to place the word at the starting place index for a random oreintation.
// Try all oreintations in a random order until one works.
// If one works place the word in the grid and return true.
// If all orientations are exhausted then return false.
bool WordSearch::placeWord(pair<size_t, size_t> index, const string &word)
{
    // v=vertical; h=horizontal; d=diagonal
    vector<char> orientations = {'v', 'h', 'd'};
    size_t randomIndex;

    while (orientations.size())
    {
        randomIndex = rand() % orientations.size();

        if (this->fitWord(index, orientations[randomIndex], word))
        {
            return true;
        }
        else
        {
            orientations.erase(orientations.begin() + randomIndex);
        }
    }

    return false;
}

void WordSearch::printMaps() const
{
    size_t i, j;

    cout << "Words:" << endl;
    for (auto mit = this->wordMap.begin(); mit != this->wordMap.end(); mit++)
    {
        printf("\tWord: %2s\n", mit->first.c_str());
    }

    cout << "Free indices: " << endl;
    for (size_t i = 0; i < this->startingPlaces.size(); i++)
    {
        cout << "i: " << this->startingPlaces[i].first << ", ";
        cout << "j: " << this->startingPlaces[i].second << endl;
    }
}

void WordSearch::makeVacancies()
{
    this->vacancies.clear();
    this->vacancies.resize((this->size), vector<int>(this->size, 1));
}

// Fill the vacant indicies with random characters.
void WordSearch::fillGrid()
{
    for (size_t i = 0; i < this->vacancies.size(); i++)
    {
        for (size_t j = 0; j < this->vacancies[i].size(); j++)
        {
            if (this->vacancies[i][j])
            {
                this->grid[i][j] = 'A' + (rand() % 26);
            }
        }
    }
}

// ########### Accessors
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

std::vector<std::vector<int>> WordSearch::getVacancies() const
{
    return this->vacancies;
}

// Makes the grid. Throws something on failures.
void WordSearch::makeGrid()
{
    string word;
    size_t randomIndex;
    bool placed, retry;
    pair<size_t, size_t> startingSpot;
    unordered_map<string, int> tempWordMap;
    vector<pair<size_t, size_t>> tempStartingPlaces;

    // Pull a random word off the wordMap
    // And place it into the grid randomly
    // until there are no more words.

    // Keep doing this until we find a valid
    // permutation of the grid.
    for (;;)
    {
        retry = false;
        tempWordMap = this->wordMap;
        this->makeVacancies();

        while (tempWordMap.size())
        {
            auto randomWord = tempWordMap.begin();
            advance(randomWord, rand() % tempWordMap.size());
            word = randomWord->first;
            placed = false;

            // Find all possible starting indices
            if (!this->findVacancies(word))
            {
                throw runtime_error("Couldn't add word: " + word);
            }

            tempStartingPlaces = this->startingPlaces;
            while (tempStartingPlaces.size())
            {
                randomIndex = rand() % tempStartingPlaces.size();
                startingSpot = tempStartingPlaces[randomIndex];

                if (this->placeWord(startingSpot, word))
                {
                    placed = true;
                    break;
                }
                else
                {
                    tempStartingPlaces.erase(tempStartingPlaces.begin() + randomIndex);
                }
            }

            if (!placed)
            {
                retry = true;
                break;
            }

            tempWordMap.erase(randomWord);
        }

        if (!retry)
        {
            break;
        }
    }
    this->fillGrid();
}