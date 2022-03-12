#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./guislider.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tra.rtWaveTableCallback.setupSine();
    tra.playWavTable(2);

    GuiSlider *g=new GuiSlider(tra.rtWaveTableCallback.rtGuiSlider.at(0));

    ui->verticalLayout->addWidget(g);
    g->show();
    ui->label->setText("added");
}

MainWindow::~MainWindow()
{
    tra.stopStream();
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{




    qDebug()<<"Task added";

}

