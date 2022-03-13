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

    for (RtGuiSlider &rts : tra.rtWaveTableCallback.rtGuiSlider) {
        GuiSlider *g=new GuiSlider(rts);
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

