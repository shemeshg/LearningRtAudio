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
}

MainWindow::~MainWindow()
{
    tra.stopStream();
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    tra.rtWaveTableCallback.rtGuiSlider.at(0).val = 440;
    GuiSlider *g=new GuiSlider("My slider",50,0,800);

    ui->verticalLayout->addWidget(g);
    g->show();
    ui->label->setText("added");

    qDebug()<<"Task added";

}

