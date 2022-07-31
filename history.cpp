#include "history.h"
#include "functions.h"
#include <fstream>
#include <sstream>
#include <QFile>
#include <queue>
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
    int i=0;
    while (!ifs.atEnd()){
        std::string line=convertTo(ifs.readLine());
        if (i%2==0){
            WordAndDef wad;
            wad.word = line;
            words.push_back(wad);
        }
        else{
            int a;
            std::stringstream ss;
            ss<<line; ss>>a;
            dictionaryNo.push_back(a);
        }
        i++;
   }
    f.close();
    if (i>0)
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
     int n;
     //ifs>>n;
     int i=0;
     while (!ifs.atEnd()){
         std::string line=convertTo(ifs.readLine());
         if (i%2==0){
             WordAndDef wad;
             wad.word = line;
             words.push_back(wad);
         }
         else{
             int a;
             std::stringstream ss;
             ss<<line; ss>>a;
             dictionaryNo.push_back(a);
         }
         i++;
    }
    f.close();
    if (i>0)
      initDefinition();
}
void History::refresh(std::string keyword){
    std::queue<int> deletePos;
    for (int i=0; i<words.size(); i++){
        if (words[i].word==keyword){
            deletePos.push(i); //tim tat ca vi tri co tu nay
        }
    }
    while (!deletePos.empty()){
        words.erase(words.begin() + deletePos.front());
        deletePos.pop();
    }
    saveToFile();
}
void Favorite::refresh(std::string keyword){
    for (int i=0; i<words.size(); i++){
        if (words[i].word==keyword){
            words.erase(words.begin() + i);
            break; //do favorite chi chua toi da 1 tu (kh trung nhau)
        }
    }
    saveToFile();
}
//de lam chuan hoa format tu trong tu dien luon
void Favorite::reset(){
    words.clear();
    saveToFile();
}
void History::reset(){
    words.clear();
    saveToFile();
}
