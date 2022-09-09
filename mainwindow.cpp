#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./guislider.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tra.coutDevicesInfo();
    constexpr int outDev=2, inDev=2,streamBufferFrames = 1024;
    tra.setupStreamParameters(outDev, inDev, streamBufferFrames);
    tra.rtWaveTableCallback.setupPlayersAndControls();
    tra.rtWaveTableCallback.getCallbackToUi() = [this](std::vector<double> &v)
    {

        static int i = 0;
        constexpr int modEvery = 50;
        if (!(++i % modEvery))
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

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onPushButtonClicked);
}

MainWindow::~MainWindow()
{
    tra.stopStream();
    delete ui;
}


void MainWindow::onPushButtonClicked()
{
    qDebug()<<"Clicked";
}

