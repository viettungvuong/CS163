#include "history.h"
#include "ui_mainwindow.h"
extern int currentSet;
extern Favorite favorite;
extern History history;
extern std::vector<WordAndDef> v;
extern std::vector<WordAndDef> suggesting;
extern int selected1, selected2;
extern int chooseWord1,chooseWord2;
void guessRandomDefinition(TernarySearchTree& tree, bool nonWord, Ui::MainWindow* ui);
void guessRandomWord(TernarySearchTree& tree, bool nonWord, Ui::MainWindow* ui);
