#ifndef EDITWORD_H
#define EDITWORD_H

#include "ui_mainwindow.h"
#include <QDialog>

namespace Ui {
class editWord;
}

class editWord : public QDialog
{
    Q_OBJECT

public:
    explicit editWord(const std::string& wordToChange, Ui::MainWindow *main, QWidget *parent = nullptr);
    ~editWord();

private slots:
    void on_textEdit_textChanged();

    void on_pushButton_clicked();

private:
    std::string changingWord;
    Ui::editWord *ui;
    Ui::MainWindow *main;
};

#endif // EDITWORD_H
