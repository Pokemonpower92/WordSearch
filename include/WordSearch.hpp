#pragma ONCE
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

class WordSearch
{
private:
    size_t size; // Number of rows and cols in the grid.

    std::vector<std::string> words;                        // Words in the search.
    std::vector<std::string> grid;                         // The grid.
    std::vector<std::vector<int>> vacancies;               // If a character of a word is in this index.
    std::vector<std::pair<size_t, size_t>> startingPlaces; // Indicies where a word can start
    std::unordered_map<std::string, int> wordMap;          // Words we need to place.

    // Helpers
    bool findVacancies(const std::string &word);
    bool fitWord(std::pair<size_t, size_t> index, char orient, const std::string &word);
    bool placeWord(std::pair<size_t, size_t> index, const std::string &word);
    void makeVacancies();
    void fillGrid();
    void printMaps() const;

public:
    // Constructors.
    WordSearch();
    WordSearch(size_t size, std::vector<std::string> words);

    // Accessors
    size_t getSize() const;
    std::vector<std::string> getWords() const;
    std::vector<std::string> getGrid() const;
    std::vector<std::vector<int>> getVacancies() const;

    // Makes the grid.
    void makeGrid();
};