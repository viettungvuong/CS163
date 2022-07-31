#pragma once
#include <vector>
#include "ternary.h"

class History {
public:
    std::vector<WordAndDef> words;
    std::vector<int> dictionaryNo;
    void initDefinition(); //ham de them def khi load
    void saveToFile();
    void loadFromFile();
    void addToHistory(WordAndDef wad, int dictionaryNo);
    void refresh(std::string keyword);
    void reset();
};


class Favorite {
public:
    std::vector<WordAndDef> words;
    std::vector<int> dictionaryNo;
    void initDefinition(); //ham de them def khi load
    void saveToFile();
    void loadFromFile();
    void refresh(std::string keyword);
    void reset();
};

