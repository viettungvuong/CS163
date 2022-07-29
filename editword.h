#ifndef EDITWORD_H
#define EDITWORD_H

#include <QDialog>

namespace Ui {
class editWord;
}

class editWord : public QDialog
{
    Q_OBJECT

public:
    explicit editWord(QWidget *parent = nullptr);
    ~editWord();

private:
    Ui::editWord *ui;
};

#endif // EDITWORD_H
