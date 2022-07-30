#include "mainwindow.h"
#include "addnewword.h"
#include "editword.h"
#include "functions.h"
#include "main.h"
#include <QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    load(ui);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);

    ui->radioButton->setEnabled(false);
    ui->radioButton_2->setEnabled(false);
    ui->radioButton_3->setEnabled(false);
    ui->radioButton_4->setEnabled(false);
    ui->radioButton_5->setEnabled(false);
    ui->radioButton_6->setEnabled(false);
    ui->radioButton_7->setEnabled(false);
    ui->radioButton_8->setEnabled(false);

    ui->favoriteList->setCurrentRow(0);
    ui->historyList->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_3_clicked()
{
    TernaryTreeNode* find = ProgramData::currentTree.search4keyword(convertTo(ui->searchBar->toPlainText()));
            if (!find || !find->definition) {
                ui->definition->setText("Not found");
                return;
            }

            //neu tu co trong tu dien
            ui->currentWord->setText(ui->searchBar->toPlainText());
            std::string def = *find->definition;
            ui->definition->setText(convertFrom(def));
            ui->pushButton_4->setEnabled(true);
            ui->pushButton_5->setEnabled(true);


            ui->suggestingWords->clear();
            std::vector<WordAndDef> v = suggestWords(convertTo(ui->searchBar->toPlainText()));
            for (auto s : v) {
                ui->suggestingWords->addItem(convertFrom(s.word));
            }
            suggesting = v;

            WordAndDef wad;
            wad.word = convertTo(ui->searchBar->toPlainText());
            wad.definition = def;
            history.addToHistory(wad, currentSet); //them vao history
                    v2ListView(history.words, ui->historyList);
}


void MainWindow::on_searchBar_textChanged()
{
    ui->suggestingWords->clear();
    std::vector<WordAndDef> v = suggestWords(convertTo(ui->searchBar->toPlainText()));
    for (auto s : v) {
        ui->suggestingWords->addItem(convertFrom(s.word));
    }
    suggesting = v;
}


void MainWindow::on_radioButton_clicked()
{
    selected1=0;
}


void MainWindow::on_radioButton_2_clicked()
{
    selected1=1;
}


void MainWindow::on_radioButton_3_clicked()
{
    selected1=2;
}


void MainWindow::on_radioButton_4_clicked()
{
    selected1=3;
}


void MainWindow::on_radioButton_5_clicked()
{
    selected2=0;
}


void MainWindow::on_radioButton_6_clicked()
{
    selected2=1;
}


void MainWindow::on_radioButton_7_clicked()
{
    selected2=2;
}


void MainWindow::on_radioButton_8_clicked()
{
    selected2=3;
}





void MainWindow::on_removeFavorite_clicked()
{
    if (ui->favoriteList->currentIndex().row()!=-1) {
            int i = ui->favoriteList->currentIndex().row();
            delete ui->favoriteList->takeItem(ui->favoriteList->currentRow());
            favorite.words.erase(favorite.words.begin() + i);
            favorite.dictionaryNo.erase(favorite.dictionaryNo.begin() + i);
            favorite.saveToFile();
            v2ListView(favorite.words, ui->favoriteList);
        }
}




void MainWindow::on_removeHistory_clicked()
{
    if (ui->historyList->currentIndex().row()!=-1) {
            int i = ui->historyList->currentIndex().row();
            delete ui->historyList->takeItem(ui->historyList->currentRow());
            history.words.erase(history.words.begin() + i);
            history.dictionaryNo.erase(history.dictionaryNo.begin() + i);
            history.saveToFile();
            v2ListView(favorite.words, ui->historyList);
        }
}


void MainWindow::on_historyList_currentRowChanged(int currentRow)
{
    if (history.words.size() > 0) {
            ui->definition_3->setText(convertFrom(history.words[currentRow].definition)); //xuat definition khi dc chon
        }
        if (currentRow != -1) {
            ui->clearAll->setEnabled(true);
            ui->removeHistory->setEnabled(true);
        }
        else
        {
            ui->clearAll->setEnabled(false);
            ui->removeHistory->setEnabled(false);
        }
}


void MainWindow::on_suggestingWords_currentRowChanged(int currentRow)
{
    if (currentRow!=-1) {
            int i = currentRow;
            ui->currentWord->setText(convertFrom(suggesting[i].word));
            ui->definition->setText(convertFrom(suggesting[i].definition));
            ui->searchBar->setText(convertFrom(suggesting[i].word));
            WordAndDef wad;
            wad.word = convertTo(ui->searchBar->toPlainText());
            wad.definition = convertTo(ui->definition->text());
            history.addToHistory(wad, currentSet); //them vao history
            v2ListView(history.words, ui->historyList);
            ui->pushButton_4->setEnabled(true);
            ui->pushButton_5->setEnabled(true);
            ui->suggestingWords->clear();
        }
        else
        {
            ui->pushButton_4->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
        }
}


void MainWindow::on_favoriteList_currentRowChanged(int currentRow)
{
    if (currentRow != -1) {
        ui->removeFavorite->setEnabled(true);
        ui->definition_2->setText(convertFrom(favorite.words[currentRow].definition));
    }
    else
    {
        ui->removeFavorite->setEnabled(false);
    }
}


