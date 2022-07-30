#ifndef ADDNEWWORD_H
#define ADDNEWWORD_H

#include <QDialog>

namespace Ui {
class addNewWord;
}

class addNewWord : public QDialog
{
    Q_OBJECT

public:
    explicit addNewWord(QWidget *parent = nullptr);
    ~addNewWord();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addNewWord *ui;
};

#endif // ADDNEWWORD_H
