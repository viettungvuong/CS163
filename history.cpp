#include "history.h"
#include "functions.h"
#include <fstream>
#include <sstream>
#include <QFile>
void History::initDefinition() {
    for (int i = 0; i < words.size(); i++) {
        words[i].definition = *ProgramData::listOfTree[dictionaryNo[i]].search4keyword(words[i].word)->definition;
    }
} //ham de them def khi load
void History::saveToFile() {
    QFile f((qApp->applicationDirPath()+"/history.txt"));
    if (!f.open(QIODevice::WriteOnly))
        return;
    QTextStream ofs(&f);
    for (int i = 0; i < words.size(); i++) {
         ofs << convertFrom(words[i].word) << "\n" << dictionaryNo[i] << "\n";
    }

    f.close();
}
void History::loadFromFile() {
    QFile f(qApp->applicationDirPath()+"/history.txt");
    if (!f.open(QIODevice::ReadOnly))
        return;
    QTextStream ifs(&f);
    while (!f.atEnd()){
            std::string temp;
            temp=convertTo(ifs.readLine());
            WordAndDef wad;
            wad.word = temp;
            words.push_back(wad);
            std::string temp2;
            temp2=convertTo(ifs.readLine());
            int a;
            std::stringstream ss;
            ss << temp2; ss >> a;
            dictionaryNo.push_back(a);
    }

    words.pop_back();
    f.close();
    initDefinition();
}
void History::addToHistory(WordAndDef wad, int dictionaryNo) {
    words.push_back(wad);
    this->dictionaryNo.push_back(dictionaryNo); //luu la thuoc tu dien nao
    saveToFile();


}
void Favorite::initDefinition() {
    for (int i = 0; i < words.size(); i++) {
        words[i].definition = *ProgramData::listOfTree[dictionaryNo[i]].search4keyword(words[i].word)->definition;
    }
} //ham de them def khi load
void Favorite::saveToFile() {
    QFile f((qApp->applicationDirPath()+"/favorite.txt"));
    if (!f.open(QIODevice::WriteOnly))
        return;
    QTextStream ofs(&f);
    for (int i = 0; i < words.size(); i++) {
            ofs << convertFrom(words[i].word) << "\n" << dictionaryNo[i] << "\n";
     }

    f.close();
}
void Favorite::loadFromFile() {
    QFile f(qApp->applicationDirPath()+"/favorite.txt");
    if (!f.open(QIODevice::ReadOnly))
        return;
     QTextStream ifs(&f);
     while (!f.atEnd()){
            std::string temp;
            temp=convertTo(ifs.readLine());
            WordAndDef wad;
            wad.word = temp;
            words.push_back(wad);
            std::string temp2;
            temp2=convertTo(ifs.readLine());
            int a;
            std::stringstream ss;
            ss << temp2; ss >> a;
            dictionaryNo.push_back(a);
    }

    words.pop_back();
    f.close();
    initDefinition();
}

