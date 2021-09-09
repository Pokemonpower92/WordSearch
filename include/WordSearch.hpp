#pragma ONCE
#include <iostream>
#include <unordered_map>
#include <vector>

class WordSearch {
private:
    std::vector<std::string> words; // Words in the search.
    std::vector<std::string> grid; // The grid.
    size_t size; // Number of rows and cols in the grid.
    std::unordered_map<size_t, std::string> wordMap; // Words we need to place.
    std::unordered_map<size_t, size_t> indexMap; // Free indices.

    // Helpers
    void makeMaps();
    void printMaps();

public:
    // Constructors.
    WordSearch();
    WordSearch(size_t size, std::vector<std::string> words);

    // Accessors
    size_t getSize() const;
    std::vector<std::string> getWords() const;
    std::vector<std::string> getGrid() const;

    // Makes the grid. Throws something on failures.
    void makeGrid();
};