#include "WordSearch.hpp"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void usage();
void uppercaseWords(vector<string> &words);
void parseArgs(int argc, char **argv, size_t &size, string &showAnswer);
void emitJgraph(const vector<string> &grid,
                const vector<string> &words,
                const vector<vector<int>> &answers,
                string &showAnswers);

vector<string> readWords()
{
    vector<string> ret;
    string word;

    while (cin >> word)
    {
        ret.push_back(word);
    }

    uppercaseWords(ret);

    return ret;
}

int main(int argc, char **argv)
{
    size_t size;
    vector<string> words = readWords();
    vector<string> grid;
    vector<vector<int>> answers;
    WordSearch ws;
    string answerFile = "";

    try
    {
        parseArgs(argc, argv, size, answerFile);
        ws = WordSearch(size, words);
        ws.makeGrid();

        grid = ws.getGrid();
        answers = ws.getVacancies();
        emitJgraph(grid, words, answers, answerFile);
    }
    catch (invalid_argument &err)
    {
        cout << err.what() << endl;
        usage();
        return -1;
    }
    catch (runtime_error &err)
    {
        cout << err.what() << endl;
        return -1;
    }

    return 0;
}

void usage()
{
    printf("Usage: ./bin/MakeSearch -s{size} -a=showAnswer -h=help {words on stdin}\n");
}

void uppercaseWords(vector<string> &words)
{

    for (size_t i = 0; i < words.size(); i++)
    {
        for (size_t j = 0; j < words[i].size(); j++)
        {
            words[i][j] = toupper(words[i][j]);
        }
    }
}

void parseArgs(int argc, char **argv, size_t &size, string &answerFile)
{
    int c;
    int s = 0;
    bool aFlag = false;

    while ((c = getopt(argc, argv, "s:a:h")) != -1)
        switch (c)
        {
        case 'a':
            answerFile = optarg;
            aFlag = true;
            break;
        case 's':
            s = sscanf(optarg, "%ld", &size);
            break;
        case 'h':
            throw invalid_argument("Help requested!");
        case '?':
            throw invalid_argument("Unrecognized argument.");
        }

    if (!s)
    {
        throw invalid_argument("Invalid size specification.");
    }
    if (aFlag)
    {
        if (answerFile == "")
        {
            throw invalid_argument("No filename given");
        }
    }
}

void emitJgraph(const vector<string> &grid,
                const vector<string> &words,
                const vector<vector<int>> &answers,
                string &answerFile)
{
    FILE *fout;
    int counter;
    size_t fontSize = 60 - 20 * (grid.size() / 10);
    if (fontSize > 40)
    {
        fontSize = 40;
    }
    if (fontSize <= 0)
    {
        fontSize = 10;
    }

    if (answerFile != "")
    {
        fout = fopen(answerFile.c_str(), "w");
        if (!fout)
        {
            throw runtime_error("Can't open answerfile.");
        }

        fprintf(fout, "newgraph\n");
        fprintf(fout, "\ty_translate 4.0\n");
        fprintf(fout, "\txaxis nodraw min 0 max %ld size 6\n", grid.size());
        fprintf(fout, "\tyaxis nodraw min 0 max %ld size 6\n", grid.size());

        for (size_t i = 0; i < grid.size(); i++)
        {
            for (size_t j = 0; j < grid[i].size(); j++)
            {
                fprintf(fout, "\tnewstring fontsize %ld hjl vjc ", fontSize);
                if (!answers[i][j])
                {
                    fprintf(fout, "x %ld y %ld lcolor 0 1 0 : %c\n",
                            i,
                            grid.size() - j,
                            grid[i][j]);
                }
                else
                {
                    fprintf(fout, "x %ld y %ld : %c\n",
                            i,
                            grid.size() - j,
                            grid[i][j]);
                }
            }
        }

        fprintf(fout, "newgraph\n");
        fprintf(fout, "\ty_translate 1.0\n");
        fprintf(fout, "\txaxis nodraw min 0 max 8 size 6\n");
        fprintf(fout, "\tyaxis nodraw min 0 max 8 size 3\n");

        counter = 0;
        for (size_t i = 0; i < words.size(); i++)
        {
            if (i % 5 == 0 && i != 0)
            {
                counter++;
            }
            fprintf(fout, "\tnewstring fontsize 13 hjc vjc x %ld y %d : %s\n",
                    (i % 5) * 2,
                    counter,
                    words[i].c_str());
        }

        fclose(fout);
    }

    printf("newgraph\n");
    printf("\ty_translate 4.0\n");
    printf("\txaxis nodraw min 0 max %ld size 6\n", grid.size());
    printf("\tyaxis nodraw min 0 max %ld size 6\n", grid.size());

    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[i].size(); j++)
        {
            printf("\tnewstring fontsize %ld hjl vjc ", fontSize);
            printf("x %ld y %ld : %c\n",
                   i,
                   grid.size() - j,
                   grid[i][j]);
        }
    }

    printf("newgraph\n");
    printf("\ty_translate 1.0\n");
    printf("\txaxis nodraw min 0 max 8 size 6\n");
    printf("\tyaxis nodraw min 0 max 8 size 3\n");

    counter = 0;
    for (size_t i = 0; i < words.size(); i++)
    {
        if (i % 5 == 0 && i != 0)
        {
            counter++;
        }
        printf("\tnewstring fontsize 13 hjc vjc x %ld y %d : %s\n",
               (i % 5) * 2,
               counter,
               words[i].c_str());
    }
}