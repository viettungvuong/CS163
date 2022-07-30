#include "editword.h"
#include "ui_editword.h"
#include "functions.h"

void changeWord(TernarySearchTree tree, std::string changingWord, Ui::editWord* ui) {
    TernaryTreeNode* find = tree.search4keyword(changingWord);
    updateWord(find, convertTo(ui->textEdit->toPlainText())); //la tim duoc cai tu dang can chuyen (changWord) sang ui->textEdit->Text
}

editWord::editWord(const std::string& wordToChange, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editWord)
{
    ui->setupUi(this);
    changingWord=wordToChange;
}

editWord::~editWord()
{
    delete ui;
}

void editWord::on_textEdit_textChanged()
{
    if (ui->textEdit->toPlainText().length()!=0)
        ui->pushButton->setEnabled(true);
    else
        ui->pushButton->setEnabled(false);
}


void editWord::on_pushButton_clicked()
{
    std::string changing = changingWord; //lay tu dang chon de chinh sua
    changeWord(ProgramData::currentTree, changing, ui);
    saveAllTree(ProgramData::listOfTree);
    this->hide(); //an cua so lai
}


