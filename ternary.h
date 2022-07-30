#pragma once

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>

#define NUMofSET 3

struct WordAndDef {
    std::string word;
    std::string definition;
    bool operator ==(const WordAndDef& a) const
    {
        if (word != a.word)
            return false;
        if (definition != a.definition)
            return false;
        return true;
    }
};

struct LinkedListNode {
    WordAndDef wad;
    LinkedListNode* next = nullptr;
};

struct LinkedList {
    LinkedListNode* root = nullptr;
    void insert(WordAndDef wad);
    void display(const std::string& definition);
};

struct TernaryTreeNode
{
    char ch;
    TernaryTreeNode* left = nullptr, * mid = nullptr, * right = nullptr;
    std::string* definition = nullptr;
    std::string word = "";
};

class TernarySearchTree
{
public:

    TernarySearchTree();
    void deleteTree();
    void add2Tree(std::string keyword, std::string definition, bool importing = true);
    void editKeyword(TernaryTreeNode*& tem, std::string newDefinition);
    TernaryTreeNode* search4keyword(std::string keyword, bool normal = true, bool nonWord = false);
    void import_dictionary(int index, bool forReset = false);
    int size;
    TernaryTreeNode* getRandomWord(bool normal = true, int i = 0);
    TernaryTreeNode* getRandomWord2(bool normal = true, int i = 0);
    void guessRandomWord(bool nonWord = false);
    void guessRandomDefinition(bool nonWord = false); //nonword la danh cho slang va emotional
    void addNewWordToDict(std::string keyword, std::string definition); //them tu moi vao tu dien
    void deleteKeword(std::string keyword);
    TernaryTreeNode* getRoot();
    void inorderTraversal();
    std::vector<WordAndDef> search4Definition(std::string definition);
    std::pair<std::string, std::string> wordAndDefinition[4]; //de lam guess game
    void inorderTraversalForSuggest(TernaryTreeNode* node, std::string currentStr, std::vector<WordAndDef>& suggest);

private:
    void inorderTraversalAux(TernaryTreeNode* node, std::string currentStr);
    void inorderTraversalForSearch(TernaryTreeNode* node, std::string currentStr, std::string definition, std::vector<WordAndDef>& v);
    TernaryTreeNode* root = nullptr;

};
void updateWord(TernaryTreeNode*& tem, std::string newDefinition);

