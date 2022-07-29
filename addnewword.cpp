#include "addnewword.h"
#include "ui_addnewword.h"

addNewWord::addNewWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewWord)
{
    ui->setupUi(this);
}

addNewWord::~addNewWord()
{
    delete ui;
}
