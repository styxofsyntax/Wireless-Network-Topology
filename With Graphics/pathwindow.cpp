#include "pathwindow.h"
#include "ui_pathwindow.h"

#include <qvalidator.h>

#include "path.h"
#include "graphviz.h"

PathWindow::PathWindow(QWidget *parent, graph<router> *net, graph<router> *xtc, int lower, int upper) :
    QDialog(parent),
    ui(new Ui::PathWindow),
    net(net),
    xtc(xtc),
    lower(lower),
    upper(upper)
{
    ui->setupUi(this);

    ui->source_name->setValidator( new QIntValidator(lower, upper, this) );
    ui->destination_name->setValidator( new QIntValidator(lower, upper, this) );

    ui->errorLabel->setStyleSheet("QLabel {color : red;}");
    ui->errorLabel->hide();
}

PathWindow::~PathWindow()
{
    delete ui;
}

std::string source = "";
std::string destination = "";
graph<router> *selected;
std::vector<node<router>> path_vec;
bool with = true;
bool only = false;;
bool graph_gen = false;

void PathWindow::on_FindPath_button_clicked()
{
    if(source != ui->source_name->text().toStdString() || destination != ui->destination_name->text().toStdString() || ui->with_button->isChecked() != with){
        path a;
        source = ui->source_name->text().toStdString();
        destination = ui->destination_name->text().toStdString();
        if(ui->source_name->text().toInt() > lower  && ui->source_name->text().toInt() <= upper && ui->destination_name->text().toInt() > lower  && ui->destination_name->text().toInt() <= upper)
        {
            only = NULL;
            graph_gen = false;

            ui->errorLabel->hide();
            ui->generate_path_graph_button->setEnabled(false);

            ui->path_check->setEnabled(true);
            ui->path_check->setCheckState(Qt::Unchecked);
            ui->path_check->setEnabled(false);

            ui->show_button->setEnabled(false);

            std::string path_out;

            with = ui->with_button->isChecked();
            if(with){
                selected = xtc;
            }
            else{
                selected = net;
            }

            path_vec = a.find_path(*selected,source,destination);
            path_out = path::display_path(path_vec);

            if(path_vec.empty()){
                ui->errorLabel->setText("Path does not exist!");
                ui->errorLabel->show();
            } else{
                ui->output_text->setText(QString::fromStdString(path_out));
                ui->generate_path_graph_button->setEnabled(true);
                std::string distance = std::to_string(path::path_distance(path_vec));
                ui->distanceOuput->setText(QString::fromStdString(distance));

            }

        }else
        {
            ui->errorLabel->setText("Out of Range!");
            ui->errorLabel->show();
        }
    }
}


void PathWindow::on_generate_path_graph_button_clicked()
{
    only = ui->only_radio->isChecked() ? true: false;
    graphviz::generateFile_highlight(*selected,"path_graph",path_vec, only);
    if(only)
        graphviz::generateImage("path_graph_only");
    else graphviz::generateImage("path_graph");

    ui->path_check->setEnabled(true);
    ui->path_check->setCheckState(Qt::Checked);
    ui->path_check->setEnabled(false);
    ui->show_button->setEnabled(true);

    graph_gen = true;
}


void PathWindow::on_show_button_clicked()
{
    if(only)
        graphviz::openImage("path_graph_only.pdf");
    else graphviz::openImage("path_graph.pdf");
}



void PathWindow::on_complete_radio_clicked()
{
    if(only != ui->only_radio->isChecked() || !graph_gen){
        ui->path_check->setEnabled(true);
        ui->path_check->setCheckState(Qt::Unchecked);
        ui->path_check->setEnabled(false);
    }else {
        ui->path_check->setEnabled(true);
        ui->path_check->setCheckState(Qt::Checked);
        ui->path_check->setEnabled(false);
    }
}


void PathWindow::on_only_radio_clicked()
{
    if(only != ui->only_radio->isChecked() || !graph_gen){
        ui->path_check->setEnabled(true);
        ui->path_check->setCheckState(Qt::Unchecked);
        ui->path_check->setEnabled(false);
    }else {
        ui->path_check->setEnabled(true);
        ui->path_check->setCheckState(Qt::Checked);
        ui->path_check->setEnabled(false);
    }
}

