#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./guislider.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tra.coutDevicesInfo();
    tra.setupStreamParameters(2, 2, 1024);
    tra.rtWaveTableCallback.setupPlayersAndControls();
    tra.rtWaveTableCallback.getCallbackToUi() = [this](std::vector<double> &v)
    {
        static int i = 0;
        if (!(++i % 50))
        {
            ui->label->setText(QString::number( v[0]));
        }
    };
    tra.playWavTable();
    tra.rtWaveTableCallback.setDoScopelog(false);

    for (auto &rts : tra.rtWaveTableCallback.getRtGuiSliders()) {
        GuiSlider *g=new GuiSlider(*rts); //NOLINT
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

