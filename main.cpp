#include "functions.h"
#include "mainwindow.h"
#include "ternary.h"
#include <QApplication>
#include "main.h"
int currentSet=2;
int selected1=-1;
int selected2=-1;
Favorite favorite;
History history;
std::vector<WordAndDef> v;
std::vector<WordAndDef> suggesting;
int chooseWord1;
int chooseWord2;

void guessRandomWord(TernarySearchTree& tree, bool nonWord, Ui::MainWindow* ui) {
    for (int i = 0; i < 4; i++) {
        if (nonWord)
            tree.getRandomWord2(false, i);
        else
            tree.getRandomWord(false, i);
    }
    chooseWord1 = rand() % 4;
    std::string show = tree.wordAndDefinition[chooseWord1].second;
    ui->guess->setText(convertFrom(show));
    for (int i = 0; i < 4; i++) {
        QRadioButton* selected;
        switch (i) {
        case 0: {
            selected = ui->radioButton;
            break; }
        case 1: {
            selected = ui->radioButton_2;
            break; }
        case 2: {
            selected = ui->radioButton_3;
            break;
        }
        default: {
            selected = ui->radioButton_4;
            break;
        }
        }
        selected->setText(convertFrom(tree.wordAndDefinition[i].first));
    }

    //tu dung la wordAndDefinition[chooseWord].first

}

void guessRandomDefinition(TernarySearchTree& tree, bool nonWord, Ui::MainWindow* ui) {
    for (int i = 0; i < 4; i++) {
        if (nonWord)
            tree.getRandomWord2(false, i);
        else
            tree.getRandomWord(false, i);
    }
    chooseWord2 = rand() % 4;
    std::string show = tree.wordAndDefinition[chooseWord2].first;
    ui->guess2->setText(convertFrom(show));
    for (int i = 0; i < 4; i++) {
        QRadioButton* selected;
        switch (i) {
        case 0: {
            selected = ui->radioButton_5;
            break; }
        case 1: {
            selected = ui->radioButton_6;
            break; }
        case 2: {
            selected = ui->radioButton_7;
            break;
        }
        default: {
            selected = ui->radioButton_8;
            break;
        }
        }
        selected->setText(convertFrom(tree.wordAndDefinition[i].second));
    }

    //tu dung la wordAndDefinition[chooseWord].second

}
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    qDebug() << "App path : " << qApp->applicationDirPath();
    MainWindow w;
    w.show();
    return a.exec();
}
