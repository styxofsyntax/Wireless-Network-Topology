#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_generateButton_clicked();

    void on_pushButton_clicked();

    void on_show_net_button_clicked();

    void on_apply_button_clicked();


    void on_graph_pdf_button_clicked();

    void on_xtc_pdf_button_clicked();

    void on_open_graph_button_clicked();

    void on_open_xtc_button_clicked();

    void on_open_path_window_clicked();

    void on_experiments_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