void MainWindow::on_clearAll_clicked()
{
        history.words.clear();
        ui->historyList->clear();
        history.dictionaryNo.clear();
        history.saveToFile();
        v2ListView(history.words, ui->historyList);
        ui->definition_3->setText("");
}


void MainWindow::on_pushButton_clicked()
{
    ui->pushButton_7->setEnabled(true);
    ui->radioButton->setEnabled(true);
    ui->radioButton_2->setEnabled(true);
    ui->radioButton_3->setEnabled(true);
    ui->radioButton_4->setEnabled(true);
    guessRandomWord(ProgramData::listOfTree[2],false,ui);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton_6->setEnabled(true);
    ui->radioButton_5->setEnabled(true);
    ui->radioButton_6->setEnabled(true);
    ui->radioButton_7->setEnabled(true);
    ui->radioButton_8->setEnabled(true);
    guessRandomDefinition(ProgramData::listOfTree[2],false,ui);
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->answer->setAutoFillBackground(true);
    if (selected1 != -1 && selected1 == chooseWord1) //dung
    {
           QPalette palette = ui->answer->palette();
           palette.setColor(ui->answer->backgroundRole(), Qt::green);
           palette.setColor(ui->answer->foregroundRole(), Qt::green);
           ui->answer->setPalette(palette);
           ui->answer->setText("Correct answer!");
    }
    else {
          QPalette palette = ui->answer->palette();
          palette.setColor(ui->answer->backgroundRole(), Qt::red);
          palette.setColor(ui->answer->foregroundRole(), Qt::red);
          ui->answer->setPalette(palette);
          ui->answer->setText(convertFrom("Wrong answer. The correct answer is " + ProgramData::currentTree.wordAndDefinition[chooseWord1].first));
    }
    ui->pushButton_7->setEnabled(false);
    selected1 = -1;
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->answer2->setAutoFillBackground(true);
    if (selected2 != -1 && selected2 == chooseWord2) //dung
    {
           QPalette palette = ui->answer2->palette();
           palette.setColor(ui->answer2->backgroundRole(), Qt::green);
           palette.setColor(ui->answer2->foregroundRole(), Qt::green);
           ui->answer2->setPalette(palette);
           ui->answer2->setText("Correct answer!");
    }
    else {
          QPalette palette = ui->answer2->palette();
          palette.setColor(ui->answer2->backgroundRole(), Qt::red);
          palette.setColor(ui->answer2->foregroundRole(), Qt::red);
          ui->answer2->setPalette(palette);
          ui->answer2->setText(convertFrom("Wrong answer. The correct answer is " + ProgramData::currentTree.wordAndDefinition[chooseWord2].second));
    }
    ui->pushButton_6->setEnabled(false);
    selected2 = -1;
}


void MainWindow::on_comboBox_currentIndexChanged(int index) //chinh dataset
{
    currentSet = index; //2 la index cua listOfTree
    /*ProgramData::listOfTree[currentSet].import_dictionary(currentSet);*/
    ProgramData::currentTree = ProgramData::listOfTree[currentSet];
    //wordOfTheDay(ui);
    ui->searchBar->clear();
    suggesting.clear();
    ui->suggestingWords->clear();
    QFile f;
    f.setFileName(qApp->applicationDirPath()+"/currentSet.txt");
    f.open(QIODevice::WriteOnly);
        QTextStream ofs(&f);
        ofs<<currentSet;

    f.close();
}


void MainWindow::on_resetDictionary_clicked()
{
    resetAllDictionary(ProgramData::listOfTree);
    saveAllTree(ProgramData::listOfTree);
}


void MainWindow::on_pushButton_8_clicked()
{
    v = (ProgramData::currentTree).search4Definition(convertTo(ui->searchBar_2->toPlainText()));
    v2ListView(v, ui->suggestingWords2);
}


void MainWindow::on_suggestingWords2_currentRowChanged(int currentRow)
{
    if (v.size() > 0) {
        ui->currentWord_2->setText(convertFrom(v[currentRow].word));
          ui->definition2->setText(convertFrom(v[currentRow].definition)); //xuat definition khi dc chon
          WordAndDef wad;
          wad.word = convertTo(ui->searchBar->toPlainText());
          wad.definition = v[currentRow].definition;
          history.addToHistory(wad, currentSet); //them vao history
          v2ListView(history.words, ui->historyList);
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    bool found = false;
    std::string selectedWord=convertTo(ui->searchBar->toPlainText());
    for (int i = 0; i < favorite.words.size(); i++) {
         if (favorite.words[i].word == selectedWord) {
             found = true;
             break;
         }
    }
    if (!found) {
            WordAndDef wad;
            wad.word = selectedWord;
            wad.definition = convertTo(ui->definition->text());
            favorite.words.push_back(wad);
            favorite.dictionaryNo.push_back(currentSet); //them vao danh sach favorite va luu no thuoc tu dien nao
            v2ListView(favorite.words, ui->favoriteList);
            favorite.saveToFile();
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    editWord* ew=new editWord(convertTo(ui->searchBar->toPlainText()),ui); //mo cua so edit word
    ew->show();
    favorite.initDefinition();
    history.initDefinition();
    v2ListView(favorite.words,ui->favoriteList);
    v2ListView(history.words,ui->historyList);
    //cap nhat lai trong cac list favorite va history de doi def luon
}


void MainWindow::on_pushButton_9_clicked()
{
    addNewWord aw=new addNewWord();
    aw.show();
}

