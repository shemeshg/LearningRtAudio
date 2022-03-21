#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./guislider.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    tra.setupStreamParameters(2);
    tra.rtWaveTableCallback.setupPlayersAndControls();
    tra.playWavTable();

    for (auto &rts : tra.rtWaveTableCallback.rtGuiSlider) {
        GuiSlider *g=new GuiSlider(*rts);
        ui->verticalLayout->addWidget(g);
        g->show();
    }

    ui->label->setText("Sliders:");
}

MainWindow::~MainWindow()
{
    tra.stopStream();
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{




    qDebug()<<"Clicked";

}

