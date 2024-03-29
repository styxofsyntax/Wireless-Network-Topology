#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    Dialog(QWidget *parent = nullptr, QString message = "default");
    ~Dialog();

private slots:
    void on_Dialog_accepted();



private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
