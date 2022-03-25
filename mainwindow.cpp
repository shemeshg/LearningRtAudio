#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./guislider.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    tra.coutDevicesInfo();
    tra.setupStreamParameters(2,2,1024);
    tra.rtWaveTableCallback.setupPlayersAndControls();
    tra.rtWaveTableCallback.callbackToUi = [](std::vector<double> &v) {
        static int i=0;
        if  (!(++i % 50)){
            qDebug()<<"Called back from RTAudio: "<<i<<" "<<v[0]<< " \n";

        }
        /*
        static int i=0;
        if  (!(++i % 50)){
            QString s= QString("Called back from RTAudio: %1 %2").arg(i).arg(v[0]);
            ui->label->setText(s);
        }
        */
    };
    tra.playWavTable();

    for (auto &rts : tra.rtWaveTableCallback.rtGuiSliders) {
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

