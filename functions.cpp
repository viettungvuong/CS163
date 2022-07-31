#include "functions.h"
#include "main.h"
#include "ui_mainwindow.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <QFile>
#include <QFileInfo>
TernarySearchTree ProgramData::listOfTree[3];
TernarySearchTree ProgramData::currentTree = ProgramData::listOfTree[2]; //mac dinh

//0 la slang
//1 la emoji
//2 la english

void deletetree(TernaryTreeNode* root)
{
    if (!root)
        return;
    deletetree(root->left);
    deletetree(root->mid);
    deletetree(root->right);
    delete root->definition;
    delete root;
}

void createSet(TernarySearchTree* listOfTree)
{
    for (int i = 0; i < NUMofSET; ++i)
    {
        ProgramData::listOfTree[i].import_dictionary(i);
    }
}

int childOfNode(TernaryTreeNode* node)//return number of child
{
    int i = 0;
    if (node->left)
        ++i;
    if (node->mid)
        ++i;
    if (node->right)
        ++i;
    return i;
}

void helper_saveTree(TernaryTreeNode* root, std::string str, int index)
{
    if (!root)
        return;
    if (root->definition)
    {
        str.push_back(root->ch);
        QFile f;

        switch (index)
        {
        case 0://slang
            f.setFileName(qApp->applicationDirPath()+"/Library/slang.txt");
            break;
        case 1://emotion
            f.setFileName(qApp->applicationDirPath()+"/Library/emotional.txt");
            break;
        case 2://dictionary
            f.setFileName(qApp->applicationDirPath()+"/Library/dictionary.txt");
            break;
        default:
            break;
        }
        if (!f.open(QIODevice::WriteOnly | QIODevice::Append))
            return;
        QTextStream fout(&f);
        fout << convertFrom(str) << "  " << convertFrom(*root->definition) << "\n";
        f.close();
        str.pop_back();
    }
    helper_saveTree(root->left, str, index);
    str.push_back(root->ch);
    helper_saveTree(root->mid, str, index);
    str.pop_back();
    helper_saveTree(root->right, str, index);
}

void saveTree(TernaryTreeNode* root, int index)
{
    std::string str = "";
    helper_saveTree(root, str, index);
}

void saveAllTree(TernarySearchTree* listOfTree)
{
    QFile f;
    f.setFileName(qApp->applicationDirPath()+"/Library/slang.txt");
    QTextStream fA(&f);
    if (!f.open(QIODevice::WriteOnly))
        return;
    fA<<"";
    f.close();
    f.setFileName(qApp->applicationDirPath()+"/Library/emotional.txt");
    QTextStream fB(&f);
    if (!f.open(QIODevice::WriteOnly))
        return;
    fB<<"";
    f.close();
    f.setFileName(qApp->applicationDirPath()+"/Library/dictionary.txt");
    QTextStream fC(&f);
    if (!f.open(QIODevice::WriteOnly))
        return;
    fC<<"";
    f.close();
    for (int i = 0; i < NUMofSET; ++i)
    {
        saveTree(ProgramData::listOfTree[i].getRoot(), i);
    }
}

void resetAllDictionary(TernarySearchTree* listOfTree)
{
    for (int i = 0; i < NUMofSET; ++i)
    {
        ProgramData::listOfTree[i].deleteTree();
        ProgramData::listOfTree[i].import_dictionary(i, 1);
    }
    saveAllTree(ProgramData::listOfTree);
}

void changeSet(int& currentSet)
{
    std::cout << "1.Slang set\n2.Emotion set\n3.Dictionary set\nPls Choose your set:";
    int i;
    std::cin >> i;
    if (1 <= i && i <= 3)
    {
        currentSet = i - 1;
        return;
    }
    else
    {
        currentSet = 2;
    }
}

void v2ListView(std::vector<WordAndDef> v, QListWidget* lb) {
    lb->clear();
    for (WordAndDef wad : v) {
        lb->addItem(convertFrom(wad.word));
    }
}

std::vector<WordAndDef> suggestWords(std::string soFar) {
    std::vector<WordAndDef> v;
    if (soFar.empty()||soFar.length()==1)
        return v;
    TernaryTreeNode* t = ProgramData::currentTree.search4keyword(soFar);
    if (t) {
        soFar.pop_back();
        ProgramData::currentTree.inorderTraversalForSuggest(t, soFar, v);
    }
    return v;
}
bool fileExists(const std::string& name) {
    QFileInfo check_file(convertFrom(name));
        // check if file exists and if yes: Is it really a file and no directory?
        if (check_file.exists() && check_file.isFile()) {
            return true;
        } else {
            return false;
        }
}
void load(Ui::MainWindow* ui) {
    //load history va favorite
    srand(time(NULL)); //khoi tao random//Tung dang test cai nay
    currentSet = 2;
    QFile f(qApp->applicationDirPath()+"/currentSet.txt");
    if (!f.open(QIODevice::ReadOnly)) {
        QTextStream ofs(&f);
        ofs<<currentSet;
    }
    else{
        QTextStream ifs(&f);
        qDebug() << "F : " << f.fileName();
        ifs >> currentSet;
    }
    f.close();
    ui->comboBox->setCurrentIndex(currentSet);
    /*ProgramData::listOfTree[2].import_dictionary(2);
    if (currentSet!=2)
       ProgramData::listOfTree[currentSet].import_dictionary(currentSet);*/
    for (int i=0;i<NUMofSET; i++){
        ProgramData::listOfTree[i].import_dictionary(i);
    }
    ProgramData::currentTree = ProgramData::listOfTree[currentSet];
    //ProgramData::listOfTree[0].import_dictionary(0);
    wordOfTheDay(ui);
    history.loadFromFile();
    favorite.loadFromFile();
    if (history.words.size() > 0) {
        v2ListView(history.words, ui->historyList);
    }
    if (favorite.words.size() > 0) {
        v2ListView(favorite.words, ui->favoriteList);
    }

}
void wordOfTheDay(Ui::MainWindow* ui) {
    TernaryTreeNode* t;
    t = ProgramData::listOfTree[2].getRandomWord();
    ui->word->setText(convertFrom(t->word));
    ui->def->setText(convertFrom(*t->definition));
}
std::string convertTo(QString input){
    return input.toStdString();
}
QString convertFrom(std::string input){
    return QString::fromStdString(input);
}
void normalizeString(std::string& str){
    //tai vi format cua tu dien la chu cai dau viet hoa
    //cac chu con lai viet thuong
    str[0]=toupper(str[0]);
    for (int i=1; i<str.length(); i++)
        str[i]=tolower(str[i]);
}
