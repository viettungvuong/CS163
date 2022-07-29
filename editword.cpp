#include "editword.h"
#include "ui_editword.h"

editWord::editWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editWord)
{
    ui->setupUi(this);
}

editWord::~editWord()
{
    delete ui;
}
