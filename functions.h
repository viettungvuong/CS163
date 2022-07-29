#pragma once

#include "ternary.h"
#include <string.h>
#include <vector>

#include "ui_mainwindow.h"

class ProgramData {
public :static TernarySearchTree currentTree;
       static TernarySearchTree listOfTree[3];
};
void deletetree(TernaryTreeNode* root);

void createSet(TernarySearchTree* listOfTree);
int childOfNode(TernaryTreeNode* node);
void saveTree(TernaryTreeNode* root, int index);
void saveAllTree(TernarySearchTree* listOfTree);
void resetAllDictionary(TernarySearchTree* listOfTree);
void changeSet(int& currentSet);
std::string convertTo(QString input);
QString convertFrom(std::string input);
void v2ListView(std::vector<WordAndDef> v, QListWidget* lb);
std::vector<WordAndDef> suggestWords(std::string soFar);

bool fileExists(const std::string& name);
void load(Ui::MainWindow* ui);
void wordOfTheDay(Ui::MainWindow* ui);
