#include "editword.h"
#include "ui_editword.h"
#include "functions.h"

void changeWord(TernarySearchTree tree, std::string changingWord, Ui::editWord* ui, Ui::MainWindow* main) {
    TernaryTreeNode* find = tree.search4keyword(changingWord);
    updateWord(find, convertTo(ui->textEdit->toPlainText())); //la tim duoc cai tu dang can chuyen (changWord) sang ui->textEdit->Text
    if (main->currentWord->text()==convertFrom(changingWord))
        main->definition->setText(ui->textEdit->toPlainText()); //cap nhat tai cho luon
}

editWord::editWord(const std::string& wordToChange, Ui::MainWindow *main, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editWord)
{
    this->main=main;
    ui->setupUi(this);
    changingWord=wordToChange;
    ui->currentWord->setText(convertFrom(changingWord));
    ui->pushButton->setEnabled(false);
        this->setFixedSize(QSize(400,300));
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
    changeWord(ProgramData::currentTree, changing, ui, main);
    saveAllTree(ProgramData::listOfTree);
    this->close(); //an cua so lai
}


