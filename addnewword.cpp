#include "addnewword.h"
#include "ui_addnewword.h"
#include "functions.h"
#include "main.h"

addNewWord::addNewWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewWord)
{

    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    ui->definitionInput->setEnabled(false);
}

addNewWord::~addNewWord()
{
    delete ui;
}


void addNewWord::on_pushButton_clicked()
{
    std::string keyword=convertTo(ui->wordInput->toPlainText());
    std::string definition=convertTo(ui->definitionInput->toPlainText());
    keyword[0]=toupper(keyword[0]); //viet hoa chu dau
    ProgramData::currentTree.addNewWordToDict(keyword,definition);
    saveAllTree(ProgramData::listOfTree);
    //ProgramData::listOfTree[currentSet].import_dictionary(currentSet);
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
        ui->definitionInput->setEnabled(false);
    }
    else{
        ui->pushButton->setEnabled(true);
        ui->status->setText("");
        ui->definitionInput->setEnabled(true);
    }
}

