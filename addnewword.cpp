#include "addnewword.h"
#include "ui_addnewword.h"
#include "functions.h"

addNewWord::addNewWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewWord)
{
    ui->pushButton->setEnabled(false);
    ui->setupUi(this);
}

addNewWord::~addNewWord()
{
    delete ui;
}


void addNewWord::on_pushButton_clicked()
{
    std::string keyword=convertTo(ui->wordInput->toPlainText());
    std::string definition=convertTo(ui->definitionInput->toPlainText());
    ProgramData::currentTree.addNewWordToDict(keyword,definition);
    saveAllTree(ProgramData::listOfTree);
    this->close();
}


void addNewWord::on_wordInput_textChanged()
{
    //de kiem tra tu da co trong tu dien hay chua
    if (ProgramData::currentTree.search4keyword(convertTo(ui->wordInput->toPlainText()))){ //tu da co trong tu dien
        ui->pushButton->setEnabled(false);
        QPalette palette = ui->status->palette();
        palette.setColor(ui->status->backgroundRole(), Qt::red);
        palette.setColor(ui->status->foregroundRole(), Qt::red);
        ui->status->setPalette(palette); //chinh no thanh mau do
        ui->status->setText("Word is already in dictionary");
    }
    else{
        ui->pushButton->setEnabled(true);
        ui->status->setText("");
    }
}

